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
std::vector<CBarricade*> CLevel::m_vecBarricades;

CLevel::CLevel(CLevelLogic& _logic)
//Predefine level properties
: m_pEnemyShip(0)
, m_pPlayer(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
, m_iEnemysRemaining(0)
, m_iRandShipDirection(1)
//Predefine clocks
, m_cBeginBullet(0)
, m_cEndBullet(0)
, m_cBeginEnemyMove(0)
, m_cEndEnemyMove(0)
, m_cBeginShipMove(0)
, m_cEndShipMove(0)
, m_cEndPlayerDead(0)
, m_cBeginPlayerDead(0)
//, m_cBeginEnemyDead(0)
//, m_cEndEnemyDead(0)
{
	m_pLevelLogic = &_logic;
	m_pLevelLogic->SetLVLEnemyMoveDelay(m_pLevelLogic->GetLVLRealEnemyDelay());
	srand((unsigned)time(NULL));
}

//CLevel::CLevel()
//{
//	/*m_pLevelLogic = new CLevelLogic();
//	m_cEndShipMove = clock();
//
//	m_cEndEnemyMove = clock();
//	srand((unsigned)time(NULL));*/
//}

CLevel::~CLevel()
{
	while (m_vecEnemies.size() > 0)
	{
		CEnemy* pEnemy = m_vecEnemies[m_vecEnemies.size() - 1];

		m_vecEnemies.pop_back();

		delete pEnemy;
		pEnemy = 0;
	}

	/*while (m_vecBarricades.size() > 0)
	{
		CBarricade* m_pBarricade = m_vecBarricades[m_vecBarricades.size() - 1];

		m_vecBarricades.pop_back();

		delete m_pBarricade;
		m_pBarricade = 0;
	}*/
	
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pEnemyShip;
	m_pEnemyShip = 0;

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

	//Set different sprites depending on each level of initialisation
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
				pEnemy->SetCanShoot(true); //Only allow enemies at the latest level to shoot (when an enemy infront has been shot, the enemy behind can start shooting)
			}
		}

		//Set up enemy settings
		pEnemy->SetX(static_cast<float>(iCurrentX));
		pEnemy->SetY(static_cast<float>(iCurrentY));
		pEnemy->SetVelocityX(20.0f);
		pEnemy->Process(1); //need due to timer within enemy movement giving a movement delay therefore giving the impression of a spawn delay
		iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;

		if (iCurrentX > 730) //Set up enemy positions
		{
			iCurrentX = kiStartX;
			iCurrentY += 50;
		}

		pEnemy->SwitchOnAnimation(true); //Switch on animation for enemies
		m_vecEnemies.push_back(pEnemy); //Add enemy to vector
	}
	if (m_vecBarricades.size() == 0)
	{
		m_vecBarricades = InitialiseBarricades(m_vecBarricades);
	}
		
		/*for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		m_vecBarricades.push_back(m_vecBarricades[i]);
	}*/
	
	//InitialiseBarricades();
	SetEnemysRemaining(kiNumEnemys); //Set number of enemies remaining in level

	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	return (true);
}

std::vector<CBarricade*> CLevel::InitialiseBarricades(std::vector<CBarricade*> _b)
{
	const int kiNumBarricades = 14;
	int kiBarStartX = 200;
	const int kiBarStartY = 525;

	int iCurrentBarX = kiBarStartX;
	int iCurrentBarY = kiBarStartY;
	int kiBarGap = 248;

	for (int j = 0; j < 4; ++j)
	{
		for (int i = 1; i <= kiNumBarricades; ++i)
		{
			CBarricade* m_pBarricade = new CBarricade();
			m_pBarricade->Initialise(static_cast<ESprite>(i));

			//Set up enemy settings
			if (i == 14)
			{
				iCurrentBarX += 32;
			}
			m_pBarricade->SetX(static_cast<float>(iCurrentBarX));
			m_pBarricade->SetY(static_cast<float>(iCurrentBarY));
			m_pBarricade->Process(1); //need due to timer within enemy movement giving a movement delay therefore giving the impression of a spawn delay
			iCurrentBarX += static_cast<int>(m_pBarricade->GetWidth());

			m_pBarricade->Process(1); //need due to timer within enemy movement giving a movement delay therefore giving the impression of a spawn delay
									  //m_vecBarricades[i]->GetSpriteInstance();
			if (iCurrentBarX > kiBarGap) //Set up enemy positions
			{
				iCurrentBarX = kiBarStartX;
				iCurrentBarY += 11;
			}
			_b.push_back(m_pBarricade);
			//m_vecBarricades.push_back(m_pBarricade); //Add barricade to vector
		}
		kiBarStartX += 190;
		iCurrentBarX = kiBarStartX;
		iCurrentBarY = kiBarStartY;
		kiBarGap += 190;
	}
	return _b;
}

//void CLevel::InitialiseBarricades()
//{
//	const int kiNumBarricades = 14;
//	int kiBarStartX = 200;
//	const int kiBarStartY = 525;
//
//	int iCurrentBarX = kiBarStartX;
//	int iCurrentBarY = kiBarStartY;
//	int kiBarGap = 248;
//
//	for (int j = 0; j < 4; ++j)
//	{
//		for (int i = 1; i <= kiNumBarricades; ++i)
//		{
//			CBarricade* m_pBarricade = new CBarricade();
//			m_pBarricade->Initialise(static_cast<ESprite>(i));
//
//			//Set up enemy settings
//			if (i == 14)
//			{
//				iCurrentBarX += 32;
//			}
//			m_pBarricade->SetX(static_cast<float>(iCurrentBarX));
//			m_pBarricade->SetY(static_cast<float>(iCurrentBarY));
//			m_pBarricade->Process(1); //need due to timer within enemy movement giving a movement delay therefore giving the impression of a spawn delay
//			iCurrentBarX += static_cast<int>(m_pBarricade->GetWidth());
//
//			m_pBarricade->Process(1); //need due to timer within enemy movement giving a movement delay therefore giving the impression of a spawn delay
//									  //m_vecBarricades[i]->GetSpriteInstance();
//			if (iCurrentBarX > kiBarGap) //Set up enemy positions
//			{
//				iCurrentBarX = kiBarStartX;
//				iCurrentBarY += 11;
//			}
//			m_vecBarricades.push_back(m_pBarricade);
//			//m_vecBarricades.push_back(m_pBarricade); //Add barricade to vector
//		}
//		kiBarStartX += 190;
//		iCurrentBarX = kiBarStartX;
//		iCurrentBarY = kiBarStartY;
//		kiBarGap += 190;
//	}
//}

/********
* Draw: Draw function for CLevel
*********/
void
CLevel::Draw()
{
	m_pBackground->Draw();

	m_pPlayer->Draw();

	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i) //Draw all enemies in vector
	{
		m_vecEnemies[i]->Draw();
	}

	for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		m_vecBarricades[i]->Draw();
	}

	/*for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		m_vecBarricades[i]->Draw();
	}*/

	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j) //Draw all player bullets
	{
		m_vecPlayerBullets[j]->Draw();
	}

	for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j) //Draw all enemy bullets
	{
		m_vecEnemyBullets[j]->Draw();
	}
	
	if (m_pEnemyShip != nullptr) //If the enemy ship exists, draw.
	{
		m_pEnemyShip->Draw();
	}

	//Draw UI
	DrawScore();
	DrawLevelCount();
}

/********
* Process: Process function for CLevel
*********/
void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);

	if (m_pEnemyShip != nullptr) //Process ship if it exists
	{
		m_pEnemyShip->Process(_fDeltaTick);
	}
	
	for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		m_vecBarricades[i]->Process(_fDeltaTick);
	}

	/*for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		m_pLevelLogic->GetLVLBarricades()[i]->Process(_fDeltaTick);
	}
*/
	if (GetAsyncKeyState(VK_SPACE) && !m_pPlayer->GetIsShooting()) //Call shooting for player
	{
		FireBullet(true, m_pLevelLogic->GetLVLPlayerBulletSpeed());
		m_pPlayer->SetIsShooting(true);
	}

	FireBullet(false, m_pLevelLogic->GetLVLEnemyBulletSpeed()); //Call shooting for enemies

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) //Process all player bullets
	{
		m_vecPlayerBullets[i]->Process(_fDeltaTick);
	}

	for (unsigned int i = 0; i < m_vecEnemyBullets.size(); ++i) //Process all enemy bullets
	{
		m_vecEnemyBullets[i]->Process(_fDeltaTick);
	}
	ProcessBarricadeCollision();
	//Process all game logic
	ProcessPlayerMovement();
	EnemyMovement(_fDeltaTick);
	ProcessEnemyShip();
	ProcessBulletEnemyCollision();
	ProcessBulletPlayerCollision();
	if (!m_pPlayer->GetIsPlayerAlive())
	{
		ProcessPlayerDead();
	}
	//ProcessEnemyDeadAnim();
	ProcessCheckForWin();
	ProcessBulletBounds();
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

/********
* GetLevelController: Gets the level logic for the level
*********/
CLevelLogic & CLevel::GetLevelController()
{
	return *m_pLevelLogic;
}

/********
* FireBullet: Allows player or enemies to fire bullets.
*			: Players may only shoot once their bullet is dead.
*			: Enemies that shoot are randomly picked and enemy shooting has a delayed speed
* @parameter: isPlayer - true is player, false is enemy
* @parameter: bulletSpeed - bullet speed of entity
*********/
void CLevel::FireBullet(bool isPlayer, float bulletSpeed)
{
	const float fBulletVelX = 0.0f;
	float fBulletVelY = -bulletSpeed;

	if (isPlayer) //If player
	{
		m_pBullet = new CBullet();

		m_pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
		m_pBullet->SetX(m_pPlayer->GetX());
		m_pBullet->SetY(m_pPlayer->GetY() - 20.0f);
		m_vecPlayerBullets.push_back(m_pBullet);
	}
	else //If enemy
	{
		m_cEndBullet = clock();
		//Check that time since the last bullet is bigger than the specified delay time
		double elapsed_secs = double(m_cEndBullet - m_cBeginBullet) / CLOCKS_PER_SEC;
		if (elapsed_secs > m_pLevelLogic->GetLVLEnemyShootingDelay() || elapsed_secs < 0.0f)
		{
			int randEnemy = rand() % (55 + 0); //choose random enemy

			//Note: Made it so enemies that sit behind other enemies are not able to shoot
			if (m_vecEnemies[randEnemy]->GetCanShoot() && !m_vecEnemies[randEnemy]->IsHit()) //If enemy is not dead and is able to shoot
			{
				m_pBullet = new CBullet();

				fBulletVelY *= -1;
				m_pBullet->Initialise(static_cast<float>(m_iWidth), static_cast<float>(m_iHeight), fBulletVelX, fBulletVelY);
				m_pBullet->SetX(m_vecEnemies[randEnemy]->GetX());
				m_pBullet->SetY(m_vecEnemies[randEnemy]->GetY() + 20.0f);
				m_vecEnemyBullets.push_back(m_pBullet);
				m_cBeginBullet = clock();
			}
		}
	}
}

/********
* GetPlayer: Getter for the player 
*********/
CPlayer*
CLevel::GetPlayer() const
{
	return (m_pPlayer);
}

/********
* ProcessBulletEnemyCollision: Detects bullet-enemy collision and deletes bullet 
*							   and enemy on collision while increasin player score
*********/
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

					if (i > 11)
					{
						m_vecEnemies[i - 11]->SetCanShoot(true);
					}

					m_pLevelLogic->SetLVLPlayerScore(m_pLevelLogic->GetLVLPlayerScore()+m_vecEnemies[i]->GetEnemyPoints());

					//Destroy player bullet
					delete m_vecPlayerBullets[j];
					m_vecPlayerBullets[j] = 0;

					m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
					m_pPlayer->SetIsShooting(false);

					//Decrease enemy count
					SetEnemysRemaining(GetEnemysRemaining() - 1);
				}				
			}
		}
	}

	//Detects playerbullet-enemyShip collision and add to player score
	for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
	{
		if (m_pEnemyShip != nullptr && m_vecPlayerBullets[j]->IsCollidingWith(*m_pEnemyShip))
		{
      		m_pEnemyShip->SetHit(true);
  			m_pLevelLogic->SetLVLPlayerScore(m_pLevelLogic->GetLVLPlayerScore() + m_pEnemyShip->GetEnemyPoints());
			delete m_vecPlayerBullets[j];
			m_vecPlayerBullets[j] = 0;

			m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
			m_pPlayer->SetIsShooting(false);
		}
	}
	
}

/********
* ProcessBarricadeCollision: Detects and processes player/enemy bullet vs barricade collision
*********/
void
CLevel::ProcessBarricadeCollision()
{
	for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		for (unsigned int j = 0; j < m_vecPlayerBullets.size(); ++j)
		{
			if (!m_vecBarricades[i]->IsHit())
			{
				//If bullet collides with barricade entity
				if (m_vecPlayerBullets[j]->IsCollidingWith(*m_vecBarricades[i]))
				{
					m_vecBarricades[i]->ChangeBarricadeSprite();
					int state = static_cast<int>(m_vecBarricades[i]->GetBarState()) + 1;
					if (state != 5)
					{
						m_vecBarricades[i]->SetBarState(static_cast<EBarState>(state));
					}
					else
					{
						m_vecBarricades[i]->SetHit(true);
					}

					//Destroy player bullet
					delete m_vecPlayerBullets[j];
					m_vecPlayerBullets[j] = 0;

					m_vecPlayerBullets.erase(m_vecPlayerBullets.begin() + j);
					m_pPlayer->SetIsShooting(false);
				}
			}
		}
	}

	for (unsigned int i = 0; i < m_vecBarricades.size(); ++i)
	{
		for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
		{
			if (!m_vecBarricades[i]->IsHit())
			{
				//If bullet collides with barricade entity
				if (m_vecEnemyBullets[j]->IsCollidingWith(*m_vecBarricades[i]))
				{
					//Hide enemy, erase bullet, decrease enemy count

					m_vecBarricades[i]->ChangeBarricadeSprite();
					int state = static_cast<int>(m_vecBarricades[i]->GetBarState()) + 1;
					if (state != 5)
					{
						m_vecBarricades[i]->SetBarState(static_cast<EBarState>(state));
					}
					else
					{
						m_vecBarricades[i]->SetHit(true);
					}

					//Destroy enemy bullet
					delete m_vecEnemyBullets[j];
					m_vecEnemyBullets[j] = 0;

					m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + j);
				}
			}
		}
	}
}

/********
* ProcessBulletPlayerCollision: Detects if enemy bullets hit player. If they do, remove player life and delete bullet
*********/
void
CLevel::ProcessBulletPlayerCollision()
{
	if (m_pPlayer->GetIsPlayerAlive())
	{
		for (unsigned int j = 0; j < m_vecEnemyBullets.size(); ++j)
		{
			//If enemy bullet collides with player entity
			if (m_vecEnemyBullets[j]->IsCollidingWith(*m_pPlayer))
			{
				delete m_vecEnemyBullets[j];
				m_vecEnemyBullets[j] = 0;
				m_vecEnemyBullets.erase(m_vecEnemyBullets.begin() + j);

				//If the player is not invincible, remove player life
				if (!m_pLevelLogic->GetLVLPlayerInvincibility())
				{
					//Hide enemy, erase bullet, decrease enemy count
					m_pPlayer->SetPlayerAlive(false);
					m_cBeginPlayerDead = clock();
					m_pPlayer->SwitchDead(true);
					m_cEndPlayerDead = clock();
					//Remove life
					m_pLevelLogic->SetLVLPlayerLives(m_pLevelLogic->GetLVLPlayerLives() - 1);//m_pPlayer->GetPlayerLives() - 1);

					if (m_pLevelLogic->GetLVLPlayerLives() == 0)
					{
						CGame::GetInstance().GameOverLost();
					}
				}
			}
		}
	}

}

/********
* ProcessPlayerDead: Keeps player as dead sprite for 1 second. Player is invincible for 1 second.
*********/
void CLevel::ProcessPlayerDead()
{
	//Set a move delay player dead
	double elapsed_secs = double(m_cEndPlayerDead - m_cBeginPlayerDead) / CLOCKS_PER_SEC;
	if (elapsed_secs > 1.0f || elapsed_secs < 0.0f)
	{
		m_pPlayer->SwitchDead(false);
		m_pPlayer->SetPlayerAlive(true);
	}
	m_cEndPlayerDead = clock();
}

/********
* ProcessCheckForWin: Check if player has won
*********/
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

	/*for (unsigned int i = 0; i < m_pLevelLogic->GetLVLBarricades().size(); ++i)
	{
		m_pLevelLogic->GetLVLBarricades().push_back(m_vecBarricades[i]);
	}
*/
	CGame::GetInstance().GameOverWon();
}

/********
* ProcessBulletBounds: Detects if bullets are outside of the screen. If so, delete.
*********/
void
CLevel::ProcessBulletBounds()
{
	//Player bullets
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

	//Enemy bullets
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

/********
* ProcessPlayerMovement: Processes player movement
*********/
void
CLevel::ProcessPlayerMovement()
{
	
	float fHalfPlayerW = m_pPlayer->GetWidth()/2.0f; //->GetSpriteType()->GetWidth() / 2.0f;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //If RIGHT key pressed, move player right
	{
		m_pPlayer->SetX(m_pPlayer->GetX() + m_pLevelLogic->GetLVLPlayerMovementSpeed());
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //If LEFT key pressed, move player left
	{
		m_pPlayer->SetX(m_pPlayer->GetX() - m_pLevelLogic->GetLVLPlayerMovementSpeed());
	}

	//If player is out of boundary set player at side of screen
	if (m_pPlayer->GetX() - fHalfPlayerW <= 0) 
	{
		m_pPlayer->SetX(fHalfPlayerW);
	}
	else if (m_pPlayer->GetX() + m_pPlayer->GetWidth() >= 1000.0f)
	{
		m_pPlayer->SetX(1000.0f - m_pPlayer->GetWidth());
	}
}

/********
* EnemyMovement: Processes enemy movement and detects if it reaches a wall or the bottom of the level
*********/
void
CLevel::EnemyMovement(float _fDeltaTick)
{
	bool wall = false;
	bool lose = false;
	
	//Set a move delay for the enemies
	double elapsed_secs = double(m_cEndEnemyMove - m_cBeginEnemyMove) / CLOCKS_PER_SEC;
	if (elapsed_secs > m_pLevelLogic->GetLVLEnemyMoveDelay() || elapsed_secs < 0.0f)
	{
		m_cBeginEnemyMove = clock();

		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			m_vecEnemies[i]->Process(_fDeltaTick);

			if ((m_vecEnemies[i]->GetX() + (m_vecEnemies[i]->GetWidth() / 2) >= 990.0f) //If enemy reaches wall, set bool as true
				|| (m_vecEnemies[i]->GetX() - (m_vecEnemies[i]->GetWidth() / 2) <= 0.0f))
			{
				wall = true;
			}

			if (m_vecEnemies[i]->IsHit() == false) //if enemy is alive
			{
				if (m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= (m_pPlayer->GetY() + (m_pPlayer->GetHeight() / 2))
					|| m_vecEnemies[i]->GetY() + (m_vecEnemies[i]->GetHeight() / 2) >= 650.0f) //650.0f = lose line
				{
					lose = true; //Set player loss
				}
			}
		}
	}

	m_cEndEnemyMove = clock();

	if (wall) //If player reaches wall, increase speed (decrease movement delay)
	{
		wall = false;
		if (m_pLevelLogic->GetLVLEnemyMoveDelay() >= 0.4f)
		{
			m_pLevelLogic->SetLVLEnemyMoveDelay(m_pLevelLogic->GetLVLEnemyMoveDelay() - 0.1f);
		}
		else if (m_pLevelLogic->GetLVLEnemyMoveDelay() >= 0.2f)
		{
			m_pLevelLogic->SetLVLEnemyMoveDelay(m_pLevelLogic->GetLVLEnemyMoveDelay() - 0.05f);
		}
		else if (m_pLevelLogic->GetLVLEnemyMoveDelay() >= 0.04f)
		{
			m_pLevelLogic->SetLVLEnemyMoveDelay(m_pLevelLogic->GetLVLEnemyMoveDelay() - 0.02f);
		}

		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			m_vecEnemies[i]->SetY(m_vecEnemies[i]->GetY() + 50); //Increment level down by 50
			m_vecEnemies[i]->SetVelocityX(m_vecEnemies[i]->GetVelocityX() *-1);
			m_vecEnemies[i]->Process(_fDeltaTick);
		}
	}

	if (lose) //Set the game as lost if enemies reach the bottom of the level.
	{
		CGame::GetInstance().GameOverLost();
	}
}

/********
* GetEnemysRemaining: Get the remaining enemies within the level
*********/
int
CLevel::GetEnemysRemaining() const
{
	return (m_iEnemysRemaining);
}

/********
* SetEnemysRemaining: Set the remaining enemies within the level
*********/
void
CLevel::SetEnemysRemaining(int _i)
{
	m_iEnemysRemaining = _i;
}

/********
* ProcessEnemyShip: Process the enemy ship that appears at the top of the screen.
*					Appears at a random time and random side. Enemy ship also has random points.
*********/
void CLevel::ProcessEnemyShip()
{
	//Make sure ship appears at random time
	double elapsed_secs = double(m_cEndShipMove - m_cBeginShipMove) / CLOCKS_PER_SEC;
	if (elapsed_secs > m_pLevelLogic->GetLVLShipRandTime() || elapsed_secs < 0.0f)
	{
		m_cBeginShipMove = clock();

		if (m_pEnemyShip == nullptr) //If ship doesnt exist and random time is reached
		{
			m_pEnemyShip = new CEnemy();
			m_pEnemyShip->Initialise(ESprite::ENEMYSHIP);
		
			//Generate a random number for 0 and 1 for the side of the screen the ship will appear
			m_iRandShipDirection = rand() % 2;

			if (m_iRandShipDirection == 1) //If num is 1, make ship appear on the left
			{
				m_pEnemyShip->SetX(-10);
				m_pEnemyShip->SetVelocityX(m_pLevelLogic->GetLVLEnemyShipSpeed());
			}
			else //Make ship appear on the right
			{
				m_pEnemyShip->SetX(1000);
				m_pEnemyShip->SetVelocityX(m_pLevelLogic->GetLVLEnemyShipSpeed()*-1);
			}
			m_pEnemyShip->SetY(50);
			m_pEnemyShip->SetHit(false);
			m_pEnemyShip->Process(1);
		}
		else //If ship DOES exist
		{
			if (m_iRandShipDirection == 1)
			{
				if ((m_pEnemyShip->GetX() + (m_pEnemyShip->GetWidth() / 2) >= 1000.0f)) //Delete ship when it gets to the right
				{
					delete m_pEnemyShip;
					m_pEnemyShip = 0;
				}
			}
			else
			{
				if (m_pEnemyShip->GetX() - (m_pEnemyShip->GetWidth() / 2) <= 0.0f) //Delete ship when it gets to the left
				{
					delete m_pEnemyShip;
					m_pEnemyShip = 0;
				}
			}
			//Set new random ship spawn time
			int randShipTime = (rand() % (20 - 7 + 1)) + 2;
			m_pLevelLogic->SetLVLShipRandTime(randShipTime);
		}
	}
	m_cEndShipMove = clock();
}

/********
* DrawScore: Draw the player's score, lives and invincibility message
*********/
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
	m_strScore += ToString(m_pLevelLogic->GetLVLPlayerScore());//m_pPlayer->GetPlayerScore());
	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));

	SetTextColor(hdc, RGB(27, 233, 56));
	TextOutA(hdc, 0, m_iHeight - 135, line.c_str(), static_cast<int>(line.size()));

	m_strPlayerLives = "Player Lives: ";
	m_strPlayerLives += ToString(m_pLevelLogic->GetLVLPlayerLives());
	if (m_pLevelLogic->GetLVLPlayerInvincibility())
	{
		m_strPlayerLives += "                                                                     YOU ARE CURRENTLY INVINCIBLE";
	}
	TextOutA(hdc, 20, m_iHeight - 100, m_strPlayerLives.c_str(), static_cast<int>(m_strPlayerLives.size()));

}

/********
* DrawLevelCount: Draw the current games level count
*********/
void
CLevel::DrawLevelCount()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(27, 233, 56));
	m_strPlayerLives = "Level: ";
	m_strPlayerLives += ToString(m_pLevelLogic->GetLVLLevelCount());//m_pPlayer->GetPlayerScore());

	SetTextColor(hdc, RGB(27, 233, 56));
	TextOutA(hdc, m_iWidth - 100, m_iHeight - 100, m_strPlayerLives.c_str(), static_cast<int>(m_strPlayerLives.size()));
}