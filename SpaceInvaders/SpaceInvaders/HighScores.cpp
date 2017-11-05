//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: "HighScores.cpp"
// Description	: Implementation file for HighScores
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "HighScores.h"
#include <algorithm>

CHighScores::CHighScores()
{
}

CHighScores::~CHighScores()
{
}

void CHighScores::WriteToHighScores(HScores _newValue)
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
			myFile << m_vecHScores[i].score << std::endl;
		}
		myFile.close();
	}
}

void CHighScores::ReadHighScores()
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
}

std::vector<HScores>& CHighScores::GetHighScores()
{
	return m_vecHScores;
}
