//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "Sprite.cpp"
// Description	: Implemention file for Sprite
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes
#include <iostream>
#include <map>
#include <string>

// Local Includes
#include "Game.h"
#include "BackBuffer.h"
#include "utils.h"
#include "resource.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

/************
* CLevelLogic Constructor
*************/
CSprite::CSprite(ESprite _eType)
: m_eSpriteType(_eType)
, m_iFramePositionW(8)
, m_iFramePositionH(0) //The Y position where the sprite is located on the sprite sheet
, m_iFrameToMoveW(0)
, m_bFrameSwitched(false)
, m_bDeadSwitched(false)
, m_isActivated(false)
, m_iX(0)
, m_iY(0)
, m_widthGap(8)
, m_iBarricadeMask(IDB_SSMASK)
{
	switch (_eType) //Initialise a specific sprite's specifications depending on which one the player chooses
	{
		case ESprite::MAINMENU:
		case ESprite::BACKGROUND:
		case ESprite::INSTRUCTIONS:
		case ESprite::HIGHSCORES:
		{
			m_iW = 1000;
			m_iH = 800;
			break;
		}
		case ESprite::LVLCOMP:
		{
			m_iFramePositionW = 0;
			m_iW = 350;
			m_iH = 96;
			break;
		}
		case ESprite::BULLET:
		{
			m_iFramePositionH = 256;
			m_iW = 12;
			m_iH = 20;
			break;
		}
		case ESprite::PLAYER:
		{
			m_iFramePositionH = 8;
			m_iFrameToMoveW = 68;
			m_iW = 52;
			m_iH = 32;
			break;
		}
		case ESprite::DEADPLAYER:
		{
			m_iFramePositionH = 8;
			m_iFramePositionW = 68;
			m_iW = 60;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYMED:
		{
			m_iFramePositionH = 48;
			m_iFrameToMoveW = 112;
			m_iW = 44;
			m_iH = 32;
			break;
		}
		case ESprite::DEADMED:
		{
			m_iFramePositionW = 112;
			m_iFramePositionH = 48;
			m_iW = 52;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYBOT:
		{
			m_iFramePositionH = 88;
			m_iFrameToMoveW = 104;
			m_iW = 48;
			m_iH = 32;
			break;
		}
		case ESprite::DEADBOT:
		{
			m_iFramePositionW = 104;
			m_iFramePositionH = 48;
			m_iW = 52;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYTOP:
		{
			m_iFramePositionH = 128;
			m_iFrameToMoveW = 88;
			m_iW = 32;
			m_iH = 32;
			break;
		}
		case ESprite::DEADTOP:
		{
			m_iFramePositionW = 88;
			m_iFramePositionH = 128;
			m_iW = 52;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYSHIP:
		{
			m_iFramePositionH = 168;
			m_iW = 64;
			m_iH = 28;
			break;
		}
		//TOP BARRICADES
		case ESprite::BAR1:
		{
			m_iFramePositionH = 204;
			m_iFramePositionW = 8;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR2:
		{
			m_iFramePositionH = 204;
			m_iFramePositionW = 24;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR3:
		{
			m_iFramePositionH = 204;
			m_iFramePositionW = 40;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR4:
		{
			m_iFramePositionH = 204;
			m_iFramePositionW = 56;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		//SECOND ROW BARRICADES
		case ESprite::BAR5:
		{
			m_iFramePositionH = 215;
			m_iFramePositionW = 8;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR6:
		{
			m_iFramePositionH = 215;
			m_iFramePositionW = 24;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR7:
		{
			m_iFramePositionH = 215;
			m_iFramePositionW = 40;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR8:
		{
			m_iFramePositionH = 215;
			m_iFramePositionW = 56;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		//THIRD ROW BARRICADES
		case ESprite::BAR9:
		{
			m_iFramePositionH = 226;
			m_iFramePositionW = 8;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR10:
		{
			m_iFramePositionH = 226;
			m_iFramePositionW = 24;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR11:
		{
			m_iFramePositionH = 226;
			m_iFramePositionW = 40;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR12:
		{
			m_iFramePositionH = 226;
			m_iFramePositionW = 56;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		//FOURTH ROW BARRICADES
		case ESprite::BAR13:
		{
			m_iFramePositionH = 237;
			m_iFramePositionW = 8;
			m_iW = 16;
			m_iH = 11;
			break;
		}
		case ESprite::BAR14:
		{
			m_iFramePositionH = 237;
			m_iFramePositionW = 56;
			m_iW = 16;
			m_iH = 11;
			break;
		}
	}
    ++s_iRefCount;
}

CSprite::CSprite()
{
}

/************
* CLevelLogic Destructor
*************/
CSprite::~CSprite()
{
	DeleteObject(m_hSprite);
	DeleteObject(m_hMask);

	--s_iRefCount;

	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

/************
* Initialise: Initialises a sprite depending on which one is selected to be created
* @return true
*************/
bool
CSprite::Initialise()
{
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	int iSprite = 0;
	int iMask = 0;

	//Set resources for game items
	if (m_eSpriteType == ESprite::BACKGROUND)
	{
		iSprite = IDB_BACKGROUND;
		iMask = IDB_BACKGROUNDMASK;
	}
	else if (m_eSpriteType == ESprite::MAINMENU)
	{
		iSprite = IDB_MAINMENU;
		iMask = IDB_BACKGROUNDMASK;
	}
	else if (m_eSpriteType == ESprite::INSTRUCTIONS)
	{
		iSprite = IDB_INSTRUCTIONS;
		iMask = IDB_BACKGROUNDMASK;
	}
	else if (m_eSpriteType == ESprite::LVLCOMP)
	{
		iSprite = IDB_LVLCOMP;
		iMask = IDB_LVLCOMPMASK;
	}
	else if (m_eSpriteType == ESprite::HIGHSCORES)
	{
		iSprite = IDB_HIGHSCORES;
		iMask = IDB_BACKGROUNDMASK;
	}
	else
	{
		iSprite = IDB_SS;
		iMask = IDB_SSMASK;//IDB_SSMASK;
	}

	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(iSprite));
	VALIDATE(m_hSprite);
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(iMask));
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

	//If the sprite is one of the following specified types, set the sprite widths and heights to the actual sprite w and h
	if (m_eSpriteType == ESprite::BACKGROUND || m_eSpriteType == ESprite::MAINMENU 
		|| m_eSpriteType == ESprite::INSTRUCTIONS || m_eSpriteType == ESprite::LVLCOMP
		|| m_eSpriteType == ESprite::HIGHSCORES)
	{
		m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(iMask));
		VALIDATE(m_hMask);
		GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

		m_iW = m_bitmapSprite.bmWidth;
		m_iH = m_bitmapSprite.bmHeight;
	}

    return (true);
}

/************
* Draw: Draws a sprite
*************/
void
CSprite::Draw()
{
	//Sizes of sprites
	int iW = GetWidth();
	int iH = GetHeight();
	//Positions of sprites
	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);	

    CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, m_iFramePositionW, m_iFramePositionH, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, m_iFramePositionW, m_iFramePositionH, SRCPAINT);

    SelectObject(s_hSharedSpriteDC, hOldObj);
}

/************
* Processes: Processes a sprite
*************/ //-----------------------------------------------------------------
void
CSprite::Process(float _fDeltaTick)
{
	//If animating
	if (GetIsAnimationActivated())
	{
		NormalAnimation(_fDeltaTick);
	}

	if (m_eSpriteType == ESprite::PLAYER)
	{
		DeadAnimation(_fDeltaTick);
	}
}

/************
* GetWidth: Get width of a sprite
* @return: m_iW - width of sprite
*************/
int
CSprite::GetWidth() const
{
    return m_iW;
}

/************
* GetHeight: Get height of a sprite
* @return: m_iH - height of sprite
*************/
int
CSprite::GetHeight() const
{
    return m_iH;
}

/************
* GetX: Get X position of a sprite
* @return: m_iX - x position of sprite
*************/
int 
CSprite::GetX() const
{
    return (m_iX);
}

/************
* GetY: Get Y position of a sprite
* @return: m_iY - y position of sprite
*************/
int 
CSprite::GetY() const
{
    return (m_iY);
}

/************
* SetX: SetX position of a sprite
* @parameter: _i - x pos of sprite
*************/
void 
CSprite::SetX(int _i)
{
    m_iX = _i;
}

/************
* SetY: SetY position of a sprite
* @parameter: _i - Y pos of sprite
*************/
void 
CSprite::SetY(int _i)
{
    m_iY = _i;
}

/************
* TranslateRelative: TranslateRelative position of a sprite
* @parameter: _iX - X translate pos
* @parameter: _iY - Y translate pos
*************/
void 
CSprite::TranslateRelative(int _iX, int _iY)
{
    m_iX += _iX;
    m_iY += _iY;
}

/************
* TranslateAbsolute: TranslateAbsolute position of a sprite
* @parameter: _iX - X translate pos
* @parameter: _iY - Y translate pos
*************/
void 
CSprite::TranslateAbsolute(int _iX, int _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}

/************
* ActivateAnimation: Activates current sprites animation
* @parameter: _b - animation 
*************/
void CSprite::ActivateAnimation(bool _b)
{
	m_isActivated = _b;
}

/************
* GetIsAnimationActivated: Gets if animation is activated
* @return: m_isActivated
*************/
bool CSprite::GetIsAnimationActivated()
{
	return m_isActivated;
}

/************
* NormalAnimation: Activates normal animation
*************/
void CSprite::NormalAnimation(float _fDeltaTick)
{
	if (m_bFrameSwitched)
	{
		m_bFrameSwitched = false;
		m_iFramePositionW -= m_iW + m_widthGap;
	}
	else
	{
		m_bFrameSwitched = true;
		m_iFramePositionW += m_iW + m_widthGap;
	}
}

/************
* ActivateDead: Activates dead sprite animation
* @parameter: _b - animation
*************/
void CSprite::ActivateDeadAnimation(bool _b)
{
	m_bDeadSwitched = _b;
}

bool CSprite::GetIsDead()
{
	return m_bDeadSwitched;
}

/************
* DeadAnimation: Activates dead sprite animation
*************/
void CSprite::DeadAnimation(float _fDeltaTick)
{
	if (GetIsDead())
	{
		if (m_eSpriteType == ESprite::PLAYER)
		{
			m_iFramePositionW = m_iW + m_widthGap + m_widthGap;
		}
		else if (m_eSpriteType == ESprite::ENEMYBOT 
				|| m_eSpriteType == ESprite::ENEMYMED
				|| m_eSpriteType == ESprite::ENEMYTOP)
		{
			m_iFramePositionW += m_iW + m_iW + m_widthGap + m_widthGap + m_widthGap;
		}
	}
	else
	{
		if (m_eSpriteType == ESprite::PLAYER)
		{
			m_iFramePositionW = m_widthGap;
		}
	}
}

void CSprite::ChangeBarricade()
{
	m_iFramePositionW += 72;
}
