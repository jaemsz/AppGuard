#pragma once
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "CQueue.h"
#include "COutput.h"

/*
*   The producer thread adds random values to the queue.
*
*   @param queue : queue to store random values
*   @param hProducerEvent : Event object that tells producer there is work to do
*   @param hConsumerEvent : Event object that tells consumer there is work to do
*/
void producer(CQueue& queue, HANDLE hProducerEvent, HANDLE hConsumerEvent)
{
    QueueRet action = QueueRet::ok;
    bool bTerm = false;
    DWORD dwWait = 0;

    // Initialize random number generator
    srand((unsigned int)time(NULL));

    while (true)
    {
        if (!bTerm)
        {
            // Generate random number and add it to the queue
            int val = rand() % 10;
            action = queue.push(val);
        }
        else
        {
            // Break out of the loop and return
            break;
        }
        
        switch (action)
        {
        case QueueRet::ok:
            // Signal the consumer that there is work to do
            SetEvent(hConsumerEvent);
            break;
        case QueueRet::full:
            // queue is full.  Consumer will signal the 
            // producer when the queue is not full.
            dwWait = WaitForSingleObject(hProducerEvent, INFINITE);
            if (dwWait != WAIT_OBJECT_0)
            {
                // WaitForSingleObject should return WAIT_OBJECT_0 normally,
                // but there is a case where it may return something else,
                // so we handle it by terminating the thread
                bTerm = true;
                queue.setTerm();
                SetEvent(hConsumerEvent);
            }
            break;
        case QueueRet::term:
            // queue has seen N random values, so producer
            // can stop generating random values and quit.
            bTerm = true;
            // We need to inform the consumer since it can be
            // waiting for more work.
            SetEvent(hConsumerEvent);
            break;
        default:
            break;
        }
    }
}

/*
*   The consumer thread takes random values from the queue.
*
*   @param queue : queue to read random values from
*   @param output : holds frequency of random values in a vector
*   @param hProducerEvent : Event object that tells producer there is work to do
*   @param hConsumerEvent : Event object that tells consumer there is work to do
*/
void consumer(CQueue& queue, COutput& output, HANDLE hProducerEvent, HANDLE hConsumerEvent)
{
    QueueRet action = QueueRet::ok;
    bool bTerm = false;
    int val = 0;
    DWORD dwWait = 0;

    while (true)
    {
        if (!bTerm)
        {
            // Read from the queue
            action = queue.pop(val);
        }
        else
        {
            // Break out of the loop and return
            break;
        }

        switch (action)
        {
        case QueueRet::ok:
            // Update the frequency vector
            output.update(val);
            // Signal the producer to generate more random numbers
            SetEvent(hProducerEvent);
            break;
        case QueueRet::empty:
            // The queue is empty. The producer will signal the
            // consumer when the queue has items for processing.
            dwWait = WaitForSingleObject(hConsumerEvent, INFINITE);
            if (dwWait != WAIT_OBJECT_0)
            {
                // WaitForSingleObject should return WAIT_OBJECT_0 normally,
                // but there is a case where it may return something else,
                // so we handle it by terminating the thread
                bTerm = true;
                queue.setTerm();
                SetEvent(hProducerEvent);
            }
            break;
        case QueueRet::term:
            // queue has seen N random values, so consumer
            // can stop reading from the queue and quit.
            bTerm = true;
            break;
        default:
            break;
        }
    }
}
