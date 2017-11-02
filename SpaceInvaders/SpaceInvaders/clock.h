//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "Clock.h"
// Description	: Declaration file for Clock
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Prototypes
class CClock
{
    // Member Functions
public:
    CClock();
    ~CClock();

    bool Initialise();

    void Process();

    float GetDeltaTick();

protected:
	float m_fTimeElapsed;
	float m_fDeltaTime;
	float m_fLastTime;
	double m_fCurrentTime;
	double m_SecondsPerCount;
	int m_iFrameCount = 0;

private:
    CClock(const CClock& _kr);
    CClock& operator= (const CClock& _kr);

};

#endif    // __CLOCK_H__
