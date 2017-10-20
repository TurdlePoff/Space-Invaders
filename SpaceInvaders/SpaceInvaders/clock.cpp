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
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"
// Static Variables

// Static Function Prototypes

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

bool
CClock::Initialise()
{
	__int64 _currTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);
	m_fCurrentTime = static_cast<float>(_currTime);
	m_fLastTime = static_cast<float>(_currTime);

    return (true);
}

void
CClock::Process()
{
	__int64 currTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

    m_fLastTime = m_fCurrentTime;

    m_fCurrentTime = static_cast<float>(currTime);

    if (m_fLastTime == 0.0f)
    {
        m_fLastTime = m_fCurrentTime;
    }

    m_fDeltaTime = m_fCurrentTime - m_fLastTime;

    m_fTimeElapsed += m_fDeltaTime;
}

float
CClock::GetDeltaTick()
{
    return (m_fDeltaTime / 1000.0f);
}