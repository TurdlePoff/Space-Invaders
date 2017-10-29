//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
//#include "resource.h"
#include "utils.h"

// This Include
#include "Player.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer()
: m_iPlayerScore(0)
, m_iPlayerLives(3)
, m_bIsShooting(false)
{

}

CPlayer::~CPlayer()
{

}

bool
CPlayer::Initialise()
{
	//PLAYER SPRITES INITIALISE-------------------------------------------
    VALIDATE(CEntity::Initialise(ESprite::PLAYER)); 

    return (true);
}

void
CPlayer::Draw()
{
    CEntity::Draw();
}

void
CPlayer::Process(float _fDeltaTick)
{
    
	float fHalfPlayerW = m_pSprite->GetWidth() / 2.0f;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 2.0f;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 2.0f;
	}
	if (m_fX - fHalfPlayerW <= 0)
	{
		m_fX = fHalfPlayerW;
	}
	else if (m_fX + m_pSprite->GetWidth() >= 1000.0f)
	{
		m_fX = 1000.0f - m_pSprite->GetWidth();
	}
	
	CEntity::Process(_fDeltaTick);
}

void 
CPlayer::SetPlayerAlive(bool isAlive)
{
	m_bCurrentlyAlive = isAlive;
}

bool CPlayer::GetIsPlayerAlive()
{
	return m_bCurrentlyAlive;
}

int CPlayer::GetPlayerScore()
{
	return m_iPlayerScore;
}

void CPlayer::IncreasePlayerScore(int _points)
{
	m_iPlayerScore += _points;
}

void CPlayer::SetIsShooting(bool _isShooting)
{
	m_bIsShooting = _isShooting;
}

bool CPlayer::GetIsShooting()
{
	return m_bIsShooting;
}

int CPlayer::GetPlayerLives()
{
	return m_iPlayerLives;
}

void CPlayer::SetPlayerLives(int _i)
{
	m_iPlayerLives = _i;
}
