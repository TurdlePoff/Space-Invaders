//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "Sprite.h"
// Description	: Declaration file for Sprite
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"
#include <vector>
#include <ctime>

// Local Includes
#include "EEnums.h"
// Types

// Constants

// Prototypes
class CSprite
{
    // Member Functions
public:
    CSprite(ESprite _eType);
	CSprite();
    ~CSprite();

	bool Initialise();
    void Draw();
    void Process(float _fDeltaTick);

    int GetWidth() const;
    int GetHeight() const;

    int GetX() const;
    int GetY() const;
    void SetX(int _i);
    void SetY(int _i);

    void TranslateRelative(int _iX, int _iY);
    void TranslateAbsolute(int _iX, int _iY);

	void ActivateAnimation(bool _b);
	bool GetIsAnimationActivated();

	void ActivateDeadAnimation(bool _b);
	bool GetIsDead();

	void NormalAnimation(float _fDeltaTick);
	void DeadAnimation(float _fDeltaTick);

protected:
	//Center handle
	int m_iX;
	int m_iY;
	int m_iW;
	int m_iH;
	int m_iFramePositionW;
	int m_iFramePositionH;
	int m_iFrameToMoveW;
	int m_widthGap;

	ESprite m_eSpriteType;

	HBITMAP m_hSprite;
	HBITMAP m_hMask;

	BITMAP m_bitmapSprite;
	BITMAP m_bitmapMask;

	clock_t m_cBeginSpriteMove;
	clock_t m_cEndSpriteMove;

	static HDC s_hSharedSpriteDC;
	static int s_iRefCount;

	std::vector<int> c_spriteContainer;
	int m_numOfFrames;
	bool m_isActivated;
	bool m_loop;
	bool m_bFrameSwitched;
	bool m_bDeadSwitched;

private:
    CSprite(const CSprite& _kr);
    CSprite& operator= (const CSprite& _kr);
};

#endif    // __SPRITE_H__
