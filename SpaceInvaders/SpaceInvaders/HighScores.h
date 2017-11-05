#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "HighScores.h"
// Description	: Declaration file for HighScores
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//
#include <string>
#include <fstream>
struct HScores
{
	std::string name;
	int score;
};

class CHighScores
{
	// Member Functions
public:
	CHighScores();
	~CHighScores();

	void SetScore(std::string pName, int pScore);
	HScores& GetScores();
	void ReadHighScores();
	bool scoreSorter(HScores const& lhs, HScores const& rhs);
private:
	HScores m_vTop5Scores[5];
};