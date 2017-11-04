//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "Game.h"
// Description	: Declaration file for Game
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <Windows.h>

// Local Includes
#include "clock.h"
#include "level.h"
#include "utils.h"
#include "LevelLogic.h"
#include "EEnums.h"
#include "BackBuffer.h"
#include "background.h"
#include "barricade.h"
#include "player.h"

// Types

// Constants

// Prototypes
class CBackBuffer;

class CGame
{
    // Member Functions
public:
    ~CGame();

    bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

    void Draw();
    void Process(float _fDeltaTick);
    void ExecuteOneFrame();

	void GameOverWon();
	void GameOverLost();

	//static elements
	static void SetGameState(EGameState _state);
	static EGameState GetGameState();
	static EGameState m_eGameState;

	static bool m_bIsPaused;
	static void SetPaused(bool _b);
	static bool GetPaused();

	static bool m_bLevelComplete;
	static void SetLevelComplete(bool _b);
	static bool GetLevelComplete();

	void SetNextLevel();
	bool n_bReadyForNextLevel;

	CBackBuffer* GetBackBuffer();
	HINSTANCE GetAppInstance();
	HWND GetWindow();

    // Singleton Methods
	static CLevel& GetLevelInstance();

    static CGame& GetInstance();
    static void DestroyInstance();

protected:
	//Elements needed for the game
	CClock* m_pClock;
	static CLevel* m_pLevel;
	CLevelLogic* m_pLogic;
	CBackGround* m_pMenu;
	CBackGround* m_pInstructions;
	CBackGround* m_pHighScores;
	CBackGround* m_pLevelComplete;

	CPlayer* m_pMenuNavigator;
	CBackBuffer* m_pBackBuffer;

	clock_t m_cBeginLevelBreak;
	clock_t m_cEndLevelBreak;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	// Singleton Instance
	static CGame* s_pGame;

private:
    CGame();
    CGame(const CGame& _kr);
    CGame& operator= (const CGame& _kr);

};

#endif    // __GAME_H__
