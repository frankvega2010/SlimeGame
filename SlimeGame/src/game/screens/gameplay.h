#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	enum gameplayOptions 
	{
		buttonContinue = 20,
		buttonRestart,
		buttonGameOver,
		buttonQuitToMenu
	};

	enum playerKeysNumber
	{
		UP = 8,
		RIGHT,
		GRAVITY,
		DOWN,
		LEFT,
		MAX
	};

	extern bool gameON;
	extern int playerKeys[MAX];
	extern Texture2D slime;
	extern Texture2D enemy01;
	extern Sound slimeJump;
	extern Sound slimeSplash;
	extern Music slimeMove;
	extern Music backgroundSong;

	namespace Gameplay_Section
	{
		void InitGameplayVariables();
		void InitGameplayParallax();
		void InitGameplayScreen();
		void UpdateGameplayScreen();
		void DrawGameplay();
		void RestartPhase();
		bool FinishGameplayScreen();
		void DeInitGameplayParallax();
		void DeInitGameplayResources();
	}
}
#endif // GAMEPLAY_H