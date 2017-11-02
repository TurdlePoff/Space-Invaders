//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "Clock.cpp"
// Description	: Implemention file for Clock
// Author		: Author of BreakOut code 
// Changes		: by Vivian Ngo
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"

// Implementation
CClock::CClock()
: m_fTimeElapsed(0.0f)
, m_fDeltaTime(0.0f)
, m_fLastTime(0.0f)
, m_fCurrentTime(0.0f)
{
}

CClock::~CClock()
{
}

/************
* Initialise: Initialises elements needed for clock
*************/
bool
CClock::Initialise()
{
	__int64 _TimerFrequency, _currTime;
	QueryPerformanceFrequency((LARGE_INTEGER*)&_TimerFrequency);
	m_SecondsPerCount = 1.0f / static_cast<float>(_TimerFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);
	m_fCurrentTime = static_cast<float>(_currTime);
	m_fLastTime = static_cast<float>(_currTime);

	return (true);
}

/************
* Process: Processes counters
*************/
void
CClock::Process()
{
	//Get the time this frame.

	__int64 currTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_fCurrentTime = static_cast<float>(currTime);

	//Time difference between this frame and the previous frame
	m_fDeltaTime = static_cast<float>((m_fCurrentTime - m_fLastTime)*m_SecondsPerCount);

	//Prepare for the next frame
	m_fLastTime = static_cast<float>(m_fCurrentTime);

	//Force non-negative
	if (m_fDeltaTime < 0.0)
	{
		m_fDeltaTime = 0.0;
	}

	m_fTimeElapsed += m_fDeltaTime;
}

/************
* GetDeltaTick: Getter for DeltaTick
*************/
float
CClock::GetDeltaTick()
{
	return static_cast<float>(m_fDeltaTime);
}
