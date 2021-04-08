#pragma once
#include <windows.h>

class CCriticalSectionLock
{
public:
	CCriticalSectionLock(CRITICAL_SECTION *cs)
	{
		m_cs = cs;
		EnterCriticalSection(cs);
	}

	~CCriticalSectionLock()
	{
		LeaveCriticalSection(m_cs);
	}

private:
	CRITICAL_SECTION	*m_cs;
};

