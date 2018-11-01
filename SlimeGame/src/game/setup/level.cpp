#include "level.h"

#include "setup/game.h"

namespace Juego
{
	obstacle levelBackground;

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

		void DrawLevel()
		{
			DrawRectangle(levelBackground.pos.x, levelBackground.pos.y, levelBackground.size.x, levelBackground.size.y, levelBackground.color);
		}
	}
}