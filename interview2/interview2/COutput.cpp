#include "COutput.h"
#include "CCriticalSectionLock.h"
#include <iostream>

const int COutput::m_FrequencyVectorMaxSize = 10;

/*
*   COutput default constructor initializes
*   member variables
*/
COutput::COutput() :
    m_nFrequencyVectorSize(m_FrequencyVectorMaxSize)
{
    InitializeCriticalSection(&m_cs);

    // Frequency vector should hold up to 10 elements
    for (int i = 0; i < m_FrequencyVectorMaxSize; i++)
    {
        m_vFrequency.push_back(0);
    }
}

/*
*   COutput destructor performs clean up
*/
COutput::~COutput()
{
    DeleteCriticalSection(&m_cs);
}

/*
*   The update method updates the frequency vector
* 
*   @param nIndex : an index
*/
bool COutput::update(int nIndex)
{
    if (nIndex < 0 || nIndex >= 10)
    {
        // If input value is not valid,
        // return false
        return false;
    }

    // This object can be called from multiple threads
    // so we sychronize access to shared data with an 
    // interlocked function
    InterlockedIncrement(&m_vFrequency[nIndex]);

    return true;
}

/*
*   The display method outputs frequency vector
*   to stdout
*/
void COutput::display(void)
{
    // This object can be called from multiple threads
    // so we sychronize access to shared data with a 
    // critical section
    CCriticalSectionLock lock(&m_cs);

    int i = 0;
    for (int nVal : m_vFrequency)
    {
        std::cout << "index = " << i << " : " << nVal << std::endl;
        i++;
    }
}

/*
*   The sumFreq method is used by unit tests
*   to verify that the frequency counts add
*   up to N.
*/
int COutput::sumFreq(void)
{
    // This object can be called from multiple threads
    // so we sychronize access to shared data with a 
    // critical section
    CCriticalSectionLock lock(&m_cs);

    int nAccum = 0;
    for (int nVal : m_vFrequency)
    {
        nAccum += nVal;
    }

    return nAccum;
}
