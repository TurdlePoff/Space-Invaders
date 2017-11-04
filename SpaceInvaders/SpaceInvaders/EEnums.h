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
	//BARRICADE PIECES
	BAR1 = 1,
	BAR2,
	BAR3,
	BAR4,
	BAR5,
	BAR6,
	BAR7,
	BAR8,
	BAR9,
	BAR10,
	BAR11,
	BAR12,
	BAR13,
	BAR14,
	//OtherSprites
	ENEMYTOP,
	ENEMYMED,
	ENEMYBOT,
	ENEMYSHIP,
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
	LVLCOMP,
};

enum class EBarState
{
	BARUNTOUCHED = 0, //NOT HIT
	HIT1, //HIT ONCE
	HIT2, //HIT TWICE
	HIT3, //FINAL CHANCE
	BARDEAD	//SET HIT = FALSE
};

enum class EGameState
{
	MENU, 
	INSTRUCTIONS, 
	HIGHSCORES, 
	GAME
};

#endif    // __EENUMS_H__
