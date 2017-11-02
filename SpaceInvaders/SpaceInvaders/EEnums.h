#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "EEnums.h"
// Description	: Decalaration file for ESprite and EGameState class enums used in the game
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#if !defined(__EENUMS_H__)
#define __EENUMS_H__

enum class ESprite
{
	ENEMYTOP,
	ENEMYMED,
	ENEMYBOT,
	ENEMYSHIP,
	BARRICADE,
	BULLET,
	PLAYER,
	DEADPLAYER,
	DEADTOP,
	DEADMED,
	DEADBOT,
	BACKGROUND,
	MAINMENU,
	INSTRUCTIONS,
	HIGHSCORES,
	LVLCOMP
};


enum class EGameState
{
	MENU, 
	INSTRUCTIONS, 
	HIGHSCORES, 
	GAME
};

#endif    // __EENUMS_H__
