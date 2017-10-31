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

#if !defined(__PLAYER_H__)
#define __PLAYER_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "bullet.h"

// Types

// Constants

// Prototypes

class CPlayer : public CEntity
{
    // Member Functions
public:
    CPlayer();
    virtual ~CPlayer();

    virtual bool Initialise();

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	void SetPlayerAlive(bool _isAlive);
	bool GetIsPlayerAlive();

	int GetPlayerScore();

	void IncreasePlayerScore(int _points);

	void SetIsShooting(bool _isShooting);
	bool GetIsShooting();

	int GetPlayerLives();
	void SetPlayerLives(int _i);

	float GetPlayerSpeed();
	void SetPlayerLivesSpeed(float _i);

	void SetMenuSwitch();
	bool GetMenuSwitch();

protected:

private:
    CPlayer(const CPlayer& _kr);
    CPlayer& operator= (const CPlayer& _kr);

    // Member Variables
	int m_iPlayerScore;
	int m_iPlayerLives;
	bool m_bCurrentlyAlive;
	bool m_bIsShooting;
	float m_iPlayerSpeed;
	bool m_bAtStart;

public:

protected:

private:

};

#endif    // __PLAYER_H__
