//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "player.h"
// Description	: Decalaration file for player.
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#if !defined(__PLAYER_H__)
#define __PLAYER_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "EEnums.h"
#include <Windows.h>

//Enum for navigating the menu screen
enum EMenuSelector
{
	STARTMENU, INSTMENU, HSCOREMENU, EXITMENU
};

class CPlayer : public CEntity
{
    // Member Functions
public:
    CPlayer();
    virtual ~CPlayer();

    virtual bool Initialise();
    virtual void Draw();
    virtual void Process(float _fDeltaTick);

	//Player Getter and Setter methods
	void SetPlayerAlive(bool _isAlive);
	bool GetIsPlayerAlive();

	int GetPlayerScore();
	void IncreasePlayerScore(int _points);

	void SetIsShooting(bool _isShooting);
	bool GetIsShooting();

	int GetPlayerLives();
	void SetPlayerLives(int _i);

	//Menu navigation methods
	void SetMenuSwitch(EMenuSelector _mItem);
	EMenuSelector GetMenuSwitch();
	void SwitchMenuItem(EGameState _state);

protected:
	// Member Variables
	int m_iPlayerScore;
	int m_iPlayerLives;
	bool m_bCurrentlyAlive;
	bool m_bIsShooting;
	float m_iPlayerSpeed;
	EMenuSelector m_eMenuItem;

private:
    CPlayer(const CPlayer& _kr);
    CPlayer& operator= (const CPlayer& _kr);

};

#endif    // __PLAYER_H__
