//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__ANIMATEDSPRITE_H__)
#define __ANIMATEDSPRITE_H__

// Library Includes
#include "windows.h"
#include <vector>

// Local Includes

// Types

// Constants

// Prototypes
class CAnimatedSprite
{
	// Member Functions
public:
	CAnimatedSprite();
	virtual ~CAnimatedSprite();

	virtual bool Initialise(const int _kiSpriteID, const int _kiMaskID);


	void Draw();
	void Process(float _fDeltaTick);
	void AddFrame(int x);

	int GetFrameSpeed();
	int GetFrameWidth();

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

	void Pause();
	bool IsPaused();

protected:

private:
	CAnimatedSprite(const CAnimatedSprite& _kr);
	CAnimatedSprite& operator= (const CAnimatedSprite& _kr);

	// Member Variables
public:

protected:
	//Center handle
	int m_iX;
	int m_iY;

	HBITMAP m_hSprite;
	HBITMAP m_hMask;

	BITMAP m_bitmapSprite;
	BITMAP m_bitmapMask;

	static HDC s_hSharedSpriteDC;
	static int s_iRefCount;

	std::vector<int> c_spriteContainer;
	int m_numOfFrames;
	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};

#endif    // __ANIMATEDSPRITE_H__
