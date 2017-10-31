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

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;
CLevel* CGame::m_pLevel = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
, m_gameState(MENU)
{

}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

    delete m_pBackBuffer;
    m_pBackBuffer = 0;

    delete m_pClock;
    m_pClock = 0;
}

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

	if (m_gameState == MENU)
	{

		m_pMenu = new CBackGround();
		VALIDATE(m_pMenu->Initialise(ESprite::MAINMENU));
		m_pMenu->SetX((float)1000 / 2);
		m_pMenu->SetY((float)750 / 2);


	}
	else if (m_gameState == GAME)
	{
		m_pLevel = new CLevel();
		VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));
	}
	

	ShowCursor(true);

    return (true);
}

void
CGame::Draw()
{
    m_pBackBuffer->Clear();
	// Do all the game’s drawing here...
	if (m_gameState == MENU)
	{
		m_pMenu->Draw();

	}
	else if (m_gameState == GAME)
	{
		m_pLevel->Draw();
	}
    m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
    // Process all the game’s logic here.
	//Load a new sprite.
	if (m_gameState == MENU)
	{
		m_pMenu->Process(_fDeltaTick);

	}
	else if (m_gameState == GAME)
	{
		m_pLevel->Process(_fDeltaTick);
	}
}

void 
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

    Process(fDT);
    Draw();

    m_pClock->Process();

    Sleep(1);
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

void
CGame::GameOverWon()
{
	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
CGame::GameOverLost()
{
	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

//void CGame::UpdateLevel(float pSpeed, float pBSpeed, bool pInv, float eSpeed, float eBSpeed, float eMSpeed)
//{
//	CLevel& level = GetLevelInstance();
//	level.SetLVLPlayerBulletSpeed(pBSpeed);
//}

