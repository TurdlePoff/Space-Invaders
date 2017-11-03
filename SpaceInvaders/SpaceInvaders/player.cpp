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
* CPlayer Initialiser: Initialises player entity with specified sprite
* @return bool
*********************/
bool
CPlayer::Initialise()
{
	//PLAYER SPRITES INITIALISE-------------------------------------------
    VALIDATE(CEntity::Initialise(ESprite::PLAYER)); 

    return (true);
}

/********************
* Draw: calls draw from within enity
*********************/
void
CPlayer::Draw()
{
    CEntity::Draw();
}

/********************
* Process: calls process from within enity
*********************/
void
CPlayer::Process(float _fDeltaTick)
{
	
	CEntity::Process(_fDeltaTick);
}

/********************
* SetPlayerAlive: Sets whether player is alive or not
* @parameter isAlive - player alive status
*********************/
void 
CPlayer::SetPlayerAlive(bool isAlive)
{
	m_bCurrentlyAlive = isAlive;
}

/********************
* GetIsPlayerAlive: Gets whether player is alive or not
* @return m_bCurrentlyAlive - player alive status
*********************/
bool CPlayer::GetIsPlayerAlive()
{
	return m_bCurrentlyAlive;
}

/********************
* GetPlayerScore: Gets the player's score
* @return m_iPlayerScore - player score
*********************/
int CPlayer::GetPlayerScore()
{
	return m_iPlayerScore;
}

/********************
* IncreasePlayerScore: Increases the player's score
* @parameter m_iPlayerScore - points to add
*********************/
void CPlayer::IncreasePlayerScore(int _points)
{
	m_iPlayerScore += _points;
}

/********************
* SetIsShooting: Sets whether player is shooting or not
* @parameter _isShooting - player shooting
*********************/
void CPlayer::SetIsShooting(bool _isShooting)
{
	m_bIsShooting = _isShooting;
}

/********************
* GetIsShooting: Gets whether player is shooting or not
* @return m_bIsShooting - is player shooting
*********************/
bool CPlayer::GetIsShooting()
{
	return m_bIsShooting;
}

/********************
* GetPlayerLives: Gets player's lives
* @return m_iPlayerLives - players life count
*********************/
int CPlayer::GetPlayerLives()
{
	return m_iPlayerLives;
}

/********************
* SetPlayerLives: Sets player's lives
* @return _i - players life count
*********************/
void CPlayer::SetPlayerLives(int _i)
{
	m_iPlayerLives = _i;
}

/********************
* SetMenuSwitch: Sets menu navigator position on menu screen
* @return _mItem - enum for which item the user is currently on
*********************/
void CPlayer::SetMenuSwitch(EMenuSelector _mItem)
{
	m_eMenuItem = _mItem;
	if (m_eMenuItem == STARTMENU)
	{
		SetX(1000 / 2 - 155);
		SetY(750 / 2 - 105);
	}
	else if (m_eMenuItem == INSTMENU)
	{
		SetX(1000 / 2 - 280);
		SetY(750 / 2 - 5);
	}
	else if (m_eMenuItem == HSCOREMENU)
	{
		SetX(1000 / 2 - 260);
		SetY(750 / 2 + 100);
	}
	else if (m_eMenuItem == EXITMENU)
	{
		SetX(1000 / 2 - 130);
		SetY(750 / 2 + 200);
	}
}

/********************
* GetMenuSwitch: Gets menu item the player is currently on in the menu screen
* @return m_eMenuItem - enum for menu item the user is currently on
*********************/
EMenuSelector CPlayer::GetMenuSwitch()
{
	return m_eMenuItem;
}

/********************
* SwitchMenuItem: Navigates the menu item
* @return _state - state the menu item is currently on
*********************/
void CPlayer::SwitchMenuItem(EGameState _state)
{
	if (_state == EGameState::MENU)
	{
		Sleep(120); //Sleep for a bit before player can click another button (otherwise button will keep moving the navigator)
		if (GetAsyncKeyState(VK_RETURN)) //If enter is pressed...
		{
			if (GetMenuSwitch() == STARTMENU) //When on the START item
			{
				CGame::SetGameState(EGameState::GAME); //Set game state to game
			}
			else if(GetMenuSwitch() == INSTMENU)  //When on the INSTRUCTIONS item
			{
				CGame::SetGameState(EGameState::INSTRUCTIONS); //Set game state to instructions
			}
			else if (GetMenuSwitch() == HSCOREMENU)  //When on the HSCOREMENU item
			{
				CGame::SetGameState(EGameState::HIGHSCORES); //Set game state to high scores
			}
			else 
			{
				PostQuitMessage(0); //When player navigator is on the exit item, exit the application
			}
		}
		else if (GetAsyncKeyState(VK_UP)) //When player presses up when they are on a current menu item,
		{								  //set navigator to move up to next level
			if (GetMenuSwitch() == INSTMENU)
			{
				SetMenuSwitch(STARTMENU);
			}
			else if (GetMenuSwitch() == HSCOREMENU)
			{
				SetMenuSwitch(INSTMENU);
			}
			else if (GetMenuSwitch() == EXITMENU)
			{
				SetMenuSwitch(HSCOREMENU);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) //When player presses down when they are on a current menu item,
		{									//set navigator to move down to next level
			if (GetMenuSwitch() == STARTMENU)
			{
				SetMenuSwitch(INSTMENU);
			}
			else if (GetMenuSwitch() == INSTMENU)
			{
				SetMenuSwitch(HSCOREMENU);
			}
			else if (GetMenuSwitch() == HSCOREMENU)
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