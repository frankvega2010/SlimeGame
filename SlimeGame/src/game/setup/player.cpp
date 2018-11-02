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
			player.position = { (float)screenWidth / 2, levelBackground.pos.y + levelBackground.size.y - player.size.y };
			player.isAlive = true;
			player.inputActive = false;
			player.rotation = 0;
			player.textureTint = WHITE;
			player.isPlayerStickedOnWall = false;
			player.activatedGravity = false;
		}
		
		void playerInput()
		{
			if (IsKeyPressed(playerKeys[GRAVITY]))
			{
				//player.isInvertedGravityY =! player.isInvertedGravityY;
				if (player.isPlayerStickedOnWall && player.position.y > levelBackground.pos.y)
				{
					player.activatedGravity = true;
					if (player.position.x < levelBackground.pos.x + (levelBackground.size.x/2)) player.isInvertedGravityX = true;
					else if (player.position.x > levelBackground.pos.x + (levelBackground.size.x / 2)) player.isInvertedGravityX = false;
					
				}

				if (player.activatedGravity && player.isInvertedGravityX) player.position.x = player.position.x + 10;
				else if (player.activatedGravity && !player.isInvertedGravityX) player.position.x = player.position.x - 10;
			}

			if (IsKeyDown(playerKeys[UP]) && player.isPlayerStickedOnWall)
			{
				if (player.position.y <= levelBackground.pos.y) player.position.y = levelBackground.pos.y;
				else
				{
					playerAccelerationUp = playerAccelerationUp + 0.25f;

					if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
					else playerAccelerationDown = playerAccelerationDown - 0.25f;

					player.position.y -= playerAccelerationUp * GetFrameTime();
					//player.rotation = 350;
				}					
			}
			else if (IsKeyDown(playerKeys[DOWN]) && player.isPlayerStickedOnWall)
			{
				if (player.position.y + player.size.y > levelBackground.pos.y + levelBackground.size.y) player.position.y = levelBackground.pos.y + levelBackground.size.y - player.size.y;
				else
				{
					playerAccelerationDown = playerAccelerationDown + 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.25f;

					player.position.y += playerAccelerationDown * GetFrameTime();
					//player.rotation = 10;
				}	
			}
			else if (IsKeyDown(playerKeys[RIGHT]))
			{
				playerAccelerationRight = playerAccelerationRight + 0.25f;

				if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;
			}
			else if (IsKeyDown(playerKeys[LEFT]))
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

			if (player.position.x <= levelBackground.pos.x || player.position.x + player.size.x >= levelBackground.pos.x + levelBackground.size.x || player.position.y <= levelBackground.pos.y && !player.isInvertedGravityY)
			{
				player.isPlayerStickedOnWall = true;
				player.textureTint = RED;
			}
			else
			{
				player.textureTint = WHITE;
				player.isPlayerStickedOnWall = false;
			}
		}

		void playerUpdate()
		{
			if (playerAccelerationLeft >= player.defaultSpeed) playerAccelerationLeft = player.defaultSpeed;
			if (playerAccelerationRight >= player.defaultSpeed) playerAccelerationRight = player.defaultSpeed;
			if (playerAccelerationDown >= player.defaultSpeed) playerAccelerationDown = player.defaultSpeed;
			if (playerAccelerationUp >= player.defaultSpeed) playerAccelerationUp = player.defaultSpeed;

			//playerAccelerationRight
			
			//if (player.position.y > )
			if (!player.isPlayerStickedOnWall && player.position.y < levelBackground.pos.y + levelBackground.size.y && !player.isInvertedGravityY && !player.activatedGravity) player.position.y += player.defaultSpeed*1.5f * GetFrameTime();
			else if (!player.isPlayerStickedOnWall && player.position.y > levelBackground.pos.y && player.isInvertedGravityY && !player.activatedGravity) player.position.y -= player.defaultSpeed*1.5f * GetFrameTime();

			if (!player.isPlayerStickedOnWall && player.position.x < levelBackground.pos.x + levelBackground.size.x && player.isInvertedGravityX && player.activatedGravity) player.position.x += player.defaultSpeed*3.0f * GetFrameTime();
			else if (!player.isPlayerStickedOnWall && player.position.x > levelBackground.pos.x && !player.isInvertedGravityX && player.activatedGravity) player.position.x -= player.defaultSpeed*3.0f * GetFrameTime();

			if (player.position.y + player.size.y > levelBackground.pos.y + levelBackground.size.y)
			{
				playerAccelerationDown = 0;
				player.position.y = levelBackground.pos.y + levelBackground.size.y - player.size.y;
			} 
			else
			{
				player.position.y += playerAccelerationDown * GetFrameTime();
			}

			if (player.position.y < levelBackground.pos.y)
			{
				playerAccelerationUp = 0;
				player.position.y = levelBackground.pos.y;
			}
			else
			{
				player.position.y -= playerAccelerationUp * GetFrameTime();
			}

			if (player.position.x + player.size.x > levelBackground.pos.x + levelBackground.size.x)
			{
				player.position.x = levelBackground.pos.x + levelBackground.size.x - player.size.x;
				player.activatedGravity = false;
			}
			if (player.position.x < levelBackground.pos.x)
			{
				player.position.x = levelBackground.pos.x;
				player.activatedGravity = false;
			}

			if (player.position.x + player.size.x > levelBackground.pos.x + levelBackground.size.x) 
			{
				playerAccelerationRight = 0;
				player.position.x = levelBackground.pos.x + levelBackground.size.x - player.size.x;
			} 
			else
			{
				player.position.x += playerAccelerationRight * GetFrameTime();
			}

			if (player.position.x <= levelBackground.pos.x) 
			{
				playerAccelerationLeft = 0;
				player.position.x = levelBackground.pos.x;
			} 
			else
			{
				player.position.x -= playerAccelerationLeft * GetFrameTime();
			}
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