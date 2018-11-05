#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

namespace Juego
{
	enum obstacles
	{
		obMiddleSquare = 0,
		obMiddleSquare2,
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
	extern obstacle obBackground;
	extern obstacle obstacles[maxObstacles];

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void createLevelObstacles();
		void DrawLevel();
	}
}

#endif // LEVEL_H
