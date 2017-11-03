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
	std::sort(customers.begin(), customers.end(), &scoreSorter);
	if (m_vTop5Scores[4].score < pScore)
	{
		m_vTop5Scores[4] = { pName, pScore };
	}
	std::sort(m_vTop5Scores, m_vTop5Scores + 5);
}

HScores& CHighScores::GetScores()
{
	return *m_vTop5Scores;
}

bool CHighScores::scoreSorter(HScores const & lhs, HScores const & rhs)
{
	return lhs.score < rhs.score;
}
