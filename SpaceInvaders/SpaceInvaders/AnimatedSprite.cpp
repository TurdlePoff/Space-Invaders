#include "AnimatedSprite.h"

CAnimatedSprite::CAnimatedSprite()
	: m_frameSpeed(0)
	, m_frameWidth(0)
	, m_timeElapsed(0)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
	, m_numOfFrames(0)
{

}

CAnimatedSprite::~CAnimatedSprite()
{
}

bool CAnimatedSprite::Initialise(ESprite _eSprite)
{
	m_frameWidth = 0;
	m_frameHeight = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	CSprite::CSprite(_eSprite);

	StartAnimating();

	return (true);
}

void CAnimatedSprite::Draw()
{
	//INITIALISE
}

void CAnimatedSprite::Process(float _fDeltaTick)
{

}

void CAnimatedSprite::AddFrame(int x)
{

}

int CAnimatedSprite::GetFrameSpeed()
{
	return m_frameSpeed;
}

int CAnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

int CAnimatedSprite::GetFrameHeight()
{
	return m_frameHeight;
}

void CAnimatedSprite::SetFrameSpeed(int f)
{
	m_frameSpeed = f;
}

void CAnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

bool CAnimatedSprite::IsAnimating()
{
	return m_animating;
}

void CAnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

/**
* IsLooping - Checks if the animation is currently looping
* - used for enemies when idle
**/
bool CAnimatedSprite::IsLooping()
{
	return m_loop;
}

void CAnimatedSprite::SetLooping(bool b)
{
	m_loop = true;
}

void CAnimatedSprite::Pause()
{
	m_paused = true;
}

bool CAnimatedSprite::IsPaused()
{
	return m_paused;
}
