//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: "level.cpp"
// Description	: Implemention file for level
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

// Library Includes
#include <vld.h>

// Local Includes
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
	: m_iEnemysRemaining(0)
	, m_pPlayer(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_fpsCounter(0)
	, m_cBeginBullet(0)
	, m_cEndBullet(0)
	, m_cBeginEnemyMove(0)
	, m_cEndEnemyMove(0)
	, m_fLVLEnemyBulletVelocity(1.0f)
	, m_fLVLPlayerBulletVelocity(6.0f)
	, m_fLVLEnemyShootingDelay(2.0f)
	, m_fLVLEnemySpeed(1.0f)
{
	m_cEndEnemyMove = clock();
	srand((unsigned)time(NULL));
}

CLevel::~CLevel()
{
	while (m_vecEnemies.size() > 0)
	{
		CEnemy* pEnemy = m_vecEnemies[m_vecEnemies.size() - 1];

		m_vecEnemies.pop_back();

		delete pEnemy;
		pEnemy = 0;
	}

	delete m_pPlayer;
	m_pPlayer = 0;

	while (m_vecPlayerBullets.size() > 0)
	{
		CBullet* pBullet = m_vecPlayerBullets[m_vecPlayerBullets.size() - 1];

		m_vecPlayerBullets.pop_back();

		delete pBullet;
		pBullet = 0;
	}

	while (m_vecEnemyBullets.size() > 0)
	{
		CBullet* pEnemyBullet = m_vecEnemyBullets[m_vecEnemyBullets.size() - 1];

		m_vecEnemyBullets.pop_back();

		delete pEnemyBullet;
		pEnemyBullet = 0;
	}

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	//Background initialisation
	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	//Player initialisation
	m_pPlayer = new CPlayer();
	VALIDATE(m_pPlayer->Initialise());
	m_pPlayer->SetX((float)m_iWidth / 2);
	m_pPlayer->SetY((float)m_iHeight - 150.0f);
	m_pPlayer->SetPlayerAlive(true);

	//Enemy initialisation
	const int kiNumEnemys = 55;
	const int kiStartX = 90;
	int kiGap = 10;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX;

	for (int i = 0; i < kiNumEnemys; ++i)
	{
		CEnemy* pEnemy = new CEnemy();
		if (i < 11)
		{
			VALIDATE(pEnemy->Initialise(ESprite::ENEMYTOP));
			kiGap = 28;
		}
		else if (i >= 11 && i < 33)
		{
			VALIDATE(pEnemy->Initialise(ESprite::ENEMYMED));
			kiGap = 16;
		}
		else
		{
			VALIDATE(pEnemy->Initialise(ESprite::ENEMYBOT));
			kiGap = 12;

			if (i >= 44)
			{
				pEnemy->SetCanShoot(true);
			}
		}

		pEnemy->SetX(static_cast<float>(iCurrentX));
		pEnemy->SetY(static_cast<float>(iCurrentY));
		pEnemy->SetVelocityX(20.0f);
		iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;

		if (iCurrentX > 730)
		{
			iCurrentX = kiStartX;
			iCurrentY += 50;
		}

		m_vecEnemies.push_back(pEnemy);
	}

	SetEnemysRemaining(kiNumEnemys);

	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();

	m_pPlayer->Draw();

	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
	{
		m_vecPlayerBullets[j]->Draw();
	}

	for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
	{
		m_vecEnemyBullets[j]->Draw();
	}

	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		m_vecEnemies[i]->Draw();
	}

	DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{

	m_pBackground->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);
	EnemyMovement(_fDeltaTick);

	////TODO: bullet/ball code

	if (GetAsyncKeyState(VK_SPACE) && !m_pPlayer->GetIsShooting())
	{
		FireBullet(true, GetLVLPlayerBulletSpeed()); //isPlayer = true (player)
		m_pPlayer->SetIsShooting(true);
	}

	//Generate a random number between 0 + 5
	int randTime = rand() % (110 + 90);

	FireBullet(false, GetLVLEnemyBulletSpeed()); //isPlayer = true (player)

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i)
	{
		m_vecPlayerBullets[i]->Process(_fDeltaTick);
	}

	for (unsigned int i = 0; i < m_vecEnemyBullets.size(); ++i)
	{
		m_vecEnemyBullets[i]->Process(_fDeltaTick);
	}

	ProcessBulletEnemyCollision();

	ProcessCheckForWin();
	ProcessBulletBounds();


	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

void CLevel::FireBullet(bool isPlayer, float bulletSpeed)
{
	const float fBulletVelX = 0.0f;
	float fBulletVelY = -bulletSpeed;

	if (isPlayer)
	{
		pBullet = new CBullet();

		pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
		pBullet->SetX(m_pPlayer->GetX());
		pBullet->SetY(m_pPlayer->GetY() - 20.0f);
		m_vecPlayerBullets.push_back(pBullet);
	}
	else
	{
		m_cEndBullet = clock();
		double elapsed_secs = double(m_cEndBullet - m_cBeginBullet) / CLOCKS_PER_SEC;
		if (elapsed_secs > GetLVLEnemyShootingDelay() || elapsed_secs < 0.0f)
		{
			int randEnemy = rand() % (55 + 0);

			if (m_vecEnemies[randEnemy]->GetCanShoot() && !m_vecEnemies[randEnemy]->IsHit())
			{
				pBullet = new CBullet();

				fBulletVelY *= -1;
				pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
				pBullet->SetX(m_vecEnemies[randEnemy]->GetX());
				pBullet->SetY(m_vecEnemies[randEnemy]->GetY() + 20.0f);
				m_vecEnemyBullets.push_back(pBullet);
				m_cBeginBullet = clock();

			}
		}
	}
}

CPlayer*
CLevel::GetPlayer() const
{
	return (m_pPlayer);
}

void
CLevel::ProcessBulletEnemyCollision()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
		{
			if (!m_vecEnemies[i]->IsHit())
			{
				//If bullet collides with enemy entity
				if (m_vecPlayerBullets[j]->IsCollidingWith(*m_vecEnemies[i]))
				{
					//Hide enemy, erase bullet, decrease enemy count
					m_vecEnemies[i]->SetHit(true);
					//TODO: SET SPRITE DEAD
					if (i > 11)
					{
						m_vecEnemies[i - 11]->SetCanShoot(true);
					}
					//TODO: SET SPRITE DEAD
					m_pPlayer->IncreasePlayerScore(m_vecEnemies[i]->GetEnemyPoints());

					delete m_vecPlayerBullets[j];
					m_vecPlayerBullets[j] = 0;

					m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
					m_pPlayer->SetIsShooting(false);

					if (m_vecEnemies[i]->GetSpriteType() != ESprite::ENEMYSHIP)
					{
						SetEnemysRemaining(GetEnemysRemaining() - 1);
					}
				}
			}
		}
	}
}


void
CLevel::ProcessBulletPlayerCollision()
{
	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
	{
		//If bullet collides with enemy entity
		if (m_vecPlayerBullets[j]->IsCollidingWith(*m_pPlayer))
		{
			//Hide enemy, erase bullet, decrease enemy count
			m_pPlayer->SetPlayerAlive(false);
			m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);

			/*if (m_pPlayer[i]->m_eSpriteType != ESprite::ENEMYSHIP)
				SetEnemysRemaining(GetEnemysRemaining() - 1);*/
		}
	}
}

void
CLevel::ProcessCheckForWin()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (!m_vecEnemies[i]->IsHit())
		{
			return;
		}
	}

	CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessBulletBounds()
{
	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
	{
		if (m_vecPlayerBullets[j]->GetY() < 0)
		{
			delete m_vecPlayerBullets[j];
			m_vecPlayerBullets[j] = 0;
			m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
			m_pPlayer->SetIsShooting(false);
		}
	}

	for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
	{
		if (m_vecEnemyBullets[j]->GetY() > 135)
		{
			delete m_vecEnemyBullets[j];
			m_vecEnemyBullets[j] = 0;
			m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + j);
		}
	}
}

//void
//CLevel::EnemyMovement(float _fDeltaTick)
//{
//	bool wall = false;
//	bool lose = false;
//	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
//	{
//		m_vecEnemies[i]->Process(_fDeltaTick);
//
//		if ((m_vecEnemies[i]->GetX() + (m_vecEnemies[i]->GetWidth() / 2) >= 1000.0f)
//			|| (m_vecEnemies[i]->GetX() - (m_vecEnemies[i]->GetWidth() / 2) <= 0.0f))
//		{
//			wall = true;
//		}
//
//		if (m_vecEnemies[i]->IsHit() == false)
//		{
//			if (m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= (m_pPlayer->GetY() - (m_pPlayer->GetHeight() / 2))
//				|| m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= m_iHeight-135.0f) //700 = lose line
//			{
//				lose = true;
//			}
//		}
//	}
//
//	if (wall)
//	{
//		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
//		{
//			wall = false;
//			m_vecEnemies[i]->SetY(m_vecEnemies[i]->GetY() + 50); //Increment level down by 50
//			m_vecEnemies[i]->SetVelocityX(m_vecEnemies[i]->GetVelocityX() *-1);
//			m_vecEnemies[i]->Process(_fDeltaTick);
//		}
//	}
//
//	if (lose)
//	{
//		CGame::GetInstance().GameOverLost();
//	}
//}

void
CLevel::EnemyMovement(float _fDeltaTick)
{
	bool wall = false;
	bool lose = false;

	

	double elapsed_secs = double(m_cEndBullet - m_cBeginEnemyMove) / CLOCKS_PER_SEC;
	if (elapsed_secs > GetLVLEnemySpeed() || elapsed_secs < 0.0f)
	{
		m_cBeginEnemyMove = clock();

		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			m_vecEnemies[i]->Process(_fDeltaTick);

			if ((m_vecEnemies[i]->GetX() + (m_vecEnemies[i]->GetWidth() / 2) >= 990.0f)
				|| (m_vecEnemies[i]->GetX() - (m_vecEnemies[i]->GetWidth() / 2) <= 0.0f))
			{
				wall = true;
			}

			if (m_vecEnemies[i]->IsHit() == false) //if alive
			{
				if (m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= (m_pPlayer->GetY() + (m_pPlayer->GetHeight() / 2))
					|| m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= 650.0f) //700 = lose line
				{
					lose = true;
				}
			}
		}
	}

	m_cEndEnemyMove = clock();

	if (wall)
	{
		wall = false;
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			m_vecEnemies[i]->SetY(m_vecEnemies[i]->GetY() + 50); //Increment level down by 50
			m_vecEnemies[i]->SetVelocityX(m_vecEnemies[i]->GetVelocityX() *-1);
			m_vecEnemies[i]->Process(_fDeltaTick);
		}
	}

	if (lose)
	{
		CGame::GetInstance().GameOverLost();
	}
}

int
CLevel::GetEnemysRemaining() const
{
	return (m_iEnemysRemaining);
}

void
CLevel::SetEnemysRemaining(int _i)
{
	m_iEnemysRemaining = _i;
	UpdateScoreText();
}

void CLevel::SetLVLEnemyShootingDelay(float _f)
{
	m_fLVLEnemyShootingDelay = _f;
}

float CLevel::GetLVLEnemyShootingDelay()
{
	return m_fLVLEnemyShootingDelay;
}

void
CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 20;
	const int kiY = 20;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(27, 233, 56));
	std::string line = "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));

	SetTextColor(hdc, RGB(27, 233, 56));
	TextOutA(hdc, 0, m_iHeight - 135, line.c_str(), static_cast<int>(line.size()));

}
void
CLevel::UpdateScoreText()
{
	m_strScore = "SCORE: ";

	m_strScore += ToString(m_pPlayer->GetPlayerScore());

}

void
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	//HFONT font = CreateFont(
	//	0,	 //Height
	//	0,  //Width
	//	0,	 //Rotation
	//	0,	 //Orientation
	//	FW_EXTRALIGHT, //Weight
	//	false, //Italic
	//	false, //Underline
	//	false, //Crossed out
	//	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	//	DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");

	//SelectObject(hdc, font);

	SetTextColor(hdc, RGB(27, 233, 56));
	m_fpsCounter->DrawFPSText(hdc, m_iWidth - 100, m_iHeight - 70);

	//HFONT font2 = CreateFont(
	//	40,	 //Height
	//	15,  //Width
	//	0,	 //Rotation
	//	0,	 //Orientation
	//	FW_EXTRALIGHT, //Weight
	//	false, //Italic
	//	false, //Underline
	//	false, //Crossed out
	//	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	//	DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
	//SelectObject(hdc, font2);

}


void CLevel::SetLVLEnemyBulletSpeed(float _f)
{
	m_fLVLEnemyBulletVelocity = _f;
}

float CLevel::GetLVLEnemyBulletSpeed()
{
	return m_fLVLEnemyBulletVelocity;
}

void CLevel::SetLVLPlayerBulletSpeed(float _f)
{
	m_fLVLPlayerBulletVelocity = _f;
}

float CLevel::GetLVLPlayerBulletSpeed()
{
	return m_fLVLPlayerBulletVelocity;
}

void CLevel::SetLVLEnemySpeed(float _f)
{
	m_fLVLEnemySpeed = _f;
}

float CLevel::GetLVLEnemySpeed()
{
	return m_fLVLEnemySpeed;
}
