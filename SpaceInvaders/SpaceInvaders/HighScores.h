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
#include <vector>

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

	void WriteToHighScores(HScores _newValue);
	void ReadHighScores();
	std::vector<HScores>& GetHighScores();

private:
	std::vector<HScores> m_vecHScores;
};