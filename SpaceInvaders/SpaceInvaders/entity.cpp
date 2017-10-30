//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
//TODO: inclResource
#include "resource.h"
#include "Sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Static Variables

// Static Function Prototypes

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

bool
CEntity::Initialise(ESprite _eType)
{
	SetSpriteType(_eType);
    VALIDATE(m_pSprite->Initialise());

    return (true);
}

void
CEntity::Draw()
{
    m_pSprite->Draw();
}

void
CEntity::Process(float _fDeltaTick)
{
    m_pSprite->SetX(static_cast<int>(m_fX));
    m_pSprite->SetY(static_cast<int>(m_fY));

    m_pSprite->Process(_fDeltaTick);
}

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

ESprite CEntity::GetSpriteType()
{
	return m_eSpriteType;
}

void CEntity::SetSpriteType(ESprite _e)
{
	m_eSpriteType = _e;
	if (m_pSprite != NULL)
	{
		/*delete m_pSprite;
		m_pSprite = 0;*/
	}
	m_pSprite = new CSprite(m_eSpriteType);
	m_pSprite->Initialise();
}

float 
CEntity::GetX() const
{
    return (m_fX);
}

float 
CEntity::GetY() const
{
    return (m_fY);
}

float 
CEntity::GetWidth() const
{
    return (static_cast<float>(m_pSprite->GetWidth()));
}

float 
CEntity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

void
CEntity::SetHeight(float _f)
{
	m_fY = _f;
}

void CEntity::SetWidth(float _f)
{
	m_fX = _f;
}

void
CEntity::SetX(float _f)
{
    m_fX = _f;
}

void
CEntity::SetY(float _f)
{
    m_fY = _f;
}
