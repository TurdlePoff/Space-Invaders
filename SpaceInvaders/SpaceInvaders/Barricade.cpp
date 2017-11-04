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
: m_eBarState(EBarState::HIT1)
, m_bHit(false)
{
	
}


CBarricade::~CBarricade()
{
}

bool CBarricade::Initialise(ESprite _spriteType)
{
	VALIDATE(CEntity::Initialise(_spriteType));

	return true;
}

void CBarricade::Draw()
{
		CEntity::Draw();
}

void CBarricade::Process(float _fDeltaTick)
{
	/*if (!IsBarDead())
	{*/
		CEntity::Process(_fDeltaTick);
	//}
}

void CBarricade::SetBarState(EBarState _e)
{
	m_eBarState = _e;
}

EBarState CBarricade::GetBarState() const
{
	return m_eBarState;
}

bool CBarricade::IsBarDead() const
{
	if (GetBarState() == EBarState::BARDEAD)
	{
		return true;
	}
	return false;
}

void
CBarricade::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CBarricade::IsHit() const
{
	return (m_bHit);
}
