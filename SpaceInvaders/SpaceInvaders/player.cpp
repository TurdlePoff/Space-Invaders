//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: "player.cpp"
// Description	: Implemention file for Player 
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes

// Local Includes
//#include "resource.h"
#include "utils.h"

// This Include
#include "Player.h"
#include "game.h"

// Static Variables

// Static Function Prototypes

// Implementation

/********************
* CPlayer Contructor
*********************/
CPlayer::CPlayer()
: m_iPlayerScore(0)
, m_iPlayerLives(3)
, m_bIsShooting(false)
, m_bAtStart(true)
{

}

/********************
* CPlayer Destructor
*********************/
CPlayer::~CPlayer()
{

}

/********************
* CPlayer Initialiser:
* - Initialises player entity with specified sprite
* @return bool
*********************/
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

float CPlayer::GetPlayerSpeed()
{
	return m_iPlayerSpeed;
}

void CPlayer::SetPlayerLivesSpeed(float _f)
{
	m_iPlayerSpeed = _f;
}

void CPlayer::SetMenuSwitch()
{
	m_bAtStart = !m_bAtStart;
	if (m_bAtStart)
	{
		SetX(1000 / 2 - 110);
		SetY(750 / 2 - 50);
	}
	else
	{
		SetX(1000 / 2 - 100);
		SetY(750 / 2 + 52);
	}
}

bool CPlayer::GetMenuSwitch()
{
	return m_bAtStart;
}

void CPlayer::SwitchMenuItem(EGameState _state)
{
	SHORT keyState = GetKeyState(VK_CAPITAL);
	bool isDown = keyState & 0x8000;

	if (_state == EGameState::MENU)
	{
		if (!isDown)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				if (m_bAtStart)
				{
					CGame::SetGameState(EGameState::GAME);
				}
				else
				{
					PostQuitMessage(0);
				}
			}
			else if (GetAsyncKeyState(VK_UP) || (GetAsyncKeyState(VK_DOWN)))
			{
				SetMenuSwitch();
			}
		}
		
	}
}