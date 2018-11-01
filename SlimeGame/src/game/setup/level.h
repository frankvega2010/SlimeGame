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

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void DrawLevel();
	}
}

#endif // LEVEL_H
