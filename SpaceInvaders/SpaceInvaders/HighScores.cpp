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
	for (int i = 0; i < 5; i++)
	{
		m_vTop5Scores[i] = {" ", 0};
	}
}

CHighScores::~CHighScores()
{
}

void CHighScores::SetScore(std::string pName, int pScore)
{
	/*std::sort(customers.begin(), customers.end(), &scoreSorter);
	if (m_vTop5Scores[4].score < pScore)
	{
		m_vTop5Scores[4] = { pName, pScore };
	}
	std::sort(m_vTop5Scores, m_vTop5Scores + 5);*/
}

HScores& CHighScores::GetScores()
{
	return *m_vTop5Scores;
}

void CHighScores::ReadHighScores()
{
	std::ifstream myFile;
	myFile.open("scores.txt");
	if (myFile.is_open())
	{
		std::string strLine;
		while (!myFile.eof())
		{
			std::getline(myFile, strLine);
			size_t equalsPos = strLine.find('=');
			std::string strName = strLine.substr(0, equalsPos);
			std::string strScore = strLine.substr(equalsPos + 1,
				strLine.length());
			int iScore = atoi(strScore.c_str());
			//Then put the score in the highscore table...
		}
		myFile.close();
	}
}

bool CHighScores::scoreSorter(HScores const & lhs, HScores const & rhs)
{
	return lhs.score < rhs.score;
}
