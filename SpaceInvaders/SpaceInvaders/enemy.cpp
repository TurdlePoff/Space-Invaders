//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "enemy.cpp"
// Description	: Implementation file for Enemy
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

//#include "resource.h"
#include "utils.h"

// This Include
#include "enemy.h"

// Implementation
CEnemy::CEnemy()
: m_bHit(false)
, m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
, m_bCanShoot(false)
, m_bIsDead(false)
, m_bIsShot(false)
{
	srand(static_cast<unsigned int>(time(NULL)));
}

CEnemy::~CEnemy()
{
}

/********************
* CEnemy Initialiser: 
* - Initialises enemy entity with specified sprite, 
* - Sets each enemy with their own individual points
* @parameter: _spriteType - Sprite to be initialised with entity
* @return bool
*********************/
bool
CEnemy::Initialise(ESprite _spriteType)
{
    VALIDATE(CEntity::Initialise(_spriteType));
	int pointArray[6] = {10, 20, 30, 50, 100, 300};
	int randTime = (rand() % (7));
	//Set points depending on which enemy is being created
	switch(_spriteType)
	{
		case ESprite::ENEMYTOP: //Squido
		{
			m_iPoints = 30;
			break;
		}
		case ESprite::ENEMYMED: //Buggo
		{
			m_iPoints = 20;
			break;
		}
		case ESprite::ENEMYBOT: //Octomonsto
		{
			m_iPoints = 10;
			break;
		}
		case ESprite::ENEMYSHIP: //Nyooms
		{
			//Create enemy ship with random point value
			m_iPoints = pointArray[randTime];
			break;
		}
	}

    return (true);
}

/************
* Draw: Calls draw from within entity
*************/
void
CEnemy::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

/************
* Process: Calls process from within entity if enemy is not hit and moves position of enemy with velocities
*************/
void
CEnemy::Process(float _fDeltaTick)
{
	m_fX += m_fVelocityX;
	m_fY += m_fVelocityY;

    if (!m_bHit)
    {
        CEntity::Process(_fDeltaTick);
    }
}

float
CEnemy::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CEnemy::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CEnemy::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}

void
CEnemy::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

void CEnemy::SetCanShoot(bool _b)
{
	m_bCanShoot = _b;
}

bool CEnemy::GetCanShoot()
{
	return m_bCanShoot;
}

void CEnemy::SetDead(bool _b)
{
	m_bIsDead = _b;
}

bool CEnemy::IsDead() const
{
	return m_bIsDead;
}

void CEnemy::SetShot(bool _b)
{
	m_bIsShot = _b;
}

bool CEnemy::IsShot() const
{
	return m_bIsShot;
}

void
CEnemy::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
CEnemy::IsHit() const
{
    return (m_bHit);
}

int CEnemy::GetEnemyPoints()
{
	return m_iPoints;
}
