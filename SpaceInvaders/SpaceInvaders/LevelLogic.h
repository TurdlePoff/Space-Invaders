//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "levellogic.h"
// Description	: Decalaration file for levelogic. 
//				: Class used to control the game variables that need to be shared across levels. 
//				: ('logic' was probably the wrong word to name it woops)
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVELLOGIC_H__)
#define __LEVELLOGIC_H__

#include "enemy.h"

class CLevelLogic
{
public:
	CLevelLogic();
	~CLevelLogic();

	//Enemy Getters and Setters
	void SetLVLEnemyShootingDelay(float _f);
	float GetLVLEnemyShootingDelay();
	void SetLVLEnemyBulletSpeed(float _f);
	float GetLVLEnemyBulletSpeed();
	void SetLVLEnemyMoveDelay(float _f);
	float GetLVLEnemyMoveDelay();

	void SetLVLRealEnemyDelay(float _f);
	float GetLVLRealEnemyDelay();

	void SetLVLEnemyShipSpeed(float _f);
	float GetLVLEnemyShipSpeed();
	void SetLVLShipRandTime(int _f);
	int GetLVLShipRandTime();

	//Player Getters and Setters
	void SetLVLPlayerBulletSpeed(float _f);
	float GetLVLPlayerBulletSpeed();
	void SetLVLPlayerMovementSpeed(float _f);
	float GetLVLPlayerMovementSpeed();
	void SetLVLPlayerInvincibility(bool _b);
	bool GetLVLPlayerInvincibility();

	//Level UI Getters and Setters
	void SetLVLPlayerScore(int _i);
	int GetLVLPlayerScore();
	void SetLVLPlayerLives(int _i);
	int GetLVLPlayerLives();
	void SetLVLLevelCount(int _i);
	int GetLVLLevelCount();

protected:

	//Enemy variables
	float m_fLVLEnemyShootingDelay;
	float m_fLVLEnemyBulletVelocity;
	float m_fLVLEnemyMoveDelay;
	float m_iLVLRealEnemyDelay;
	float m_fLVLEnemyShipSpeed;
	int m_iShipRandTime;

	//Player variables
	float m_fLVLPlayerBulletVelocity;
	float m_fLVLPlayerSpeed;
	bool m_fLVLPlayerInvincibility;

	//Level UI variables
	int m_iLVLPlayerScore;
	int m_iLVLPlayerLives;
	int m_iLVLLevelCount;

private:
	CLevelLogic(const CLevelLogic& _kr);
	CLevelLogic& operator= (const CLevelLogic& _kr);
};

#endif    // __LEVELLOGIC_H__