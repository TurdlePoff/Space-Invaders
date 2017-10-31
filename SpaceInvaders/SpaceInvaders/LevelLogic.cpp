#include "LevelLogic.h"

CLevelLogic::CLevelLogic()
: m_fLVLEnemyBulletVelocity(1.0f)
, m_fLVLPlayerBulletVelocity(6.0f)
, m_fLVLEnemyShootingDelay(2.0f)
, m_fLVLEnemyMoveDelay(1.0f)
, m_fLVLPlayerSpeed(4.0f)
, m_fLVLPlayerInvincibility(false)
, m_fLVLEnemyShipSpeed(2.0f)
, m_iShipRandTime(0)
{

}

CLevelLogic::~CLevelLogic()
{
}

void CLevelLogic::SetLVLEnemyBulletSpeed(float _f)
{
	m_fLVLEnemyBulletVelocity = _f;
}

float CLevelLogic::GetLVLEnemyBulletSpeed()
{
	return m_fLVLEnemyBulletVelocity;
}

void CLevelLogic::SetLVLPlayerBulletSpeed(float _f)
{
	m_fLVLPlayerBulletVelocity = _f;
}

float CLevelLogic::GetLVLPlayerBulletSpeed()
{
	return m_fLVLPlayerBulletVelocity;
}

void CLevelLogic::SetLVLPlayerMovementSpeed(float _f)
{
	m_fLVLPlayerSpeed = _f;
}

float CLevelLogic::GetLVLPlayerMovementSpeed()
{
	return m_fLVLPlayerSpeed;
}

void CLevelLogic::SetLVLPlayerInvincibility(bool _b)
{
	m_fLVLPlayerInvincibility = _b;
}

bool CLevelLogic::GetLVLPlayerInvincibility()
{
	return m_fLVLPlayerInvincibility;
}

void CLevelLogic::SetLVLEnemyMoveDelay(float _f)
{
	m_fLVLEnemyMoveDelay = _f;
}

float CLevelLogic::GetLVLEnemyMoveDelay()
{
	return m_fLVLEnemyMoveDelay;
}

void CLevelLogic::SetLVLEnemyShipSpeed(float _f)
{
	m_fLVLEnemyShipSpeed = _f;
}

float CLevelLogic::GetLVLEnemyShipSpeed()
{
	return m_fLVLEnemyShipSpeed;
}

void CLevelLogic::SetLVLShipRandTime(float _f)
{
	m_iShipRandTime = _f;
}

float CLevelLogic::GetLVLShipRandTime()
{
	return m_iShipRandTime;
}

void CLevelLogic::SetLVLEnemyShootingDelay(float _f)
{
	m_fLVLEnemyShootingDelay = _f;
}

float CLevelLogic::GetLVLEnemyShootingDelay()
{
	return m_fLVLEnemyShootingDelay;
}