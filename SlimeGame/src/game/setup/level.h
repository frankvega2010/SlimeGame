#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

namespace Juego
{
	enum obstacles
	{
		obBackground = 0,
		obMiddleSquare,
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

	//extern obstacle levelBackground;
	//extern obstacle levelMiddleSquare;
	extern obstacle obstacles[maxObstacles];

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void createLevelObstacles();
		void DrawLevel();
	}
}

#endif // LEVEL_H
