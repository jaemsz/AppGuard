#pragma once
#include <queue>
#include <windows.h>

// Define return codes for CQueue push
// and pop methods
enum class QueueRet
{
    ok,     // Successfully pushed or popped an item
    empty,  // Queue is empty
    full,   // Queue is full
    term,   // Queue has seen N items
};

/*
*   Definition of CQueue
*/
class CQueue
{
public:
    // The queues max size.  It should be 10.
    static const int m_nQueueMaxSize;

    CQueue();
    CQueue(int nMaxValues);
    ~CQueue();

    QueueRet push(int val);
    QueueRet pop(int& val);

private:
    bool                m_bTerm;
    int                 m_nMaxValues;   // This is N
    int                 m_nCount;
    std::queue<int>     m_queue;

    // Decided to use a critical section since
    // we just need to synchronize access to shared
    // data between threads in a single process
    CRITICAL_SECTION    m_cs;
};

