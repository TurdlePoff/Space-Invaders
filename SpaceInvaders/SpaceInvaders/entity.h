//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: "entity.h"
// Description	: Declaration file for entity
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//


#pragma once

#if !defined(__ENTITY_H__)
#define __ENTITY_H__

// Library Includes

// Local Includes
#include "EEnums.h"
// Types

// Constants

// Prototypes
class CSprite;

class CEntity
{
public:
	CEntity();
	virtual ~CEntity();

	virtual bool Initialise(ESprite enemyType);

	virtual void Draw() = 0;
	virtual void Process(float _fDeltaTick);

	void SetX(float _f);
	void SetY(float _f);

	float GetX() const;
	float GetY() const;

	void SetHeight(float _f);
	void SetWidth(float _f);

	float GetHeight() const;
	float GetWidth() const;

	bool IsCollidingWith(CEntity& e);
	ESprite GetSpriteType();
	void SetSpriteType(ESprite m_eSpriteType);
	//void SetSpritePic(ESprite m_eSpriteType);
	void SwitchOnAnimation(bool _b);
	void SwitchDead(bool _b);
	bool GetIsDead();

protected:
	CSprite* m_pSprite;

	float m_fX;
	float m_fY;
	float m_fWidth;
	float m_fHeight;

private:
	CEntity(const CEntity& _kr);
	CEntity& operator= (const CEntity& _kr);
	ESprite m_eSpriteType;

};


#endif    // __ENTITY_H__
