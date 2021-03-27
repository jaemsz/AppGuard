#include "COutput.h"
#include <iostream>

/*
*   COutput default constructor initializes
*   member variables
*/
COutput::COutput()
{
    InitializeCriticalSection(&m_cs);

    // Frequency vector should hold up to 10 
    // values:  0 to 9
    m_vFrequency = { 0,0,0,0,0,0,0,0,0,0 };
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
    // so we sychronize access to shared data with a 
    // critical section
    EnterCriticalSection(&m_cs);
    // incrememt count at the index
    m_vFrequency[nIndex] += 1;
    LeaveCriticalSection(&m_cs);

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
    EnterCriticalSection(&m_cs);

    int i = 0;
    for (int nVal : m_vFrequency)
    {
        std::cout << "index = " << i << " : " << nVal << std::endl;
        i++;
    }

    LeaveCriticalSection(&m_cs);
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
    EnterCriticalSection(&m_cs);

    int nAccum = 0;
    for (int nVal : m_vFrequency)
    {
        nAccum += nVal;
    }

    LeaveCriticalSection(&m_cs);
    return nAccum;
}
