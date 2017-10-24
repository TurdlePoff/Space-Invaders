//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "level.h"
// Description	: Decalaration file for level
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>
#include <ctime>

// Local Includes

// Types

// Constants

// Prototypes
class CBullet;
class CPlayer;
class CEnemy;
class CFPSCounter;
class CBackGround;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPlayer* GetPlayer() const;

    int GetEnemysRemaining() const;

protected:
    void ProcessBulletWallCollision();
	void ProcessPlayerWallCollison();
    void ProcessBulletPlayerCollision();
    void ProcessBulletEnemyCollision();

    void ProcessCheckForWin();

    void ProcessBulletBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

    void SetEnemysRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CPlayer* m_pPlayer;
    std::vector<CEnemy*> m_vecTopEnemys;
	std::vector<CEnemy*> m_vecMidEnemys;
	std::vector<CEnemy*> m_vecBotEnemys;
	std::vector<CBullet*> m_vecBullets;
	clock_t m_cBeginBullet;
	clock_t m_cEndBullet;

	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

    int m_iEnemysRemaining;

    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
