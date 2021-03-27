#include "CQueue.h"

// queue size
const int CQueue::m_nQueueMaxSize = 10;

/*
*   CQueue default constructor initializes
*   member variables
*/
CQueue::CQueue() :
    m_bTerm(false),
    m_nCount(0),
    m_nMaxValues(10)
{
    InitializeCriticalSection(&m_cs);
}

/*
*   CQueue constructor initializes
*   member variables
* 
*   @param nMaxValues : This value represents N
*/
CQueue::CQueue(int nMaxValues) : 
    m_bTerm(false),
    m_nCount(0), 
    m_nMaxValues(nMaxValues)
{
    InitializeCriticalSection(&m_cs);
}

/*
*   CQueue destructor performs clean up
*/
CQueue::~CQueue()
{
    // Delete the critical section object
    DeleteCriticalSection(&m_cs);
}

/*
*   The push function adds a value to the queue
* 
*   @param val : A value to add to the queue
*   @return : 
*       QueueRet::ok    : val was added successuflly
*       QueueRet::full  : queue is full
*       QueueRet:term   : queue has seen N items
*/
QueueRet CQueue::push(int val)
{
    // This object can be called from multiple threads
    // so we sychronize access to shared data with a 
    // critical section
    EnterCriticalSection(&m_cs);

    if (m_nCount == m_nMaxValues)
    {
        // N values have been seen.
        // Save this state to m_bTerm
        m_bTerm = true;
        LeaveCriticalSection(&m_cs);
        // Let the caller terminate
        return QueueRet::term;
    }

    if (m_queue.size() < m_nQueueMaxSize)
    {
        // Add val to the queue
        m_queue.push(val);
        // Increment our counter
        m_nCount++;

        LeaveCriticalSection(&m_cs);
        // Let the caller know that val was added
        return QueueRet::ok;
    }

    LeaveCriticalSection(&m_cs);
    return QueueRet::full;
}

/*
*   The pop function returns a value from the queue.
* 
*   @param val : A value from the queue
*   @return :
*       QueueRet::ok    : val was popped successuflly
*       QueueRet::empty : queue is empty
*       QueueRet:term   : queue has seen N items
*/
QueueRet CQueue::pop(int& val)
{
    // This object can be called from multiple threads
    // so we sychronize access to shared data with a 
    // critical section
    EnterCriticalSection(&m_cs);

    if (m_queue.empty())
    {
        if (m_bTerm)
        {
            // The queue has seen N values and there
            // are no more items to process on the queue
            LeaveCriticalSection(&m_cs);
            // Let the caller terminate
            return QueueRet::term;
        }

        LeaveCriticalSection(&m_cs);
        // Tell the caller that the queue is empty
        return QueueRet::empty;
    }

    // Take a value from the queue
    // and save it to val
    val = m_queue.front();
    m_queue.pop();

    LeaveCriticalSection(&m_cs);
    // Let the caller know that pop succeeded
    return QueueRet::ok;
}
