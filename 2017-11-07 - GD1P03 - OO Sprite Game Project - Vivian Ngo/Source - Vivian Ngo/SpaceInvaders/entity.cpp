//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: "entity.cpp"
// Description	: Implementation file for entity
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "Sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Implementation
CEntity::CEntity()
: m_fX(0.0f)
, m_fY(0.0f)
{
}

CEntity::~CEntity()
{
    delete m_pSprite;
    m_pSprite = 0;
}

/********************
* CEntity Initialiser: Initialises entity with specified sprite,
* @parameter: _spriteType - Sprite to be initialised with entity
* @return bool
*********************/
bool
CEntity::Initialise(ESprite _eType)
{

	m_eSpriteType = _eType;
	m_pSprite = new CSprite(m_eSpriteType);
	//SetSpriteType(_eType);
    VALIDATE(m_pSprite->Initialise());

    return (true);
}

/************
* Draw: Calls the sprite's draw function
*************/
void
CEntity::Draw()
{
    m_pSprite->Draw();
}

/************
* Process: Calls the sprite's process function
*************/
void
CEntity::Process(float _fDeltaTick)
{
    m_pSprite->SetX(static_cast<int>(m_fX));
    m_pSprite->SetY(static_cast<int>(m_fY));
    m_pSprite->Process(_fDeltaTick);
}

/************
* IsCollidingWith: Checks if the current entity is colliding with another
* @parameter: e - Entity to check collision with
* @return true if entities are colliding
*************/
bool CEntity::IsCollidingWith(CEntity& e)
{
	bool colliding = false;

	int e1 = m_pSprite->GetHeight() / 2;
	int e1X = m_pSprite->GetX();
	int e1Y = m_pSprite->GetY();

	int e2 = e.m_pSprite->GetHeight() / 2;
	int e2X = e.m_pSprite->GetX();
	int e2Y = e.m_pSprite->GetY();

	int collision = e1 + e2;
	int actualdistance = static_cast<int>(sqrt(pow((e2X - e1X), 2) + pow((e2Y - e1Y), 2)));

	if (actualdistance < collision)
	{
		colliding = true;
	}

	return colliding;
}

/************
* GetSpriteType: Gets the sprite type of the current entity
* @return m_eSpriteType - sprite type
*************/
ESprite CEntity::GetSpriteType()
{
	return m_eSpriteType;
}

/************
* SwitchOnAnimation: Switches on the Animation
*************/
void CEntity::SwitchOnAnimation(bool _b)
{
	m_pSprite->ActivateAnimation(_b);
}

/************
* SwitchDead: Switches player sprite to dead sprite
*************/
void CEntity::SwitchDead(bool _b)
{
	m_pSprite->ActivateDeadAnimation(_b);
}

/************
* GetIsDead: Checks of sprite is a dead sprite
*************/
bool CEntity::GetIsDead()
{
	return m_pSprite->GetIsDead();
}

/************
* ChangeBarricadeSprite: Changes the state of the barricade sprite
*************/
void CEntity::ChangeBarricadeSprite()
{
	m_pSprite->ChangeBarricade();
}

/************
* GetX: Gets the X position of the entity
* @return m_fX - entity x position
*************/
float 
CEntity::GetX() const
{
    return (m_fX);
}

/************
* GetY: Gets the Y position of the entity
* @return m_fY - entity Y position
*************/
float 
CEntity::GetY() const
{
    return (m_fY);
}

/************
* GetX: Gets the width of the entity/sprite
* @return m_pSprite->GetWidth() - width of sprite
*************/
float 
CEntity::GetWidth() const
{
    return (static_cast<float>(m_pSprite->GetWidth()));
}

/************
* GetX: Gets the height of the entity/sprite
* @return m_pSprite->GetHeight() - height of sprite
*************/
float 
CEntity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

/************
* SetHeight: Sets the height of the entity
* @parameter: _f - the height of the entity
*************/
void
CEntity::SetHeight(float _f)
{
	m_fY += _f;
}

/************
* SetWidth: Sets the width of the entity
* @parameter: _f - Sets the width of the entity
*************/
void CEntity::SetWidth(float _f)
{
	m_fX += _f;
}

/************
* SetX: Sets the X position of the entity
* @parameter: _f - the X position of the entity
*************/
void
CEntity::SetX(float _f)
{
    m_fX = _f;
}

/************
* SetY: Sets the Y position of the entity
* @parameter: _f - the Y position of the entity
*************/
void
CEntity::SetY(float _f)
{
    m_fY = _f;
}