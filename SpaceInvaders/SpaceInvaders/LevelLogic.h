#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "levellogic.h"
// Description	: Decalaration file for levelogic
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVELLOGIC_H__)
#define __LEVELLOGIC_H__

class CLevelLogic
{
	

public:
	CLevelLogic();
	~CLevelLogic();

	void SetLVLEnemyShootingDelay(float _f);
	float GetLVLEnemyShootingDelay();
	void SetLVLEnemyBulletSpeed(float _f);
	float GetLVLEnemyBulletSpeed();
	void SetLVLEnemyMoveDelay(float _f);
	float GetLVLEnemyMoveDelay();

	void SetLVLEnemyShipSpeed(float _f);
	float GetLVLEnemyShipSpeed();
	void SetLVLShipRandTime(float _f);
	float GetLVLShipRandTime();

	void SetLVLPlayerBulletSpeed(float _f);
	float GetLVLPlayerBulletSpeed();
	void SetLVLPlayerMovementSpeed(float _f);
	float GetLVLPlayerMovementSpeed();
	void SetLVLPlayerInvincibility(bool _b);
	bool GetLVLPlayerInvincibility();

protected:
	float m_fLVLEnemyShootingDelay;
	float m_fLVLEnemyBulletVelocity;
	float m_fLVLEnemyMoveDelay;

	float m_fLVLEnemyShipSpeed;
	int m_iShipRandTime;

	float m_fLVLPlayerBulletVelocity;
	float m_fLVLPlayerSpeed;
	bool m_fLVLPlayerInvincibility;

private:
	CLevelLogic(const CLevelLogic& _kr);
	CLevelLogic& operator= (const CLevelLogic& _kr);
};

#endif    // __LEVELLOGIC_H__