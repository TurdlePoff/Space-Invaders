//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "framecounter.h"
// Description	: Declaration file for framecounter
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#ifndef _FPSCOUNTER_H_
#define _FPSCOUNTER_H_

// Library Includes
#include <Windows.h>
#include <string>

class CFPSCounter
{
	//Member Functions
public:
	CFPSCounter();
	~CFPSCounter();

	void CountFramesPerSecond(float _fDeltaTime);
	bool Initialise();

	void UpdateFPSText();

protected:

private:
	int m_iFrameCount;
	float m_fTimeElapsed;
	float m_fFrameRate;
	std::wstring m_strFPS;

};


#endif // 
