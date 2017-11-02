//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "bullet.h"
// Description	: Decalaration file for bullet
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#pragma once

#if !defined(__BULLET_H__)
#define __BULLET_H__

// Local Includes
#include "entity.h"

// Prototypes
class CSprite;

class CBullet : public CEntity
{
	public:
		CBullet();
		virtual ~CBullet();

		virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

		virtual void Draw();
		virtual void Process(float _fDeltaTick);

		float GetVelocityX() const;
		float GetVelocityY() const;
		void SetVelocityX(float _fX);
		void SetVelocityY(float _fY);

	protected:
		float m_fVelocityX;
		float m_fVelocityY;

	private:
		CBullet(const CBullet& _kr);
		CBullet& operator= (const CBullet& _kr);

};


#endif    // __BULLET_H__
