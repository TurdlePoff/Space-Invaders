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

#include "Barricade.h"
#include "utils.h"

CBarricade::CBarricade()
: m_eBarState(EBarState::BARUNTOUCHED)
, m_bHit(false)
{
}


CBarricade::~CBarricade()
{
}

/************
* Initialise: Initialises barricade entity
*************/
bool CBarricade::Initialise(ESprite _spriteType)
{
	VALIDATE(CEntity::Initialise(_spriteType));

	return true;
}

/************
* Initialise: Initialises barricade entity
*************/
void CBarricade::Draw()
{
	if (!IsBarDead())
	{
		CEntity::Draw();
	}
}

/************
* Process: Process barricade entity
*************/
void CBarricade::Process(float _fDeltaTick)
{
	if (!IsBarDead())
	{
		CEntity::Process(_fDeltaTick);
	}
}

/************
* SetBarState: sets the state of the given barricade
*************/
void CBarricade::SetBarState(EBarState _e)
{
	m_eBarState = _e;
}

/************
* GetBarState: Get the state of the barricade
*************/
EBarState CBarricade::GetBarState() const
{
	return m_eBarState;
}

/************
* IsBarDead: Checks if barricade is dead
*************/
bool CBarricade::IsBarDead() const
{
	if (GetBarState() == EBarState::BARDEAD)
	{
		return true;
	}
	return false;
}

/************
* SetHit: Sets whether barricade is hit or not
*************/
void
CBarricade::SetHit(bool _b)
{
	m_bHit = _b;
}

/************
* IsHit: returns whether barricade is hit or not
*************/
bool
CBarricade::IsHit() const
{
	return (m_bHit);
}
