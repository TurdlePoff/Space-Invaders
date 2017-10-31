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

#if !defined(__MenuNavigator_H__)
#define __MenuNavigator_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes

class CMenuNavigator : public CEntity
{
	// Member Functions
public:
	CMenuNavigator();
	virtual ~CMenuNavigator();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:

private:
	CMenuNavigator(const CMenuNavigator& _kr);
	CMenuNavigator& operator= (const CMenuNavigator& _kr);

	// Member Variables
	bool b_atStart;

public:

protected:

private:

};

#endif    // __MenuNavigator_H__
