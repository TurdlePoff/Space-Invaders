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
, m_eMenuItem(STARTMENU)
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

void CPlayer::SetMenuSwitch(EMenuSelector _mItem)
{
	m_eMenuItem = _mItem;
	if (m_eMenuItem == STARTMENU)
	{
		SetX(1000 / 2 - 155);
		SetY(750 / 2 - 25);
	}
	else if (m_eMenuItem == INSTMENU)
	{
		SetX(1000 / 2 - 275);
		SetY(750 / 2 + 75);
	}
	else if (m_eMenuItem == EXITMENU)
	{
		SetX(1000 / 2 - 130);
		SetY(750 / 2 + 180);
	}
}

EMenuSelector CPlayer::GetMenuSwitch()
{
	return m_eMenuItem;
}

void CPlayer::SwitchMenuItem(EGameState _state)
{
	if (_state == EGameState::MENU)
	{
		Sleep(90);
		if (GetAsyncKeyState(VK_RETURN))
		{
			if (GetMenuSwitch() == STARTMENU)
			{
				CGame::SetGameState(EGameState::GAME);
			}
			else if(GetMenuSwitch() == INSTMENU)
			{
				CGame::SetGameState(EGameState::INSTRUCTIONS);
			}
			else 
			{
				PostQuitMessage(0);
			}
		}
		else if (GetAsyncKeyState(VK_UP))
		{
			if (GetMenuSwitch() == INSTMENU)
			{
				SetMenuSwitch(STARTMENU);
			}
			else if (GetMenuSwitch() == EXITMENU)
			{
				SetMenuSwitch(INSTMENU);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (GetMenuSwitch() == STARTMENU)
			{
				SetMenuSwitch(INSTMENU);
			}
			else if (GetMenuSwitch() == INSTMENU)
			{
				SetMenuSwitch(EXITMENU);
			}
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			//Get rid of key press stored in game
		}
	}
}