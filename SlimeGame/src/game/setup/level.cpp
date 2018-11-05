#include "level.h"

#include "setup/game.h"

namespace Juego
{
	//obstacle levelBackground;
	//obstacle levelMiddleSquare;

	obstacle obBackground;
	obstacle obstacles[maxObstacles];

	namespace Gameplay_Section
	{
		void createLevelBackground()
		{
			
		}

		void createLevelObstacles()
		{
			/*for (int i = 0;i < maxObstacles;i++)
			{

			}*/

			obBackground.pos.x = 0 + 50;
			obBackground.pos.y = 0 + 50;
			obBackground.size.x = screenWidth - 100;
			obBackground.size.y = screenHeight - 100;
			obBackground.speed = 0;
			obBackground.isAlive = true;
			obBackground.color = GRAY;

			obstacles[obMiddleSquare].pos.x = (float)screenWidth/4 - 100;
			obstacles[obMiddleSquare].pos.y = screenHeight/2 - 100;
			obstacles[obMiddleSquare].size.x = 200;
			obstacles[obMiddleSquare].size.y = 200;
			obstacles[obMiddleSquare].speed = 0;
			obstacles[obMiddleSquare].isAlive = true;
			obstacles[obMiddleSquare].color = BLACK;

			obstacles[obMiddleSquare2].pos.x = (float)screenWidth / 1.2f - 100;
			obstacles[obMiddleSquare2].pos.y = screenHeight / 2 - 100;
			obstacles[obMiddleSquare2].size.x = 200;
			obstacles[obMiddleSquare2].size.y = 200;
			obstacles[obMiddleSquare2].speed = 0;
			obstacles[obMiddleSquare2].isAlive = true;
			obstacles[obMiddleSquare2].color = BLACK;
		}

		void DrawLevel()
		{
			DrawRectangle(obBackground.pos.x, obBackground.pos.y, obBackground.size.x, obBackground.size.y, obBackground.color);
			
			for (int i = 0; i < maxObstacles; i++)
			{
				DrawRectangle(obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].size.x, obstacles[i].size.y, obstacles[i].color);
			}
			//DrawRectangle(levelMiddleSquare.pos.x, levelMiddleSquare.pos.y, levelMiddleSquare.size.x, levelMiddleSquare.size.y, levelMiddleSquare.color);
		}
	}
}