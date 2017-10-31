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
//#include <vld.h>

// Local Includes
#include "game.h"
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
	, m_pLevelLogic(0)
{
	m_pLevelLogic = new CLevelLogic();

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

/********
* Initialise: Initialise function for CLevel
*
* parameter
*********/
bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;


	//Background initialisation
	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise(ESprite::BACKGROUND));
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
		pEnemy->Process(1); //need due to timer within enemy movement giving a movement delay therefore giving the impression of a spawn delay
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

	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		m_vecEnemies[i]->Draw();
	}

	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
	{
		m_vecPlayerBullets[j]->Draw();
	}

	for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
	{
		m_vecEnemyBullets[j]->Draw();
	}

	DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{

	m_pBackground->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);
	ProcessPlayerMovement();
	EnemyMovement(_fDeltaTick);

	////TODO: bullet/ball code

	if (GetAsyncKeyState(VK_SPACE) && !m_pPlayer->GetIsShooting())
	{
		FireBullet(true, m_pLevelLogic->GetLVLPlayerBulletSpeed()); //isPlayer = true (player)
		m_pPlayer->SetIsShooting(true);
	}

	//Generate a random number between 0 + 5
	int randTime = rand() % (110 + 90);

	FireBullet(false, m_pLevelLogic->GetLVLEnemyBulletSpeed()); //isPlayer = true (player)

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i)
	{
		m_vecPlayerBullets[i]->Process(_fDeltaTick);
	}

	for (unsigned int i = 0; i < m_vecEnemyBullets.size(); ++i)
	{
		m_vecEnemyBullets[i]->Process(_fDeltaTick);
	}

	ProcessBulletEnemyCollision();
	ProcessBulletPlayerCollision();
	ProcessCheckForWin();
	ProcessBulletBounds();


	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CLevelLogic & CLevel::GetLevelController()
{
	return *m_pLevelLogic;
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
		if (elapsed_secs > m_pLevelLogic->GetLVLEnemyShootingDelay() || elapsed_secs < 0.0f)
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
					//TODO: SET SPRITE DEAD ANIMATION
					if (i > 11)
					{
						m_vecEnemies[i - 11]->SetCanShoot(true);
					}
					//TODO: SET SPRITE DEAD ANIMATION
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
	for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
	{
		//If enemy bullet collides with player entity
		if (m_vecEnemyBullets[j]->IsCollidingWith(*m_pPlayer))
		{
			//Hide enemy, erase bullet, decrease enemy count
			m_pPlayer->SetPlayerAlive(false);
			delete m_vecEnemyBullets[j];
			m_vecEnemyBullets[j] = 0;
			m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + j);

			if (!m_pLevelLogic->GetLVLPlayerInvincibility())
			{
				m_pPlayer->SetPlayerLives(m_pPlayer->GetPlayerLives() - 1);

				if (m_pPlayer->GetPlayerLives() == 0)
				{
					CGame::GetInstance().GameOverLost();
				}
			}
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
		if (m_vecEnemyBullets[j]->GetY() > m_iHeight - 135)
		{
			delete m_vecEnemyBullets[j];
			m_vecEnemyBullets[j] = 0;
			m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + j);
		}
	}
}

void 
CLevel::ProcessPlayerMovement()
{
	float fHalfPlayerW = m_pPlayer->GetWidth()/2.0f; //->GetSpriteType()->GetWidth() / 2.0f;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pPlayer->SetX(m_pPlayer->GetX() + m_pLevelLogic->GetLVLPlayerMovementSpeed());
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pPlayer->SetX(m_pPlayer->GetX() - m_pLevelLogic->GetLVLPlayerMovementSpeed());
	}
	if (m_pPlayer->GetX() - fHalfPlayerW <= 0)
	{
		m_pPlayer->SetX(fHalfPlayerW);
	}
	else if (m_pPlayer->GetX() + m_pPlayer->GetWidth() >= 1000.0f)
	{
		m_pPlayer->SetX(1000.0f - m_pPlayer->GetWidth());
	}
}

void
CLevel::EnemyMovement(float _fDeltaTick)
{
	bool wall = false;
	bool lose = false;

	double elapsed_secs = double(m_cEndEnemyMove - m_cBeginEnemyMove) / CLOCKS_PER_SEC;
	if (elapsed_secs > m_pLevelLogic->GetLVLEnemyMoveDelay() || elapsed_secs < 0.0f)
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
}


void
CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 20;
	const int kiY = 20;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(27, 233, 56));
	line = "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
	m_strScore = "SCORE: ";
	m_strScore += ToString(m_pPlayer->GetPlayerScore());
	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));

	SetTextColor(hdc, RGB(27, 233, 56));
	TextOutA(hdc, 0, m_iHeight - 135, line.c_str(), static_cast<int>(line.size()));

	m_strPlayerLives = "Player Lives: ";
	m_strPlayerLives += ToString(m_pPlayer->GetPlayerLives());
	if (m_pLevelLogic->GetLVLPlayerInvincibility())
	{
		m_strPlayerLives += "                                                                     YOU ARE CURRENTLY INVINCIBLE";
	}
	TextOutA(hdc, 20, m_iHeight - 100, m_strPlayerLives.c_str(), static_cast<int>(m_strPlayerLives.size()));

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
	m_fpsCounter->DrawFPSText(hdc, m_iWidth - 30, m_iHeight - 80);

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

