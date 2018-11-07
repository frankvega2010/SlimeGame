#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

namespace Juego
{
	enum obstacles
	{
		obMiddleSquare = 0,
		obMiddleSquare2,
		obMiddleSquare3,
		obMiddleSquare4,
		obMiddleSquare5,
		obMiddleSquare6,
		obMiddleSquare7,
		obMiddleSquare8,
		obMiddleSquare9,
		obMiddleSquare10,
		maxObstacles
	};
	struct obstacle
	{
		Vector2 pos;
		Vector2 size;
		float speed;
		bool isAlive;
		Color color;
	};

	const int maxSpikes = 7;
	extern int currentLevel;
	//extern obstacle levelBackground;
	//extern obstacle levelMiddleSquare;
	extern obstacle obBackground;
	extern obstacle obstacles[maxObstacles];
	extern obstacle spikes[maxSpikes];
	extern obstacle exit;
	extern Rectangle enemy01Source;
	extern Rectangle enemy02Source;
	extern Rectangle enemy03Source;

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void createLevelObstacles();
		void DrawLevel();
	}
}

#endif // LEVEL_H
