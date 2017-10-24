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
, m_pBullet(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecEnemys.size() > 0)
    {
        CEnemy* pEnemy = m_vecEnemys[m_vecEnemys.size() - 1];

        m_vecEnemys.pop_back();

        delete pEnemy;
    }

    delete m_pPlayer;
    m_pPlayer = 0;

    delete m_pBullet;
    m_pBullet = 0;

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

    const float fBulletVelX = 200.0f;
    const float fBulletVelY = 75.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	//TODO: bullet/ball code
	m_pBullet = new CBullet();
    VALIDATE(m_pBullet->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, fBulletVelX, fBulletVelY));
	m_pBullet->SetX((float)m_iWidth / 2);
	m_pBullet->SetY((float)m_iHeight - 100.0f);

	//TODO: player code

    m_pPlayer = new CPlayer();
    VALIDATE(m_pPlayer->Initialise());
	m_pPlayer->SetX((float)m_iWidth / 2);
	m_pPlayer->SetY((float)m_iHeight - 100.0f);

	/*

    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.

    /*m_pPlayer->SetX(_iWidth / 2.0f);
    m_pPlayer->SetY(_iHeight - ( 1.5f * m_pPlayer->GetHeight()));*/

	//TODO: enemy code


   /* const int kiNumEnemys = 36;
    const int kiStartX = 20;
    const int kiGap = 5;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

    for (int i = 0; i < kiNumEnemys; ++i)
    {
        CEnemy* pEnemy = new CEnemy();
        VALIDATE(pEnemy->Initialise());

        pEnemy->SetX(static_cast<float>(iCurrentX));
        pEnemy->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;

        if (iCurrentX > _iWidth)
        {
            iCurrentX = kiStartX;
            iCurrentY += 20;
        }

        m_vecEnemys.push_back(pEnemy);
    }

    SetEnemysRemaining(kiNumEnemys);*/
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	/*for (unsigned int i = 0; i < m_vecEnemys.size(); ++i)
    {
        m_vecEnemys[i]->Draw();
    }*/

    m_pPlayer->Draw();
    m_pBullet->Draw();

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	m_pBullet->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);
	//ProcessBulletWallCollision();
	////ProcessPlayerWallCollison();
 //   ProcessBulletPlayerCollision();
 //   //ProcessBulletEnemyCollision();

 //   ProcessCheckForWin();
	//ProcessBulletBounds();

 //   for (unsigned int i = 0; i < m_vecEnemys.size(); ++i)
 //   {
 //       m_vecEnemys[i]->Process(_fDeltaTick);
 //   }
	
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPlayer* 
CLevel::GetPlayer() const
{
    return (m_pPlayer);
}

void 
CLevel::ProcessBulletWallCollision()
{
    float fBulletX = m_pBullet->GetX();
    float fBulletY = m_pBullet->GetY();
    float fBulletW = m_pBullet->GetWidth();
    float fBulletH = m_pBullet->GetHeight();

    float fHalfBulletW = fBulletW / 2;
	float fHalfBulletH = fBulletH / 2;

    if (fBulletX < fHalfBulletW) //represents the situation when the ball has hit the left wall
    {
        m_pBullet->SetVelocityX(m_pBullet->GetVelocityX() * -1); //reverse the ball's x velocity
    }
    else if (fBulletX > m_iWidth - fHalfBulletW) //represents the situation when the ball has hit the right wall
    {
        m_pBullet->SetVelocityX(m_pBullet->GetVelocityX() * -1); //reverse the ball's x velocity direction
    }

	if (fBulletY < fHalfBulletH) //represents the situation when the ball has hit the top wall
    {
        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the ball's y velocity
    }

#ifdef CHEAT_BOUNCE_ON_BACK_WALL
	if (fBulletY  > m_iHeight - fHalfBulletH)  //represents the situation when the ball has hit the bottom wall
    {
        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the ball's y velocity
    }
#endif //CHEAT_BOUNCE_ON_BACK_WALL
}




void
CLevel::ProcessBulletPlayerCollision()
{
    float fBulletR = m_pBullet->GetRadius();

    float fBulletX = m_pBullet->GetX();
    float fBulletY = m_pBullet->GetY(); 

    float fPlayerX = m_pPlayer->GetX();
    float fPlayerY = m_pPlayer->GetY();

    float fPlayerH = m_pPlayer->GetHeight();
    float fPlayerW = m_pPlayer->GetWidth();

    if ((fBulletX + fBulletR > fPlayerX - fPlayerW / 2) && //ball.right > paddle.left
        (fBulletX - fBulletR < fPlayerX + fPlayerW / 2) && //ball.left < paddle.right
        (fBulletY + fBulletR > fPlayerY - fPlayerH / 2) && //ball.bottom > paddle.top
        (fBulletY - fBulletR < fPlayerY + fPlayerH / 2))  //ball.top < paddle.bottom
    {
        m_pBullet->SetY((fPlayerY - fPlayerH / 2) - fBulletR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //Reverse ball's Y direction
    }
}

void
CLevel::ProcessBulletEnemyCollision()
{
    for (unsigned int i = 0; i < m_vecEnemys.size(); ++i)
    {
        if (!m_vecEnemys[i]->IsHit())
        {
            float fBulletR = m_pBullet->GetRadius();

            float fBulletX = m_pBullet->GetX();
            float fBulletY = m_pBullet->GetY(); 

            float fEnemyX = m_vecEnemys[i]->GetX();
            float fEnemyY = m_vecEnemys[i]->GetY();

            float fEnemyH = m_vecEnemys[i]->GetHeight();
            float fEnemyW = m_vecEnemys[i]->GetWidth();

            if ((fBulletX + fBulletR > fEnemyX - fEnemyW / 2) &&
                (fBulletX - fBulletR < fEnemyX + fEnemyW / 2) &&
                (fBulletY + fBulletR > fEnemyY - fEnemyH / 2) &&
                (fBulletY - fBulletR < fEnemyY + fEnemyH / 2))
            {
                //Hit the front side of the brick...
                m_pBullet->SetY((fEnemyY + fEnemyH / 2.0f) + fBulletR);
                m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);
                m_vecEnemys[i]->SetHit(true);

                SetEnemysRemaining(GetEnemysRemaining() - 1);
            }
        }
    }
}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecEnemys.size(); ++i)
    {
        if (!m_vecEnemys[i]->IsHit())
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
	if (m_pBullet->GetX() < 0)
    {
        m_pBullet->SetX(0);
    }
	else if (m_pBullet->GetX() > m_iWidth)
    {
        m_pBullet->SetX(static_cast<float>(m_iWidth));
    }

    if (m_pBullet->GetY() < 0)
    {
        m_pBullet->SetY(0.0f);
    }
    else if (m_pBullet->GetY() > m_iHeight)
    {

		//LOST

        //CGame::GetInstance().GameOverLost();
        //m_pBullet->SetY(static_cast<float>(m_iHeight));
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

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
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

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}
