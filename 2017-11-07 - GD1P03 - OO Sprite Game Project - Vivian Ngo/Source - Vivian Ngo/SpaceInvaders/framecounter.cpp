//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "framecounter.cpp"
// Description	: Implementation file for framecounter
// Author		: Author of BreakOut. Modified by Vivian Ngo.
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// This Include
#include "framecounter.h"

CFPSCounter::CFPSCounter()
:m_fTimeElapsed(0.0f)
, m_iFrameCount(0)
, m_fFrameRate(0)
{
}

CFPSCounter::~CFPSCounter()
{
}

/********************
* Initialise: Initialises FPSCounter
*********************/
bool
CFPSCounter::Initialise()
{
	return (true);
}

/********************
* CountFramesPerSecond: Counts the number of frames every second
*********************/
void 
CFPSCounter::CountFramesPerSecond(float _fDeltaTime)
{
	++m_iFrameCount;

	m_fTimeElapsed += _fDeltaTime;

	if (m_fTimeElapsed >= 1.0f)
	{
		m_fFrameRate = static_cast< float >(m_iFrameCount);
		m_iFrameCount = 0;
		m_fTimeElapsed = 0.0f;
	}
	UpdateFPSText();
}

/********************
* UpdateFPSText: Updates the FPS text
*********************/
void CFPSCounter::UpdateFPSText()
{
	m_strFPS = L"FPS: ";
	wchar_t wstrTemp[10];
	_itow_s(static_cast< int >(m_fFrameRate), wstrTemp, 10);
	m_strFPS += wstrTemp;
}