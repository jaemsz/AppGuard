#pragma once
#include <vector>
#include <windows.h>

/*
*	Definition of COutput
*/
class COutput
{
public:
	COutput();
	~COutput();

	bool update(int nIndex);
	void display(void);

	// Used for unit testing
	int sumFreq(void);

private:
	std::vector<int>	m_vFrequency;

	// Decided to use a critical section since
	// we just need to synchronize access to shared
	// data between threads in a single process
	CRITICAL_SECTION	m_cs;
};

