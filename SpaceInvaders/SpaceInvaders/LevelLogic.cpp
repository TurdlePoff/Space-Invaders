//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: "LevelLogic.cpp"
// Description	: Implementation file for LevelLogic
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "LevelLogic.h"
#include <iostream>
#include <fstream>

/************
* CLevelLogic Constructor
*************/
CLevelLogic::CLevelLogic()
//Enemy predefininitions
	: m_fLVLEnemyBulletVelocity(1.0f)
	, m_fLVLEnemyShootingDelay(2.0f)
	, m_iLVLRealEnemyDelay(1.0f)
	, m_fLVLEnemyMoveDelay(1.0f)
	, m_fLVLEnemyShipSpeed(2.0f)
	//Player predefininitions
	, m_fLVLPlayerBulletVelocity(6.0f)
	, m_fLVLPlayerSpeed(4.0f)
	, m_fLVLPlayerInvincibility(false)
	, m_iLVLPlayerScore(0)
	, m_iLVLPlayerLives(3)
	//Misc predefinitions
	, m_iShipRandTime(0)
	, m_iLVLLevelCount(1)
{
	//CreateBarricades();
}

/************
* ~CLevelLogic Destructor
*************/
CLevelLogic::~CLevelLogic()
{
	m_vecHScores.clear();

	while (m_LVLVecBarricades.size() > 0)
	{
		CBarricade* m_pBarricade = m_LVLVecBarricades[m_LVLVecBarricades.size() - 1];

		m_LVLVecBarricades.pop_back();

		delete m_pBarricade;
		m_pBarricade = 0;
	}
	m_LVLVecBarricades.clear();

}

/************
* SetLVLEnemyBulletSpeed: Sets bullet speed of enemy of the CURRENT level
* @parameter: _f
*************/
void CLevelLogic::SetLVLEnemyBulletSpeed(float _f)
{
	m_fLVLEnemyBulletVelocity = _f;
}

/************
* GetLVLEnemyBulletSpeed: Gets bullet speed of enemy of the CURRENT level
* @return: m_fLVLEnemyBulletVelocity - bullet speed of enemy
*************/
float CLevelLogic::GetLVLEnemyBulletSpeed()
{
	return m_fLVLEnemyBulletVelocity;
}

/************
* SetLVLPlayerBulletSpeed: Sets bullet speed of player
* @parameter: _f
*************/
void CLevelLogic::SetLVLPlayerBulletSpeed(float _f)
{
	m_fLVLPlayerBulletVelocity = _f;
}

/************
* GetLVLPlayerBulletSpeed: Sets speed of player bullet
* @return: m_fLVLPlayerBulletVelocity - speed of player bullet
*************/
float CLevelLogic::GetLVLPlayerBulletSpeed()
{
	return m_fLVLPlayerBulletVelocity;
}

/************
* SetLVLPlayerMovementSpeed: Sets movement speed of player
* @parameter: _f
*************/
void CLevelLogic::SetLVLPlayerMovementSpeed(float _f)
{
	m_fLVLPlayerSpeed = _f;
}

/************
* GetLVLPlayerMovementSpeed: Sets speed of player
* @return: m_fLVLPlayerSpeed - speed of player
*************/
float CLevelLogic::GetLVLPlayerMovementSpeed()
{
	return m_fLVLPlayerSpeed;
}

/************
* SetLVLPlayerInvincibility: Sets invincibility for player
* @parameter: _b
*************/
void CLevelLogic::SetLVLPlayerInvincibility(bool _b)
{
	m_fLVLPlayerInvincibility = _b;
}

/************
* GetLVLPlayerInvincibility: Gets player invincibility
* @return: m_fLVLPlayerInvincibility - player invincibility
*************/
bool CLevelLogic::GetLVLPlayerInvincibility()
{
	return m_fLVLPlayerInvincibility;
}

/************
* SetLVLPlayerScore: Sets player score
* @parameter: _i
*************/
void CLevelLogic::SetLVLPlayerScore(int _i)
{
	m_iLVLPlayerScore = _i;
}

/************
* GetLVLPlayerScore: Gets the player's score
* @return: m_iLVLPlayerScore - player score
*************/
int CLevelLogic::GetLVLPlayerScore()
{
	return m_iLVLPlayerScore;
}


/************
* SetLVLPlayerLives: Sets player lives
* @parameter: _i
*************/
void CLevelLogic::SetLVLPlayerLives(int _i)
{
	m_iLVLPlayerLives = _i;
}

/************
* GetLVLPlayerLives: Gets the player's life count
* @return: m_iLVLPlayerLives - player lives
*************/
int CLevelLogic::GetLVLPlayerLives()
{
	return m_iLVLPlayerLives;
}

/************
* SetLVLLevelCount: Sets level count of current game
* @parameter: _i
*************/
void CLevelLogic::SetLVLLevelCount(int _i)
{
	m_iLVLLevelCount = _i;
}

/************
* GetLVLLevelCount: Gets the level count of the current game
* @return: m_iLVLLevelCount - level count
*************/
int CLevelLogic::GetLVLLevelCount()
{
	return m_iLVLLevelCount;
}

/************
* HighScores: Displays the highscores onto the screen
*************/
void CLevelLogic::DisplayHighScores()
{

}

/************
* SetLVLEnemyMoveDelay: Sets enemy movement DELAY in seconds
* @parameter: _f
*************/
void CLevelLogic::SetLVLEnemyMoveDelay(float _f)
{
	m_fLVLEnemyMoveDelay = _f;
}

/************
* GetLVLEnemyMoveDelay: Gets the movement delay of the enemies
* @return: m_fLVLEnemyMoveDelay - movement delay of enemies
*************/
float CLevelLogic::GetLVLEnemyMoveDelay()
{
	return m_fLVLEnemyMoveDelay;
}

/************
* SetLVLRealEnemyDelay: Sets the enemy's real delay time
* @parameter: _f
*************/
void CLevelLogic::SetLVLRealEnemyDelay(float _f)
{
	m_iLVLRealEnemyDelay = _f;
}

/************
* GetLVLRealEnemyDelay: Gets the real movement delay of the enemies
* @return: m_iLVLRealEnemyDelay - real movement delay of enemies
*************/
float CLevelLogic::GetLVLRealEnemyDelay()
{
	return m_iLVLRealEnemyDelay;
}

/************
* SetLVLEnemyShipSpeed: Sets the speed of the enemies
* @parameter: _f
*************/
void CLevelLogic::SetLVLEnemyShipSpeed(float _f)
{
	m_fLVLEnemyShipSpeed = _f;
}

/************
* GetLVLEnemyShipSpeed: Gets the speed of the enemy ship
* @return: m_fLVLEnemyShipSpeed - enemy ship speed
*************/
float CLevelLogic::GetLVLEnemyShipSpeed()
{
	return m_fLVLEnemyShipSpeed;
}

/************
* SetLVLShipRandTime: Sets a random time delay for the enemy ship at the top of the screen to spawn
* @parameter: _i
*************/
void CLevelLogic::SetLVLShipRandTime(int _i)
{
	m_iShipRandTime = _i;
}

/************
* GetLVLShipRandTime: Gets the random time delay for the enemy ship
* @return: m_iShipRandTime - random time delay for enemy ship
*************/
int CLevelLogic::GetLVLShipRandTime()
{
	return m_iShipRandTime;
}

/************
* SetLVLEnemyShootingDelay: Sets the enemy shooting delay for the current level
* @parameter: _f
*************/
void CLevelLogic::SetLVLEnemyShootingDelay(float _f)
{
	m_fLVLEnemyShootingDelay = _f;
}

/************
* GetLVLEnemyShootingDelay: Gets the shooting delay for the enemies
* @return: m_fLVLEnemyShootingDelay - shooting delay for the enemies
*************/
float CLevelLogic::GetLVLEnemyShootingDelay()
{
	return m_fLVLEnemyShootingDelay;
}

/************
* SetLVLHighScoreName: Sets the name of the player
*************/
void CLevelLogic::SetLVLHighScoreName(std::string _s)
{
	m_sLVLPlayerName = _s;
}

/************
* GetLVLHighScoreName: Gets the name of the player
* return m_sLVLPlayerName - player name
*************/
std::string CLevelLogic::GetLVLHighScoreName()
{
	return m_sLVLPlayerName;
}

/************
* WriteToHighScores: Writes a highscore to the txt file to store scores across games
*************/
void CLevelLogic::WriteToHighScores(HScores _newValue)
{
	m_vecHScores.push_back(_newValue);
	std::ofstream myFile;
	const int kiMaxScores = 3;

	//Write the score file to scores.txt
	myFile.open("..\\Sprites\\scores.txt");
	if (myFile.is_open())
	{
		for (int i = 0; i < m_vecHScores.size(); ++i)
		{
			myFile << m_vecHScores[i].name << "=";
			myFile << m_vecHScores[i].score;
			if (i != m_vecHScores.size()-1)
			{
				myFile << std::endl;
			}
		}
		myFile.close();
	}
}

/************
* ReadHighScores: Reads all highscores and pushes them to the highscore vector
*************/
void CLevelLogic::ReadHighScores()
{
	m_vecHScores.clear();
	std::ifstream myFile;
	myFile.open("..\\Sprites\\scores.txt");
	std::string strName;
	std::string strScore;
	int iScore;
	if (myFile.is_open())
	{
		std::string strLine;
		while (!myFile.eof())
		{
			std::getline(myFile, strLine);
			size_t equalsPos = strLine.find('=');
			strName = strLine.substr(0, equalsPos);
			iScore = atoi((strLine.substr(equalsPos + 1, strLine.length())).c_str());
			//Each
			m_vecHScores.push_back({ strName, iScore });
		}
		myFile.close();
	}
	//Sort highscores from highest to lowest
	std::sort(m_vecHScores.begin(), m_vecHScores.end(), highScoreFunctor());
}

/************
* GetHighScores: gets the highscore vector
* @return m_vecHScores - vector of highscores
*************/
std::vector<HScores>& CLevelLogic::GetHighScores()
{
	return m_vecHScores;
}
