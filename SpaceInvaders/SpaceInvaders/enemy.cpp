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
//#include "resource.h"
#include "utils.h"

// This Include
#include "enemy.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEnemy::CEnemy()
: m_bHit(false)
{

}

CEnemy::~CEnemy()
{

}

bool
CEnemy::Initialise(EEnemy _eType)
{
	switch (_eType)
	{
		case (ENEMYTOP):
		{
			//VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));
			break;
		}
		case (ENEMYMED):
		{
			break;
		}
		case (ENEMYBOT):
		{
			break;
		}
		case (ENEMYSHIP):
		{
			break;
		}
		default:
			break;
	}
	//TODO: ENEMY SPRITES
    //VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

    return (true);
}

void
CEnemy::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void
CEnemy::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
        CEntity::Process(_fDeltaTick);
    }
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