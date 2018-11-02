#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

namespace Juego
{
	struct obstacle
	{
		Vector2 pos;
		Vector2 size;
		float speed;
		bool isAlive;
		Color color;
	};

	extern obstacle levelBackground;
	extern obstacle levelMiddleSquare;

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void createLevelObstacles();
		void DrawLevel();
	}
}

#endif // LEVEL_H
