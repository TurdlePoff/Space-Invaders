//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__ENEMY_H__)
#define __ENEMY_H__

// Library Includes
#include <ctime>

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CEnemy : public CEntity
{
	// Member Variables
public:
	enum EState
	{
		ACTION1,
		ACTION2,
		DEAD,
	};

protected:
	bool m_bHit;

private:

    // Member Functions
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

    void SetHit(bool _b);
    bool IsHit() const;
	int m_iPoints;
	ESprite m_eSpriteType;

protected:
	float m_fVelocityX;
	float m_fVelocityY;

private:
    CEnemy(const CEnemy& _kr);
    CEnemy& operator= (const CEnemy& _kr);
};


#endif    // __ENEMY_H__

