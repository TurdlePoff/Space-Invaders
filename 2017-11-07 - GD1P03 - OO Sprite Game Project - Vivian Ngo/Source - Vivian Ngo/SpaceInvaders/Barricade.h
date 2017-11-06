//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "barricade.h"
// Description	: Decalaration file for barricade
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once
#include "entity.h"
#include "EEnums.h"
class CBarricade : public CEntity
{
public:
	CBarricade();
	virtual ~CBarricade();

	virtual bool Initialise(ESprite _spriteType);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetBarState(EBarState _b);
	EBarState GetBarState() const;
	bool IsBarDead() const;

	void SetHit(bool _b);
	bool IsHit() const;

protected:

private:
	EBarState m_eBarState;
	bool m_bHit;

};

