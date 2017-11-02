//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "game.cpp"
// Description	: Implemention file for Game
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "utils.h"
#include "BackBuffer.h"
#include "background.h"
#include "player.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;
CLevel* CGame::m_pLevel = 0;
EGameState CGame::m_eGameState = (EGameState::MENU);
bool CGame::m_bIsPaused = false;
bool CGame::m_bLevelComplete = false;

// Implementation
CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, n_bReadyForNextLevel(false)
, m_cBeginLevelBreak(0)
, m_cEndLevelBreak(0)
{
	m_pLogic = new CLevelLogic();
}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pMenu;
	m_pMenu = 0;

	delete m_pMenuNavigator;
	m_pMenuNavigator = 0;

	delete m_pInstructions;
	m_pInstructions = 0;

	delete m_pHighScores;
	m_pHighScores = 0;

	delete m_pLevelComplete;
	m_pLevelComplete = 0;

    delete m_pBackBuffer;
    m_pBackBuffer = 0;

    delete m_pClock;
    m_pClock = 0;
}

/************
* Initialise: Initialises elements that are needed throughout the game
*************/
bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hApplicationInstance = _hInstance;
    m_hMainWindow = _hWnd;

    m_pClock = new CClock();
    VALIDATE(m_pClock ->Initialise());
    m_pClock->Process();

    m_pBackBuffer = new CBackBuffer();
    VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	//Initialise all menu and background items
	if (m_eGameState == EGameState::MENU)
	{
		m_pMenu = new CBackGround();
		VALIDATE(m_pMenu->Initialise(ESprite::MAINMENU));
		m_pMenu->SetX((float)1000 / 2);
		m_pMenu->SetY((float)750 / 2);

		m_pMenuNavigator = new CPlayer();
		VALIDATE(m_pMenuNavigator->Initialise());
		m_pMenuNavigator->SetX(1000 / 2 - 155);
		m_pMenuNavigator->SetY(750 / 2 - 105);

		m_pInstructions = new CBackGround();
		VALIDATE(m_pInstructions->Initialise(ESprite::INSTRUCTIONS));
		m_pInstructions->SetX((float)1000 / 2);
		m_pInstructions->SetY((float)750 / 2);

		m_pHighScores = new CBackGround();
		VALIDATE(m_pHighScores->Initialise(ESprite::HIGHSCORES));
		m_pHighScores->SetX((float)1000 / 2);
		m_pHighScores->SetY((float)750 / 2);
		
		m_pLevelComplete = new CBackGround();
		VALIDATE(m_pLevelComplete->Initialise(ESprite::LVLCOMP));
		m_pLevelComplete->SetX((float)1000 / 2);
		m_pLevelComplete->SetY((float)750 / 2);
	}

	ShowCursor(true);

    return (true);
}

/************
* Draw: Game Draw function draws elements of the current state onto the screen
*************/
void
CGame::Draw()
{
    m_pBackBuffer->Clear();
	// Do all the game’s drawing here...
	if (m_eGameState == EGameState::MENU)
	{
		m_pMenu->Draw();
		m_pMenuNavigator->Draw();
	}
	else if (m_eGameState == EGameState::INSTRUCTIONS)
	{
		m_pInstructions->Draw();
	}
	else if (m_eGameState == EGameState::HIGHSCORES)
	{
		m_pHighScores->Draw();
	}
	else if (m_eGameState == EGameState::GAME)
	{
		m_pLevel->Draw();
		if (n_bReadyForNextLevel)
		{
			m_pLevelComplete->Draw();
		}
	}

    m_pBackBuffer->Present();
}

/************
* Process: Game Processer that deals with elements of the current state should be 
  processed within the game application
*************/
void
CGame::Process(float _fDeltaTick)
{
    // Process all the game’s logic here.
	//Load a new sprite.
	if (m_eGameState == EGameState::MENU)
	{
		m_pMenu->Process(_fDeltaTick);
		m_pMenuNavigator->Process(_fDeltaTick);
		m_pMenuNavigator->SwitchMenuItem(m_eGameState);
		if (m_eGameState == EGameState::GAME)
		{
			m_pLevel = new CLevel(*m_pLogic);
			m_pLevel->Initialise(1000, 800);
			m_pLogic->SetLVLPlayerLives(3);
			m_pLogic->SetLVLLevelCount(1);
			m_pLogic->SetLVLPlayerScore(0);

		}
		else if (m_eGameState == EGameState::INSTRUCTIONS)
		{
			m_pInstructions->Process(_fDeltaTick);
		}
		else if (m_eGameState == EGameState::HIGHSCORES)
		{
			m_pHighScores->Process(_fDeltaTick);
		}
	}
	else if (m_eGameState == EGameState::INSTRUCTIONS || m_eGameState == EGameState::HIGHSCORES)
	{
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN))
		{
			SetGameState(EGameState::MENU);
		}
	}
	else if (m_eGameState == EGameState::GAME)
	{
		m_pLevel->Process(_fDeltaTick);
		
		if (GetLevelComplete())
		{
			m_pLevelComplete->Process(_fDeltaTick);

			SetLevelComplete(false);
			m_cBeginLevelBreak = clock();
			n_bReadyForNextLevel = true;
		}

		double elapsed_secs = double(m_cEndLevelBreak - m_cBeginLevelBreak) / CLOCKS_PER_SEC;

		if (elapsed_secs > 3.0f && n_bReadyForNextLevel)
		{
			SetNextLevel();
		}
		m_cEndLevelBreak = clock();
	}
}

void 
CGame::ExecuteOneFrame()
{
	if (!GetPaused())
	{
		float fDT = m_pClock->GetDeltaTick();

		Process(fDT);
		Draw();

		m_pClock->Process();

		Sleep(1);
	}
}

CGame&
CGame::GetInstance()
{
    if (s_pGame == 0)
    {
        s_pGame = new CGame();
    }

    return (*s_pGame);
}

CLevel&
CGame::GetLevelInstance()
{
	return (*m_pLevel);
}

void 
CGame::DestroyInstance()
{
    delete s_pGame;
    s_pGame = 0;
}


/************
* SetGameState: Sets a game state 
* States: MENU, GAME, INSTRUCTIONS, HIGHSCORES
*************/
void 
CGame::SetGameState(EGameState _state)
{
	m_eGameState = _state;
}

/************
* GetGameState: Getter for game state
* States: MENU, GAME, INSTRUCTIONS, HIGHSCORES
*************/
EGameState CGame::GetGameState()
{
	return m_eGameState;
}

void CGame::SetPaused(bool _b)
{
	m_bIsPaused = _b;
}

bool CGame::GetPaused()
{
	return m_bIsPaused;
}

CBackBuffer* 
CGame::GetBackBuffer()
{
    return (m_pBackBuffer);
}

HINSTANCE 
CGame::GetAppInstance()
{
    return (m_hApplicationInstance);
}

HWND 
CGame::GetWindow()
{
    return (m_hMainWindow);
}

/************
* GameOverWon: Set level as complete which leads to the next level being created
*************/
void
CGame::GameOverWon()
{
	//total enemypoints for each level = 990
	if (!n_bReadyForNextLevel)
	{
		SetLevelComplete(true);
	}
}

/************
* SetLevelComplete: Setter for marking a level as complete or incomplete
*************/
void
CGame::GameOverLost()
{
	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);

	SetGameState(EGameState::MENU);
}

/************
* SetLevelComplete: Setter for marking a level as complete or incomplete
*************/
void 
CGame::SetLevelComplete(bool _b)
{
	m_bLevelComplete = _b;
}

/************
* GetLevelComplete: returns true if level is complete
*************/
bool 
CGame::GetLevelComplete()
{
	return m_bLevelComplete;
}

/************
* SetNextLevel: Deletes current level and recreates another one with new statistics
*************/
void 
CGame::SetNextLevel()
{
	if (n_bReadyForNextLevel)
	{
		delete m_pLevel;
		m_pLevel = 0;

		m_pLevel = new CLevel(*m_pLogic);
		m_pLevel->Initialise(1000, 800);

		//Decrease the movement delay of enemies after each level
		if (m_pLogic->GetLVLRealEnemyDelay() <= 0.5f)
		{
			m_pLogic->SetLVLRealEnemyDelay(m_pLogic->GetLVLRealEnemyDelay() - 0.02f);
		}
		else
		{
			m_pLogic->SetLVLRealEnemyDelay(m_pLogic->GetLVLRealEnemyDelay() - 0.2f);
		}
		//If enemy movement delay code was changed within the debug window, reset to the real speed for the nxt level
		m_pLogic->SetLVLEnemyMoveDelay(m_pLogic->GetLVLRealEnemyDelay());

		//Increase enemy bullet speed after each level 
		m_pLogic->SetLVLEnemyBulletSpeed(m_pLogic->GetLVLEnemyBulletSpeed() + 0.5f);

		//Increase player life count by 1 if level is won
		m_pLogic->SetLVLPlayerLives(m_pLogic->GetLVLPlayerLives() + 1);

		//Increase level count
		m_pLogic->SetLVLLevelCount(m_pLogic->GetLVLLevelCount() + 1);

		n_bReadyForNextLevel = false;
	}
}