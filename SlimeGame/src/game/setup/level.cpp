#include "level.h"

#include "setup/game.h"
#include "screens/gameplay.h"

namespace Juego
{
	//obstacle levelBackground;
	//obstacle levelMiddleSquare;

	obstacle obBackground;
	obstacle obstacles[maxObstacles];
	obstacle spikes[maxSpikes];
	obstacle exit;

	int currentLevel = 1;

	Rectangle enemy01Source = { 0.0f,0.0f, 100,60 };
	Rectangle enemy02Source = { 0.0f,0.0f, 100,60 };
	Rectangle enemy03Source = { 0.0f,0.0f, 100,60 };


	//enemy01Destination = { player.position.x,player.position.y, 150,60 };

	//DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, BLANK); //player.textureTint {150,150,150,150}
	//DrawTexturePro(enemy01, enemy01Source, enemy01Destination, enemy01Origin, 0, WHITE);

	namespace Gameplay_Section
	{
		void createLevelBackground()
		{
			
		}

		void createLevelObstacles()
		{
			for (int i = 0;i < maxObstacles;i++)
			{
				obstacles[i].pos.x = 0;
				obstacles[i].pos.y = 0;
				obstacles[i].size.x = 0;
				obstacles[i].size.y = 0;
				obstacles[i].speed = 0;
				obstacles[i].isAlive = false;
				obstacles[i].color = BLANK;
			}

			for (int i = 0; i < maxSpikes; i++)
			{
				spikes[i].pos.x = 0;
				spikes[i].pos.y = 0;
				spikes[i].size.x = 0;
				spikes[i].size.y = 0;
				spikes[i].speed = 0;
				spikes[i].isAlive = false;
				spikes[i].color = BLANK;
			}

			obBackground.pos.x = 0 + 50;
			obBackground.pos.y = 0 + 50;
			obBackground.size.x = screenWidth - 100;
			obBackground.size.y = screenHeight - 100;
			obBackground.speed = 0;
			obBackground.isAlive = true;
			obBackground.color = GRAY;

			exit.pos.x = 0;
			exit.pos.y = 0;
			exit.size.x = 0;
			exit.size.y = 0;
			exit.speed = 0;
			exit.isAlive = false;
			exit.color = BLANK;

			switch (currentLevel)
			{
			case 1:
			{
				obstacles[obMiddleSquare].pos.x = (float)screenWidth / 6;
				obstacles[obMiddleSquare].pos.y = screenHeight / 2 - 100;
				obstacles[obMiddleSquare].size.x = 70;
				obstacles[obMiddleSquare].size.y = 600;
				obstacles[obMiddleSquare].speed = 0;
				obstacles[obMiddleSquare].isAlive = true;
				obstacles[obMiddleSquare].color = BLACK;

				obstacles[obMiddleSquare2].pos.x = (float)screenWidth / 2.7f;
				obstacles[obMiddleSquare2].pos.y = 0;
				obstacles[obMiddleSquare2].size.x = 70;
				obstacles[obMiddleSquare2].size.y = 500;
				obstacles[obMiddleSquare2].speed = 0;
				obstacles[obMiddleSquare2].isAlive = true;
				obstacles[obMiddleSquare2].color = BLACK;

				obstacles[obMiddleSquare3].pos.x = (float)screenWidth / 2.7f + 70;
				obstacles[obMiddleSquare3].pos.y = 0;
				obstacles[obMiddleSquare3].size.x = 300;
				obstacles[obMiddleSquare3].size.y = 300;
				obstacles[obMiddleSquare3].speed = 0;
				obstacles[obMiddleSquare3].isAlive = true;
				obstacles[obMiddleSquare3].color = BLACK;

				obstacles[obMiddleSquare4].pos.x = screenWidth / 1.9f;
				obstacles[obMiddleSquare4].pos.y = screenHeight/1.9f;
				obstacles[obMiddleSquare4].size.x = 600;
				obstacles[obMiddleSquare4].size.y = 400;
				obstacles[obMiddleSquare4].speed = 0;
				obstacles[obMiddleSquare4].isAlive = true;
				obstacles[obMiddleSquare4].color = BLACK;

				obstacles[obMiddleSquare5].pos.x = screenWidth / 1.3f;
				obstacles[obMiddleSquare5].pos.y = screenHeight / 3.1f;
				obstacles[obMiddleSquare5].size.x = 100;
				obstacles[obMiddleSquare5].size.y = 100;
				obstacles[obMiddleSquare5].speed = 0;
				obstacles[obMiddleSquare5].isAlive = true;
				obstacles[obMiddleSquare5].color = BLACK;

				obstacles[obMiddleSquare6].pos.x = screenWidth / 1.2f;
				obstacles[obMiddleSquare6].pos.y = screenHeight / 5.7f;
				obstacles[obMiddleSquare6].size.x = 300;
				obstacles[obMiddleSquare6].size.y = 50;
				obstacles[obMiddleSquare6].speed = 0;
				obstacles[obMiddleSquare6].isAlive = true;
				obstacles[obMiddleSquare6].color = BLACK;

				exit.pos.x = screenWidth / 1.11f;
				exit.pos.y = obstacles[obMiddleSquare6].pos.y - 80;
				exit.size.x = 75;
				exit.size.y = 115;
				exit.speed = 0;
				exit.isAlive = false;
				exit.color = SKYBLUE;
			}
			break;
			case 2:
			{
				obstacles[obMiddleSquare].pos.x = obBackground.pos.x;
				obstacles[obMiddleSquare].pos.y = screenHeight / 4.5f;
				obstacles[obMiddleSquare].size.x = 200;
				obstacles[obMiddleSquare].size.y = 600;
				obstacles[obMiddleSquare].speed = 0;
				obstacles[obMiddleSquare].isAlive = true;
				obstacles[obMiddleSquare].color = BLACK;

				spikes[0].pos.x = obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x;
				spikes[0].pos.y = screenHeight / 1.23f;
				spikes[0].size.x = 230;
				spikes[0].size.y = 100;
				spikes[0].speed = 0;
				spikes[0].isAlive = false;
				spikes[0].color = RED;

				obstacles[obMiddleSquare2].pos.x = (float)screenWidth / 2.7f;
				obstacles[obMiddleSquare2].pos.y = 0;
				obstacles[obMiddleSquare2].size.x = 70;
				obstacles[obMiddleSquare2].size.y = 425;
				obstacles[obMiddleSquare2].speed = 0;
				obstacles[obMiddleSquare2].isAlive = true;
				obstacles[obMiddleSquare2].color = BLACK;

				obstacles[obMiddleSquare3].pos.x = (float)screenWidth / 2.7f;
				obstacles[obMiddleSquare3].pos.y = screenHeight/1.5f;
				obstacles[obMiddleSquare3].size.x = 70;
				obstacles[obMiddleSquare3].size.y = 225;
				obstacles[obMiddleSquare3].speed = 0;
				obstacles[obMiddleSquare3].isAlive = true;
				obstacles[obMiddleSquare3].color = BLACK;

				spikes[1].pos.x = obstacles[obMiddleSquare3].pos.x + obstacles[obMiddleSquare3].size.x;
				spikes[1].pos.y = screenHeight / 1.23f;
				spikes[1].size.x = 700;
				spikes[1].size.y = 100;
				spikes[1].speed = 0;
				spikes[1].isAlive = false;
				spikes[1].color = RED;

				obstacles[obMiddleSquare4].pos.x = obstacles[obMiddleSquare3].pos.x + 200;
				obstacles[obMiddleSquare4].pos.y = screenHeight / 1.9f - 50;
				obstacles[obMiddleSquare4].size.x = 200;
				obstacles[obMiddleSquare4].size.y = 200;
				obstacles[obMiddleSquare4].speed = 0;
				obstacles[obMiddleSquare4].isAlive = true;
				obstacles[obMiddleSquare4].color = BLACK;

				obstacles[obMiddleSquare5].pos.x = obstacles[obMiddleSquare4].pos.x + 300;
				obstacles[obMiddleSquare5].pos.y = screenHeight / 1.9f - 100;
				obstacles[obMiddleSquare5].size.x = 150;
				obstacles[obMiddleSquare5].size.y = 150;
				obstacles[obMiddleSquare5].speed = 0;
				obstacles[obMiddleSquare5].isAlive = true;
				obstacles[obMiddleSquare5].color = BLACK;

				obstacles[obMiddleSquare6].pos.x = obstacles[obMiddleSquare2].pos.x;
				obstacles[obMiddleSquare6].pos.y = obBackground.pos.y;
				obstacles[obMiddleSquare6].size.x = 400;
				obstacles[obMiddleSquare6].size.y = 175;
				obstacles[obMiddleSquare6].speed = 0;
				obstacles[obMiddleSquare6].isAlive = true;
				obstacles[obMiddleSquare6].color = BLACK;

				obstacles[obMiddleSquare7].pos.x = obstacles[obMiddleSquare6].pos.x + obstacles[obMiddleSquare6].size.x;
				obstacles[obMiddleSquare7].pos.y = obstacles[obMiddleSquare6].pos.y + obstacles[obMiddleSquare6].size.y - 50;
				obstacles[obMiddleSquare7].size.x = 250;
				obstacles[obMiddleSquare7].size.y = 50;
				obstacles[obMiddleSquare7].speed = 0;
				obstacles[obMiddleSquare7].isAlive = true;
				obstacles[obMiddleSquare7].color = BLACK;

				exit.pos.x = obstacles[obMiddleSquare7].pos.x;
				exit.pos.y = obstacles[obMiddleSquare7].pos.y - 125;
				exit.size.x = 75;
				exit.size.y = 125;
				exit.speed = 0;
				exit.isAlive = false;
				exit.color = SKYBLUE;

			}
			break;
			case 3:
			{
				obstacles[obMiddleSquare].pos.x = screenWidth/2 - 50;
				obstacles[obMiddleSquare].pos.y = obBackground.pos.y;
				obstacles[obMiddleSquare].size.x = 100;
				obstacles[obMiddleSquare].size.y = 150;
				obstacles[obMiddleSquare].speed = 0;
				obstacles[obMiddleSquare].isAlive = true;
				obstacles[obMiddleSquare].color = BLACK;

				obstacles[obMiddleSquare2].pos.x = (float)screenWidth / 3.0f;
				obstacles[obMiddleSquare2].pos.y = obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y;
				obstacles[obMiddleSquare2].size.x = 500;
				obstacles[obMiddleSquare2].size.y = 385;
				obstacles[obMiddleSquare2].speed = 0;
				obstacles[obMiddleSquare2].isAlive = true;
				obstacles[obMiddleSquare2].color = BLACK;

				obstacles[obMiddleSquare3].pos.x = obBackground.pos.x;
				obstacles[obMiddleSquare3].pos.y = obBackground.pos.y;
				obstacles[obMiddleSquare3].size.x = 180;
				obstacles[obMiddleSquare3].size.y = 190;
				obstacles[obMiddleSquare3].speed = 0;
				obstacles[obMiddleSquare3].isAlive = true;
				obstacles[obMiddleSquare3].color = BLACK;

				obstacles[obMiddleSquare4].pos.x = (float)screenWidth / 3.0f - 250;
				obstacles[obMiddleSquare4].pos.y = screenHeight / 2.0f;
				obstacles[obMiddleSquare4].size.x = 270;
				obstacles[obMiddleSquare4].size.y = 50;
				obstacles[obMiddleSquare4].speed = 0;
				obstacles[obMiddleSquare4].isAlive = true;
				obstacles[obMiddleSquare4].color = BLACK;

				obstacles[obMiddleSquare5].pos.x = obstacles[obMiddleSquare4].pos.x;
				obstacles[obMiddleSquare5].pos.y = obstacles[obMiddleSquare4].pos.y + obstacles[obMiddleSquare4].size.y;
				obstacles[obMiddleSquare5].size.x = 25;
				obstacles[obMiddleSquare5].size.y = 200;
				obstacles[obMiddleSquare5].speed = 0;
				obstacles[obMiddleSquare5].isAlive = true;
				obstacles[obMiddleSquare5].color = BLACK;

				obstacles[obMiddleSquare6].pos.x = obstacles[obMiddleSquare4].pos.x + 125;
				obstacles[obMiddleSquare6].pos.y = obBackground.pos.y + obBackground.size.y - 200;
				obstacles[obMiddleSquare6].size.x = 25;
				obstacles[obMiddleSquare6].size.y = 200;
				obstacles[obMiddleSquare6].speed = 0;
				obstacles[obMiddleSquare6].isAlive = true;
				obstacles[obMiddleSquare6].color = BLACK;

				obstacles[obMiddleSquare7].pos.x = obstacles[obMiddleSquare].pos.x;
				obstacles[obMiddleSquare7].pos.y = obstacles[obMiddleSquare2].pos.y + obstacles[obMiddleSquare2].size.y;
				obstacles[obMiddleSquare7].size.x = 100;
				obstacles[obMiddleSquare7].size.y = 95;
				obstacles[obMiddleSquare7].speed = 0;
				obstacles[obMiddleSquare7].isAlive = true;
				obstacles[obMiddleSquare7].color = BLACK;

				obstacles[obMiddleSquare8].pos.x = obstacles[obMiddleSquare7].pos.x + 200;
				obstacles[obMiddleSquare8].pos.y = obBackground.pos.y + obBackground.size.y - 95;
				obstacles[obMiddleSquare8].size.x = 100;
				obstacles[obMiddleSquare8].size.y = 95;
				obstacles[obMiddleSquare8].speed = 0;
				obstacles[obMiddleSquare8].isAlive = true;
				obstacles[obMiddleSquare8].color = BLACK;

				spikes[0].pos.x = obBackground.pos.x; 
				spikes[0].pos.y = obstacles[obMiddleSquare4].pos.y; 
				spikes[0].size.x = 15;
				spikes[0].size.y = 150;
				spikes[0].speed = 0;
				spikes[0].isAlive = false;
				spikes[0].color = RED;

				spikes[1].pos.x = obstacles[obMiddleSquare4].pos.x - 15;
				spikes[1].pos.y = obstacles[obMiddleSquare4].pos.y;
				spikes[1].size.x = 15;
				spikes[1].size.y = 150;
				spikes[1].speed = 0;
				spikes[1].isAlive = false;
				spikes[1].color = RED;

				spikes[2].pos.x = obstacles[obMiddleSquare8].pos.x + obstacles[obMiddleSquare8].size.x;
				spikes[2].pos.y = obstacles[obMiddleSquare8].pos.y + obstacles[obMiddleSquare8].size.y - 80;
				spikes[2].size.x = 350;
				spikes[2].size.y = 80;
				spikes[2].speed = 0;
				spikes[2].isAlive = false;
				spikes[2].color = RED;

				spikes[3].pos.x = 1000;
				spikes[3].pos.y = obstacles[obMiddleSquare8].pos.y - obstacles[obMiddleSquare8].size.y - 80;
				spikes[3].size.x = 50;
				spikes[3].size.y = 50;
				spikes[3].speed = 0;
				spikes[3].isAlive = false;
				spikes[3].color = RED;

				spikes[4].pos.x = obstacles[obMiddleSquare8].pos.x - 370;
				spikes[4].pos.y = obstacles[obMiddleSquare8].pos.y + obstacles[obMiddleSquare8].size.y - 40;
				spikes[4].size.x = 90;
				spikes[4].size.y = 40;
				spikes[4].speed = 0;
				spikes[4].isAlive = false;
				spikes[4].color = RED;

				spikes[5].pos.x = 220;
				spikes[5].pos.y = obstacles[obMiddleSquare4].pos.y - obstacles[obMiddleSquare4].size.y - 30;
				spikes[5].size.x = 50;
				spikes[5].size.y = 50;
				spikes[5].speed = 0;
				spikes[5].isAlive = false;
				spikes[5].color = RED;

				spikes[6].pos.x = 1000;
				spikes[6].pos.y = obstacles[obMiddleSquare8].pos.y - obstacles[obMiddleSquare8].size.y - 320;
				spikes[6].size.x = 50;
				spikes[6].size.y = 50;
				spikes[6].speed = 0;
				spikes[6].isAlive = false;
				spikes[6].color = RED;


				exit.pos.x = screenWidth / 2 + 50;
				exit.pos.y = obBackground.pos.y;
				exit.size.x = 75;
				exit.size.y = 150;
				exit.speed = 0;
				exit.isAlive = false;
				exit.color = SKYBLUE;

				/*obstacles[obMiddleSquare].pos.x = screenWidth / 2 - 50;
				obstacles[obMiddleSquare].pos.y = obBackground.pos.y;
				obstacles[obMiddleSquare].size.x = 100;
				obstacles[obMiddleSquare].size.y = 150;
				obstacles[obMiddleSquare].speed = 0;
				obstacles[obMiddleSquare].isAlive = true;
				obstacles[obMiddleSquare].color = BLACK;*/

				/*

				


				spikes[1].pos.x = obstacles[obMiddleSquare3].pos.x + obstacles[obMiddleSquare3].size.x;
				spikes[1].pos.y = screenHeight / 1.23f;
				spikes[1].size.x = 700;
				spikes[1].size.y = 100;
				spikes[1].speed = 0;
				spikes[1].isAlive = false;
				spikes[1].color = RED;

				

				

				

				

				*/

			}
			break;
			}

		}

		void DrawLevel()
		{
			DrawRectangle(obBackground.pos.x, obBackground.pos.y, obBackground.size.x, obBackground.size.y, obBackground.color);
			DrawRectangle(exit.pos.x, exit.pos.y, exit.size.x, exit.size.y, exit.color);

			for (int i = 0; i < maxObstacles; i++)
			{
				DrawRectangle(obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].size.x, obstacles[i].size.y, obstacles[i].color);
			}

			for (int i = 0; i < maxSpikes; i++)
			{
				DrawRectangle(spikes[i].pos.x, spikes[i].pos.y, spikes[i].size.x, spikes[i].size.y, spikes[i].color);
			}

			if (currentLevel > 3)
			{
				DrawTextEx(mainFont, "THANKS FOR PLAYING", { screenWidth / 9.0f, screenHeight / 2.0f }, defaultFontSize / 1.2f, 1.0f, GREEN);
				DrawTextEx(mainFont, "OUR DEMO", { screenWidth / 7.0f, screenHeight / 1.5f }, defaultFontSize / 1.2f, 1.0f, GREEN);
			}
			//DrawRectangle(levelMiddleSquare.pos.x, levelMiddleSquare.pos.y, levelMiddleSquare.size.x, levelMiddleSquare.size.y, levelMiddleSquare.color);
		}
	}
}