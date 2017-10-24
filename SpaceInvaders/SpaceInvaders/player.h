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

protected:

private:
    CPlayer(const CPlayer& _kr);
    CPlayer& operator= (const CPlayer& _kr);

    // Member Variables
	CBullet* m_pBullet;

public:

protected:

private:

};

#endif    // __PLAYER_H__
