//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "bullet.cpp"
// Description	: Implementation file for bullet
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "utils.h"

// This Includes
#include "Bullet.h"

// Implementation
CBullet::CBullet()
: m_fVelocityX(0.0f)
, m_fVelocityY(0.0f)
{
}

CBullet::~CBullet()
{
}

/************
* Initialise: Initialises bullet preferences
* @parameter: _fPosX - X Position of bullet
* @parameter: _fPosY - Y Position of bullet
* @parameter: _fVelocityX - X Velocity of bullet
* @parameter: _fVelocityY - Y Velocity of bullet
*************/
bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
	//BulletSprites
    VALIDATE(CEntity::Initialise(ESprite::BULLET));

	//Set initial positions
	m_fX = _fPosX;
    m_fY = _fPosY;

	//Set initial speeds
    m_fVelocityX = _fVelocityX;
    m_fVelocityY = _fVelocityY;

    return (true);
}

/************
* Draw: Calls draw from within entity
*************/
void
CBullet::Draw()
{
    CEntity::Draw();
}

/************
* Process: Calls process from within entity amd sets velocities to start where the bullet position is
*************/
void
CBullet::Process(float _fDeltaTick)
{
    m_fX += m_fVelocityX;
    m_fY += m_fVelocityY;

    CEntity::Process(_fDeltaTick);
}

/************
* GetVelocityX: Getter for velocityX
* @return: float of velocityX
*************/
float 
CBullet::GetVelocityX() const
{
    return (m_fVelocityX);
}

/************
* GetVelocityX: Getter for velocityY
* @return: float of velocityY
*************/
float 
CBullet::GetVelocityY() const
{
    return (m_fVelocityY);
}

/************
* SetVelocityX: Setter for velocityX
*************/
void 
CBullet::SetVelocityX(float _fX)
{
    m_fVelocityX = _fX;
}

/************
* SetVelocityY: Setter for velocityY
*************/
void 
CBullet::SetVelocityY(float _fY)
{
    m_fVelocityY = _fY;
}
