//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "enemy.h"
// Description	: Decalaration file for Enemy
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#if !defined(__ENEMY_H__)
#define __ENEMY_H__

// Library Includes
#include <ctime>

// Local Includes
#include "entity.h"

class CEnemy : public CEntity
{
public:
    CEnemy();
    virtual ~CEnemy();

    virtual bool Initialise(ESprite _spriteType);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float _fX);
	void SetVelocityY(float _fY);

	void SetCanShoot(bool _b);
	bool GetCanShoot();

	void SetDead(bool _b);
	bool IsDead() const;

	void SetShot(bool _b);
	bool IsShot() const;

    void SetHit(bool _b);
    bool IsHit() const;
	int GetEnemyPoints();

protected:
	bool m_bHit;
	float m_fVelocityX;
	float m_fVelocityY;

private:
    CEnemy(const CEnemy& _kr);
    CEnemy& operator= (const CEnemy& _kr);
	int m_iPoints;
	bool m_bCanShoot;
	bool m_bIsShot;
	bool m_bIsDead;

};


#endif    // __ENEMY_H__

