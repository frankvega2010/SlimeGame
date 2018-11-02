#include "level.h"

#include "setup/game.h"

namespace Juego
{
	obstacle levelBackground;
	obstacle levelMiddleSquare;

	namespace Gameplay_Section
	{
		void createLevelBackground()
		{
			levelBackground.pos.x = 0 + 50;
			levelBackground.pos.y = 0 + 50;
			levelBackground.size.x = screenWidth - 100;
			levelBackground.size.y = screenHeight - 100;
			levelBackground.speed = 0;
			levelBackground.isAlive = true;
			levelBackground.color = GRAY;
		}

		void createLevelObstacles()
		{
			levelMiddleSquare.pos.x = screenWidth/2 - 200;
			levelMiddleSquare.pos.y = screenHeight/2 - 200;
			levelMiddleSquare.size.x = 400;
			levelMiddleSquare.size.y = 400;
			levelMiddleSquare.speed = 0;
			levelMiddleSquare.isAlive = true;
			levelMiddleSquare.color = BLACK;
		}

		void DrawLevel()
		{
			DrawRectangle(levelBackground.pos.x, levelBackground.pos.y, levelBackground.size.x, levelBackground.size.y, levelBackground.color);
			DrawRectangle(levelMiddleSquare.pos.x, levelMiddleSquare.pos.y, levelMiddleSquare.size.x, levelMiddleSquare.size.y, levelMiddleSquare.color);
		}
	}
}