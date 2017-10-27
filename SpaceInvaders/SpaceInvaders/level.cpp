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
	}

	delete m_pPlayer;
	m_pPlayer = 0;

	/*delete m_pBullet;
	m_pBullet = 0;*/

	while (m_vecPlayerBullets.size() > 0)
	{
		CBullet* pBullet = m_vecPlayerBullets[m_vecPlayerBullets.size() - 1];

		m_vecPlayerBullets.pop_back();

		delete pBullet;
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
	m_pPlayer->SetY((float)m_iHeight - 100.0f);
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

		}

		pEnemy->SetX(static_cast<float>(iCurrentX));
		pEnemy->SetY(static_cast<float>(iCurrentY));
		pEnemy->SetVelocityX(0.3f);
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
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		m_vecEnemies[i]->Draw();
	}

	m_pPlayer->Draw();

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


	////TODO: bullet/ball code

	if (GetAsyncKeyState(VK_SPACE))
	{
		FireBullet(true, 0.5f); //isPlayer = true (player)
	}

	//Generate a random number between 0 + 5
	int randTime = rand() % (110 + 90);

	FireBullet(false, randTime); //isPlayer = true (player)

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

	EnemyMovement(_fDeltaTick);

	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

void CLevel::FireBullet(bool isPlayer, float timeBetweenShot)
{
	m_cEndBullet = clock();
	double elapsed_secs = double(m_cEndBullet - m_cBeginBullet) / CLOCKS_PER_SEC;
	if (elapsed_secs > timeBetweenShot || elapsed_secs < 0.0f)
	{
		pBullet = new CBullet();
		const float fBulletVelX = 0.0f;
		float fBulletVelY = -1.0f;

		if (isPlayer)
		{
			pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
			pBullet->SetX(m_pPlayer->GetX());
			pBullet->SetY(m_pPlayer->GetY() - 20.0f);
			m_vecPlayerBullets.push_back(pBullet);
		}
		else
		{
			int randEnemy = rand() % (55 + 0);

			fBulletVelY *= -1;
			pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
			pBullet->SetX(m_vecEnemies[randEnemy]->GetX());
			pBullet->SetY(m_vecEnemies[randEnemy]->GetY() + 20.0f);
			m_vecEnemyBullets.push_back(pBullet);
		}
		m_cBeginBullet = clock();
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

					m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
					//if(m_vecEnemies[i]->m_eSpriteType != ESprite::ENEMYSHIP)
					SetEnemysRemaining(GetEnemysRemaining() - 1);
				}
			}
		}
	}
}

//void
//CLevel::ProcessBulletPlayerCollision()
//{
//	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
//	{
//		//If bullet collides with enemy entity
//		if (m_vecPlayerBullets[j]->IsCollidingWith(*m_pPlayer))
//		{
//			//Hide enemy, erase bullet, decrease enemy count
//			m_pPlayer->SetPlayerAlive(false);
//			m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
//			if (m_pPlayer[i]->m_eSpriteType != ESprite::ENEMYSHIP)
//				SetEnemysRemaining(GetEnemysRemaining() - 1);
//		}
//	}
//}

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
			m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
		}
	}

	for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
	{
		if (m_vecEnemyBullets[j]->GetY() > 800)
		{
			m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + j);
		}
	}
}

void
CLevel::EnemyMovement(float _fDeltaTick)
{
	bool wall = false;
	bool lose = false;
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		m_vecEnemies[i]->Process(_fDeltaTick);

		if ((m_vecEnemies[i]->GetX() + (m_vecEnemies[i]->GetWidth() / 2) >= 1000.0f)
			|| (m_vecEnemies[i]->GetX() - (m_vecEnemies[i]->GetWidth() / 2) <= 0.0f))
		{
			wall = true;
		}

		if (m_vecEnemies[i]->IsHit() == false)
		{
			if (m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= (m_pPlayer->GetY() + (m_pPlayer->GetHeight() / 2))
				|| m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= 700.0f) //700 = lose line
			{
				lose = true;
			}
		}
	}

	if (wall)
	{
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			wall = false;
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

void
CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 100;
	const int kiY = m_iHeight - 100;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}
void
CLevel::UpdateScoreText()
{
	m_strScore = "Enemys Remaining: ";

	m_strScore += ToString(GetEnemysRemaining());
}

void
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	SetTextColor(hdc, RGB(255, 255, 255));
	m_fpsCounter->DrawFPSText(hdc, m_iWidth - 100, m_iHeight - 90);
}
