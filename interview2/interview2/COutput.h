#pragma once
#include <vector>
#include <windows.h>

/*
*   Definition of COutput
*/
class COutput
{
    // The vector max size.  It should be 10.
    static const int m_FrequencyVectorMaxSize;

public:
    COutput();
    ~COutput();

    bool update(int nIndex);
    void display(void);

    // Used for unit testing
    int sumFreq(void);

private:
    std::vector<long>    m_vFrequency;
    int                  m_nFrequencyVectorSize;

    // Decided to use a critical section since
    // we just need to synchronize access to shared
    // data between threads in a single process
    CRITICAL_SECTION    m_cs;
};

