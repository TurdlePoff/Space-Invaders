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

// Static Function Prototypes

// Implementation

CSprite::CSprite(ESprite _eType)
: m_eSpriteType(_eType)
, m_iFramePositionW(8)
, m_iFramePositionH(0) //The Y position where the sprite is located on the sprite sheet
, m_iX(0)
, m_iY(0)
{
	switch (_eType)
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
		case ESprite::BARRICADE:
		{
			m_iFramePositionH = 204;
			m_iW = 44;
			m_iH = 32;
			break;
		}
	}
    ++s_iRefCount;
}

CSprite::CSprite()
{
}

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

bool
CSprite::Initialise()
{
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	int iBackground = 0;
	int iMask = 0;

	if (m_eSpriteType == ESprite::BACKGROUND)
	{
		iBackground = IDB_BACKGROUND;
		iMask = IDB_BACKGROUNDMASK;
	}
	else if (m_eSpriteType == ESprite::MAINMENU)
	{
		iBackground = IDB_MAINMENU;
		iMask = IDB_BACKGROUNDMASK;
	}
	else if (m_eSpriteType == ESprite::INSTRUCTIONS)
	{
		iBackground = IDB_INSTRUCTIONS;
		iMask = IDB_BACKGROUNDMASK;
	}
	else if (m_eSpriteType == ESprite::LVLCOMP)
	{
		iBackground = IDB_LVLCOMP;
		iMask = IDB_LVLCOMPMASK;
	}
	else if (m_eSpriteType == ESprite::HIGHSCORES)
	{
		iBackground = IDB_HIGHSCORES;
		iMask = IDB_BACKGROUNDMASK;
	}
	else
	{
		iBackground = IDB_SS;
		iMask = IDB_SSMASK;
	}

	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(iBackground));
	VALIDATE(m_hSprite);
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(iMask));
	VALIDATE(m_hMask);

	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);

	if (m_eSpriteType == ESprite::BACKGROUND || m_eSpriteType == ESprite::MAINMENU 
		|| m_eSpriteType == ESprite::INSTRUCTIONS || m_eSpriteType == ESprite::LVLCOMP
		|| m_eSpriteType == ESprite::HIGHSCORES)
	{
		m_iW = m_bitmapSprite.bmWidth;
		m_iH = m_bitmapSprite.bmHeight;
	}
    return (true);
}

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

void
CSprite::Process(float _fDeltaTick)
{
	//Sprite doesnt have anything to process but AnimatedSprite does.
}

int
CSprite::GetWidth() const
{
    return m_iW;
}

int
CSprite::GetHeight() const
{
    return m_iH;
}

int 
CSprite::GetX() const
{
    return (m_iX);
}

int 
CSprite::GetY() const
{
    return (m_iY);
}

void 
CSprite::SetX(int _i)
{
    m_iX = _i;
}

void 
CSprite::SetY(int _i)
{
    m_iY = _i;
}

void 
CSprite::TranslateRelative(int _iX, int _iY)
{
    m_iX += _iX;
    m_iY += _iY;
}

void 
CSprite::TranslateAbsolute(int _iX, int _iY)
{
    m_iX = _iX;
    m_iY = _iY;
}
