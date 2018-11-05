#include "Player.h"

#include "Setup\game.h"
#include "setup/level.h"
#include "Screens\settings.h"
#include "Screens\gameplay.h"

namespace Juego
{
	cube player;
	static float playerAccelerationLeft = 0;
	static float playerAccelerationRight = 0;
	static float playerAccelerationUp = 0;
	static float playerAccelerationDown = 0;

	namespace Gameplay_Section
	{
		void createPlayer()
		{
			if (resolutionNormal) 
			{
				player.size = { 50, 50 };
				player.defaultSpeed = 500.0f;
			}
			else if (resolutionSmall) 
			{
				player.size = { 50 / resolutionSizeFix, 50 / resolutionSizeFix };
				player.defaultSpeed = 500.0f / resolutionSizeFix;
			}
			player.position = { (float)screenWidth / 2, obstacles[obBackground].pos.y + obstacles[obBackground].size.y - player.size.y};
			player.isAlive = true;
			player.inputActive = false;
			player.rotation = 0;
			player.textureTint = WHITE;
			player.isPlayerStickedOnWall = false;
			player.isPlayerStickedOnWallY = false;
			player.isPlayerStickedOnWall2 = false;
			player.isPlayerStickedOnWall2Y = false;
			player.activatedGravity = false;
			player.isInvertedGravityY = false;
		}
		
		void playerInput()
		{
			if (IsKeyPressed(playerKeys[GRAVITY]) && !player.activatedGravity)
			{
					if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare].pos.x,obstacles[obMiddleSquare].pos.y,obstacles[obMiddleSquare].size.x,obstacles[obMiddleSquare].size.y }))
					{
						player.activatedGravity = true;
						if (player.activatedGravity && player.isInvertedGravityX) player.position.x = player.position.x + 10;
						else if (player.activatedGravity && !player.isInvertedGravityX) player.position.x = player.position.x - 10;
					}
					else if (player.isPlayerStickedOnWall)
					{
						if (player.position.x < obstacles[obBackground].pos.x + (obstacles[obBackground].size.x / 2)) player.isInvertedGravityX = true; // true
						else if (player.position.x > obstacles[obBackground].pos.x + (obstacles[obBackground].size.x / 2)) player.isInvertedGravityX = false; // false

						player.activatedGravity = true;
						if (player.activatedGravity && player.isInvertedGravityX) player.position.x = player.position.x + 10;
						else if (player.activatedGravity && !player.isInvertedGravityX) player.position.x = player.position.x - 10;
					}
					else if (player.isPlayerStickedOnWallY)
					{
						player.position.y = player.position.y + 10;
					}
					else
					{
						player.activatedGravity = false;
					}
				
			}

			if (IsKeyDown(playerKeys[UP]) && (player.isPlayerStickedOnWall || player.isPlayerStickedOnWall2))
			{
				//if (player.position.y <= obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y) player.position.y = obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y;
				if (player.position.y <= obstacles[obBackground].pos.y) player.position.y = obstacles[obBackground].pos.y;
				else
				{
					playerAccelerationUp = playerAccelerationUp + 0.25f;

					if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
					else playerAccelerationDown = playerAccelerationDown - 0.25f;

					player.position.y -= playerAccelerationUp * GetFrameTime();
				}
			}
			else if (IsKeyDown(playerKeys[DOWN]) && (player.isPlayerStickedOnWall || player.isPlayerStickedOnWallY || player.isPlayerStickedOnWall2))
			{
				//if (player.position.y + player.size.y <= obstacles[obMiddleSquare].pos.y) player.position.y = obstacles[obMiddleSquare].pos.y - player.size.y;
				if (player.position.y + player.size.y > obstacles[obBackground].pos.y + obstacles[obBackground].size.y) player.position.y = obstacles[obBackground].pos.y + obstacles[obBackground].size.y - player.size.y;
				else 
				{
					playerAccelerationDown = playerAccelerationDown + 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.25f;

					player.position.y += playerAccelerationDown * GetFrameTime();
					//player.rotation = 10;
				}	
			}
			else if (IsKeyDown(playerKeys[RIGHT]) && !player.activatedGravity)
			{
				playerAccelerationRight = playerAccelerationRight + 0.25f;

				if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;
			}
			else if (IsKeyDown(playerKeys[LEFT]) && !player.activatedGravity)
			{

				playerAccelerationLeft = playerAccelerationLeft + 0.25f;

				if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
				else playerAccelerationRight = playerAccelerationRight - 0.25f;
			}
			else 
			{
				if(playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;

				if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
				else playerAccelerationRight = playerAccelerationRight - 0.25f;

				if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
				else playerAccelerationUp = playerAccelerationUp - 0.25f;

				if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
				else playerAccelerationDown = playerAccelerationDown - 0.25f;

				player.rotation = 0;
			}

			/*if (player.position.x + player.size.x >= obstacles[obMiddleSquare].pos.x || player.position.x <= obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x || player.position.y <= obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y && !player.isInvertedGravityY)
			{
				player.isPlayerStickedOnWall = true;
				player.textureTint = RED;
			}*/
			

				
				//else if (player.position.y + player.size.y <= obstacles[obMiddleSquare].pos.y) player.position.y = obstacles[obMiddleSquare].pos.y - player.size.y;
		}

		void playerUpdate()
		{
			if (playerAccelerationLeft >= player.defaultSpeed) playerAccelerationLeft = player.defaultSpeed;
			if (playerAccelerationRight >= player.defaultSpeed) playerAccelerationRight = player.defaultSpeed;
			if (playerAccelerationDown >= player.defaultSpeed) playerAccelerationDown = player.defaultSpeed;
			if (playerAccelerationUp >= player.defaultSpeed) playerAccelerationUp = player.defaultSpeed;

			//playerAccelerationRight

			//if (player.position.y > )
			//obstacles[i]

			//if (!player.isPlayerStickedOnWall && player.position.y + player.size.y < obstacles[obMiddleSquare].pos.y && !player.isInvertedGravityY && !player.activatedGravity) player.position.y += player.defaultSpeed*1.5f * GetFrameTime();
			if (!player.isPlayerStickedOnWall2 && !player.isPlayerStickedOnWall && !player.isPlayerStickedOnWallY && player.position.y < obstacles[obBackground].pos.y + obstacles[obBackground].size.y && !player.isInvertedGravityY && !player.activatedGravity) player.position.y += player.defaultSpeed*1.5f * GetFrameTime();
			else if (!player.isPlayerStickedOnWall2 && !player.isPlayerStickedOnWall && !player.isPlayerStickedOnWallY && player.position.y > obstacles[obBackground].pos.y && player.isInvertedGravityY && !player.activatedGravity) player.position.y -= player.defaultSpeed*1.5f * GetFrameTime();
			//else if ()

			//if (!player.isPlayerStickedOnWall && player.position.x + player.size.x < obstacles[obMiddleSquare].pos.x && player.isInvertedGravityX && player.activatedGravity) player.position.x += player.defaultSpeed*1.5f * GetFrameTime();
			//else if (!player.isPlayerStickedOnWall && player.position.x > obstacles[obMiddleSquare].pos.x && !player.isInvertedGravityX && player.activatedGravity) player.position.x -= player.defaultSpeed*3.0f * GetFrameTime();

			if (!player.isPlayerStickedOnWall && player.position.x < obstacles[obBackground].pos.x + obstacles[obBackground].size.x && player.isInvertedGravityX && player.activatedGravity) player.position.x += player.defaultSpeed*3.0f * GetFrameTime();
			else if (!player.isPlayerStickedOnWall && player.position.x > obstacles[obBackground].pos.x && !player.isInvertedGravityX && player.activatedGravity) player.position.x -= player.defaultSpeed*3.0f * GetFrameTime();

			//player.activatedGravity = false;

			/*if (player.position.y + player.size.y < obstacles[obMiddleSquare].pos.y)
			{
				playerAccelerationDown = 0;
				player.position.y = obstacles[obMiddleSquare].pos.y - player.size.y;
			}*/

			if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare].pos.x,obstacles[obMiddleSquare].pos.y,obstacles[obMiddleSquare].size.x,obstacles[obMiddleSquare].size.y }))
			{
				//player.position.x = obstacles[obMiddleSquare].pos.x - player.size.x;
				player.textureTint = PURPLE;
				
				//player.activatedGravity = true;

				if (player.position.x <= obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x && player.position.x > obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x - 10)
				{
					player.isInvertedGravityX = true;
					player.textureTint = BLUE;
				}
				else if (player.position.x + player.size.x >= obstacles[obMiddleSquare].pos.x && player.position.x + player.size.x <= obstacles[obMiddleSquare].pos.x + 10)
				{
					player.isInvertedGravityX = false;
					player.textureTint = YELLOW;
				}

				if (player.position.y + player.size.y >= obstacles[obMiddleSquare].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare].pos.y + 10)
				{
					player.isPlayerStickedOnWall = false;
					player.isPlayerStickedOnWall2 = true;
					player.activatedGravity = false;
					player.position.y = obstacles[obMiddleSquare].pos.y - player.size.y;
				}
				else if (player.position.y <= obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y && player.position.y >= obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y - 10)
				{
					player.isPlayerStickedOnWall = false;
					player.isPlayerStickedOnWall2 = true;
					player.activatedGravity = false;
					player.position.y = obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y;
				}
				else if (player.position.x + player.size.x >= obstacles[obMiddleSquare].pos.x && player.position.x + player.size.x <= obstacles[obMiddleSquare].pos.x + 10 && player.position.y + player.size.y >= obstacles[obMiddleSquare].pos.y && player.position.y <= obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y)
				{
					//player.isPlayerStickedOnWall = true;
					//player.isInvertedGravityX = false;
					player.isPlayerStickedOnWall = false;
					player.isPlayerStickedOnWall2 = true;
					player.activatedGravity = false;
					player.position.x = obstacles[obMiddleSquare].pos.x - player.size.x;
				}
				else if (player.position.x <= obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x && player.position.x > obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x - 10 && player.position.y + player.size.y >= obstacles[obMiddleSquare].pos.y && player.position.y <= obstacles[obMiddleSquare].pos.y + obstacles[obMiddleSquare].size.y)
				{
					//player.isPlayerStickedOnWall = true;
					player.isPlayerStickedOnWall = false;
					player.isPlayerStickedOnWall2 = true;
					player.activatedGravity = false;
					player.position.x = obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x;
				}

			}
			else if ((player.position.x <= obstacles[obBackground].pos.x || player.position.x + player.size.x >= obstacles[obBackground].pos.x + obstacles[obBackground].size.x ) && !player.isInvertedGravityY && !player.isPlayerStickedOnWallY)
			{
				//player.isPlayerStickedOnWallY = false;
				player.isPlayerStickedOnWall = true;
				player.isPlayerStickedOnWall2 = false;
				player.activatedGravity = false;
				player.textureTint = RED;
			}
			else if (player.position.y <= obstacles[obBackground].pos.y && !player.isInvertedGravityY)
			{
				player.isPlayerStickedOnWall = false;
				player.isPlayerStickedOnWallY = true;
				player.activatedGravity = false;
				player.textureTint = GREEN;
			}
			else
			{
				player.isPlayerStickedOnWallY = false;
				player.textureTint = WHITE;
				player.isPlayerStickedOnWall = false;
				player.isPlayerStickedOnWall2 = false;
				//player.activatedGravity = false;
			}

			if (player.position.y + player.size.y > obstacles[obBackground].pos.y + obstacles[obBackground].size.y)
			{
				playerAccelerationDown = 0;
				player.position.y = obstacles[obBackground].pos.y + obstacles[obBackground].size.y - player.size.y;
			}
			else
			{
				player.position.y += playerAccelerationDown * GetFrameTime();
			}

			if (player.position.y < obstacles[obBackground].pos.y)
			{
				playerAccelerationUp = 0;
				player.position.y = obstacles[obBackground].pos.y;
			}
			else
			{
				player.position.y -= playerAccelerationUp * GetFrameTime();
			}

			//if (player.position.x + player.size.x > obstacles[obBackground].pos.x + obstacles[obBackground].size.x)
			//{
			//	player.position.x = obstacles[obBackground].pos.x + obstacles[obBackground].size.x - player.size.x;
			//	
			//}

			//if (player.position.x < obstacles[obBackground].pos.x)
			//{
			//	player.position.x = obstacles[obBackground].pos.x;
			//	player.activatedGravity = false;
			//}

			/*if (player.position.x + player.size.x > obstacles[obMiddleSquare].pos.x)
			{
				playerAccelerationRight = 0;
				player.position.x = obstacles[obMiddleSquare].pos.x - player.size.x;
			}*/
			if (player.position.x + player.size.x > obstacles[obBackground].pos.x + obstacles[obBackground].size.x)
			{
				playerAccelerationRight = 0;
				player.position.x = obstacles[obBackground].pos.x + obstacles[obBackground].size.x - player.size.x;
			}
			else
			{
				player.position.x += playerAccelerationRight * GetFrameTime();
			}

			/*if (player.position.x < obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x)
			{
				playerAccelerationLeft = 0;
				player.position.x = obstacles[obMiddleSquare].pos.x + obstacles[obMiddleSquare].size.x;
				player.activatedGravity = false;
			}*/
			if (player.position.x <= obstacles[obBackground].pos.x)
			{
				playerAccelerationLeft = 0;
				player.position.x = obstacles[obBackground].pos.x;
				player.activatedGravity = false;

			}
			else
			{
				player.position.x -= playerAccelerationLeft * GetFrameTime();
			}

			/*for (int i = 0; i < maxObstacles; i++)
			{
				
			}*/

			
		}

		void playerDraw()
		{
			if (resolutionNormal)
			{

				DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.textureTint);
			}
			else if (resolutionSmall)
			{

				DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.textureTint);
			}
		}
	}
}