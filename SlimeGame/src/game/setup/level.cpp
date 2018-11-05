#include "level.h"

#include "setup/game.h"

namespace Juego
{
	//obstacle levelBackground;
	//obstacle levelMiddleSquare;

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

			obstacles[obBackground].pos.x = 0 + 50;
			obstacles[obBackground].pos.y = 0 + 50;
			obstacles[obBackground].size.x = screenWidth - 100;
			obstacles[obBackground].size.y = screenHeight - 100;
			obstacles[obBackground].speed = 0;
			obstacles[obBackground].isAlive = true;
			obstacles[obBackground].color = GRAY;

			obstacles[obMiddleSquare].pos.x = screenWidth/2 - 200;
			obstacles[obMiddleSquare].pos.y = screenHeight/2 - 200;
			obstacles[obMiddleSquare].size.x = 400;
			obstacles[obMiddleSquare].size.y = 400;
			obstacles[obMiddleSquare].speed = 0;
			obstacles[obMiddleSquare].isAlive = true;
			obstacles[obMiddleSquare].color = BLACK;
		}

		void DrawLevel()
		{
			for (int i = 0; i < maxObstacles; i++)
			{
				DrawRectangle(obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].size.x, obstacles[i].size.y, obstacles[i].color);
			}
			//DrawRectangle(levelMiddleSquare.pos.x, levelMiddleSquare.pos.y, levelMiddleSquare.size.x, levelMiddleSquare.size.y, levelMiddleSquare.color);
		}
	}
}