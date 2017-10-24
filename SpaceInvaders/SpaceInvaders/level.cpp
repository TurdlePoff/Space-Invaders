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
{

}

CLevel::~CLevel()
{
    while (m_vecTopEnemys.size() > 0)
    {
        CEnemy* pEnemy = m_vecTopEnemys[m_vecTopEnemys.size() - 1];

		m_vecTopEnemys.pop_back();

        delete pEnemy;
    }

    delete m_pPlayer;
    m_pPlayer = 0;

    /*delete m_pBullet;
    m_pBullet = 0;*/

	while (m_vecBullets.size() > 0)
	{
		CBullet* pBullet = m_vecBullets[m_vecBullets.size() - 1];

		m_vecBullets.pop_back();

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

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	//m_pBullet = new CBullet();
 //   VALIDATE(m_pBullet->Initialise(m_iWidth, m_iHeight, fBulletVelX, fBulletVelY));
	//m_pBullet->SetX((float)m_iWidth / 2);
	//m_pBullet->SetY((float)m_iHeight - 200.0f);

	//TODO: player code
    m_pPlayer = new CPlayer();
    VALIDATE(m_pPlayer->Initialise());
	m_pPlayer->SetX((float)m_iWidth / 2);
	m_pPlayer->SetY((float)m_iHeight - 100.0f);

	//TODO: enemy code
    const int kiNumEnemys = 11;
    const int kiStartX = 100;
    const int kiGap = 10;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

    for (int i = 0; i < kiNumEnemys; ++i)
    {
        CEnemy* pEnemy = new CEnemy();
        VALIDATE(pEnemy->Initialise(ESprite::ENEMYMED));

        pEnemy->SetX(static_cast<float>(iCurrentX));
        pEnemy->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;

        if (iCurrentX > _iWidth)
        {
            iCurrentX = kiStartX;
            iCurrentY += 20;
        }

		m_vecTopEnemys.push_back(pEnemy);
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
	for (unsigned int i = 0; i < m_vecTopEnemys.size(); ++i)
    {
		m_vecTopEnemys[i]->Draw();
    }

    m_pPlayer->Draw();

	for (unsigned int j = 0; j < m_vecBullets.size(); ++j)
	{
		m_vecBullets[j]->Draw();
	}

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{

	m_pBackground->Process(_fDeltaTick);
	//m_pBullet->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);


	////TODO: bullet/ball code
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_cEndBullet = clock();
		double elapsed_secs = double(m_cEndBullet - m_cBeginBullet) / CLOCKS_PER_SEC;
		if (elapsed_secs > 0.4f || elapsed_secs < 0.0f)
		{
			CBullet* pBullet = new CBullet();
			const float fBulletVelX = 0.0f;
			const float fBulletVelY = -1.0f;

			pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
			pBullet->SetX(m_pPlayer->GetX());
			pBullet->SetY(m_pPlayer->GetY() - 20.0f);

			m_vecBullets.push_back(pBullet);
			m_cBeginBullet = clock();
		}
	}


	for (unsigned int i = 0; i < m_vecBullets.size(); ++i)
	{
		m_vecBullets[i]->Process(_fDeltaTick);
	}
	//ProcessBulletWallCollision();
	////ProcessPlayerWallCollison();
 //   ProcessBulletPlayerCollision();
 //   ProcessBulletEnemyCollision();

    //ProcessCheckForWin();
	ProcessBulletBounds();

    for (unsigned int i = 0; i < m_vecTopEnemys.size(); ++i)
    {
		m_vecTopEnemys[i]->Process(_fDeltaTick);
    }
	
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPlayer* 
CLevel::GetPlayer() const
{
    return (m_pPlayer);
}

//void 
//CLevel::ProcessBulletWallCollision()
//{
//    float fBulletX = m_pBullet->GetX();
//    float fBulletY = m_pBullet->GetY();
//    float fBulletW = m_pBullet->GetWidth();
//    float fBulletH = m_pBullet->GetHeight();
//
//    float fHalfBulletW = fBulletW / 2;
//	float fHalfBulletH = fBulletH / 2;
//
//    if (fBulletX < fHalfBulletW) //represents the situation when the ball has hit the left wall
//    {
//        m_pBullet->SetVelocityX(m_pBullet->GetVelocityX() * -1); //reverse the ball's x velocity
//    }
//    else if (fBulletX > m_iWidth - fHalfBulletW) //represents the situation when the ball has hit the right wall
//    {
//        m_pBullet->SetVelocityX(m_pBullet->GetVelocityX() * -1); //reverse the ball's x velocity direction
//    }
//
//	if (fBulletY < fHalfBulletH) //represents the situation when the ball has hit the top wall
//    {
//        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the ball's y velocity
//    }
//
//#ifdef CHEAT_BOUNCE_ON_BACK_WALL
//	if (fBulletY  > m_iHeight - fHalfBulletH)  //represents the situation when the ball has hit the bottom wall
//    {
//        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the ball's y velocity
//    }
//#endif //CHEAT_BOUNCE_ON_BACK_WALL
//}

//void
//CLevel::ProcessBulletPlayerCollision()
//{
//    float fBulletR = m_pBullet->GetRadius();
//
//    float fBulletX = m_pBullet->GetX();
//    float fBulletY = m_pBullet->GetY(); 
//
//    float fPlayerX = m_pPlayer->GetX();
//    float fPlayerY = m_pPlayer->GetY();
//
//    float fPlayerH = m_pPlayer->GetHeight();
//    float fPlayerW = m_pPlayer->GetWidth();
//
//    if ((fBulletX + fBulletR > fPlayerX - fPlayerW / 2) && //ball.right > paddle.left
//        (fBulletX - fBulletR < fPlayerX + fPlayerW / 2) && //ball.left < paddle.right
//        (fBulletY + fBulletR > fPlayerY - fPlayerH / 2) && //ball.bottom > paddle.top
//        (fBulletY - fBulletR < fPlayerY + fPlayerH / 2))  //ball.top < paddle.bottom
//    {
//        m_pBullet->SetY((fPlayerY - fPlayerH / 2) - fBulletR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
//        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //Reverse ball's Y direction
//    }
//}

void
CLevel::ProcessBulletEnemyCollision()
{
    for (unsigned int i = 0; i < m_vecTopEnemys.size(); ++i)
    {
		for (unsigned int j = 0; j < m_vecBullets.size(); ++j)
		{
			if (!m_vecTopEnemys[i]->IsHit())
			{
				float fBulletR = m_vecBullets[j]->GetRadius();

				float fBulletX = m_vecBullets[j]->GetX();
				float fBulletY = m_vecBullets[j]->GetY();

				float fEnemyX = m_vecTopEnemys[i]->GetX();
				float fEnemyY = m_vecTopEnemys[i]->GetY();

				float fEnemyH = m_vecTopEnemys[i]->GetHeight();
				float fEnemyW = m_vecTopEnemys[i]->GetWidth();

				if ((fBulletX + fBulletR > fEnemyX - fEnemyW / 2) &&
					(fBulletX - fBulletR < fEnemyX + fEnemyW / 2) &&
					(fBulletY + fBulletR > fEnemyY - fEnemyH / 2) &&
					(fBulletY - fBulletR < fEnemyY + fEnemyH / 2))
				{
					//Hit the front side of the brick...
					//TODO: FIX BULLET ENEMY COLLISION
					m_vecTopEnemys[i]->SetHit(true);

					SetEnemysRemaining(GetEnemysRemaining() - 1);
				}
			}
        }
    }
}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecTopEnemys.size(); ++i)
    {
        if (!m_vecTopEnemys[i]->IsHit())
        {
            return;
        }
    }

	//GAME WON
    //CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessBulletBounds()
{
	for (unsigned int j = 0; j < m_vecBullets.size(); ++j)
	{
		if (m_vecBullets[j]->GetY() < 0)
		{
  			m_vecBullets.erase(m_vecBullets.begin()+j);
		}
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
	//m_iWidth - 100, 
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
	m_fpsCounter->DrawFPSText(hdc, m_iWidth-100, m_iHeight-100);

}
