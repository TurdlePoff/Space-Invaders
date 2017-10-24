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
, m_iX(0)
, m_iY(0)
{
	switch (_eType)
	{
		case ESprite::BACKGROUND:
		{
			m_iW = 400;
			m_iH = 600;
			break;
		}
		case ESprite::BULLET:
		{
			m_iW = 12;
			m_iH = 20;
			break;
		}
		case ESprite::PLAYER:
		{
			m_iW = 52;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYTOP:
		{
			m_iW = 44;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYMED:
		{
			m_iW = 48;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYBOT:
		{
			m_iW = 32;
			m_iH = 32;
			break;
		}
		case ESprite::ENEMYSHIP:
		{
			m_iW = 64;
			m_iH = 44;
			break;
		}
		case ESprite::BARRICADE:
		{
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

	if(m_eSpriteType == ESprite::BACKGROUND)
	{
		iBackground = IDB_BACKGROUND;
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

    return (true);
}

void
CSprite::Draw()
{
	//Sizes of sprites
	int iW = GetWidth();
	int iH = GetHeight();
	//Positions of sprites
	int iX = m_iX;
	int iY = m_iY;

	int iGapX = 4;
	int iGapY = 8;
	switch (m_eSpriteType)
	{
		case ESprite::BACKGROUND:
		{
			iX -= (iW / 2);
			iY -= (iH / 2);
			break;
		}
		case ESprite::PLAYER:
		{
			iW += iGapX;
			iH += iGapY;
			iX -= (iW / 2);
			iY -= (iH / 2);
			break;
		}
		default:
			break;
	}

	

    CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();

    HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCAND);

    SelectObject(s_hSharedSpriteDC, m_hSprite);

    BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, 0, 0, SRCPAINT);

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
