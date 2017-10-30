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

	void SetLVLEnemyShootingDelay(float _f);
	float GetLVLEnemyShootingDelay();
	void SetLVLEnemyBulletSpeed(float _f);
	float GetLVLEnemyBulletSpeed();
	void SetLVLEnemyMoveDelay(float _f);
	float GetLVLEnemyMoveDelay();

	void SetLVLPlayerBulletSpeed(float _f);
	float GetLVLPlayerBulletSpeed();
	void SetLVLPlayerMovementSpeed(float _f);
	float GetLVLPlayerMovementSpeed();
	void SetLVLPlayerInvincibility(bool _b);
	bool GetLVLPlayerInvincibility();

protected:
    void ProcessBulletEnemyCollision();
	void ProcessBulletPlayerCollision();

    void ProcessCheckForWin();

    void ProcessBulletBounds();

	void FireBullet(bool isPlayer, float bulletSpeed);

    void DrawScore();
	void DrawFPS();

	void ProcessPlayerMovement();
	void EnemyMovement(float _fDeltaTick);

    void SetEnemysRemaining(int _i);



	CPlayer* GetPlayer() const;

	int GetEnemysRemaining() const;

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CPlayer* m_pPlayer;
	CBullet* pBullet;

    std::vector<CEnemy*> m_vecEnemies;
	std::vector<CBullet*> m_vecEnemyBullets;
	std::vector<CBullet*> m_vecPlayerBullets;

	clock_t m_cBeginBullet;
	clock_t m_cEndBullet;

	clock_t m_cBeginEnemyMove;
	clock_t m_cEndEnemyMove;

	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

	float m_fLVLEnemyShootingDelay;
	float m_fLVLEnemyBulletVelocity;
	float m_fLVLEnemyMoveDelay;

	float m_fLVLPlayerBulletVelocity;
	float m_fLVLPlayerSpeed;
	bool m_fLVLPlayerInvincibility;

	int m_iEnemyContainerPosX;
	int m_iEnemyContainerPosY;
	int m_iEnemyContainerWidth;
	int m_iEnemyContainerHeight;


    int m_iEnemysRemaining;

	std::string line;
    std::string m_strScore;
	std::string m_strPlayerLives;

private:

};

#endif    // __LEVEL_H__
