#include <iostream>
#include <thread>
#include "ThreadFuncs.h"

int main()
{
    // Set N to the number of random values to generate
    int N = 1000000;

    // Create the queue object to handle up to N items
    CQueue queue(N);
    // Create the output object
    COutput output;

    // Create events to signal when there is work to do
    HANDLE hProducerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hConsumerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    // Create 2 producer threads and 2 consumer threads
    std::thread t1(producer, std::ref(queue), std::ref(hConsumerEvent), std::ref(hProducerEvent));
    std::thread t2(producer, std::ref(queue), std::ref(hConsumerEvent), std::ref(hProducerEvent));
    std::thread t3(consumer, std::ref(queue), std::ref(output), std::ref(hConsumerEvent), std::ref(hProducerEvent));
    std::thread t4(consumer, std::ref(queue), std::ref(output), std::ref(hConsumerEvent), std::ref(hProducerEvent));

    // Wait for threads to return
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Cleanup
    CloseHandle(hProducerEvent);
    CloseHandle(hConsumerEvent);

    // Display the output
    output.display();

    return 0;
}
