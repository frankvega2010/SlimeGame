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

	static Rectangle slimeSource = { 0.0f,0.0f, 75,60 };
	static Rectangle slimeDestination;

	static int currentFrame = 0;

	//

	static Vector2 slimeOrigin = { 10,5 };

	static int buttonSelect = 0;
	static int buttonSelectSaveNumber = 0;
	static bool isButtonSoundPlaying = false;

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
			player.position = { (float)screenWidth / 3.7f, obBackground.pos.y + player.size.y };
			if(currentLevel == 1) player.position = { (float)screenWidth / 10, obBackground.pos.y + obBackground.size.y - player.size.y};
			else if(currentLevel == 2) player.position = { (float)screenWidth / 10, obBackground.pos.y + player.size.y };
			else if (currentLevel == 3) player.position = { (float)screenWidth / 3.2f, obBackground.pos.y + player.size.y };
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
		
		void playerGravityExec()
		{
			
			player.activatedGravity = true;
			if (player.activatedGravity && player.isInvertedGravityX) player.position.x = player.position.x + 10;
			else if (player.activatedGravity && !player.isInvertedGravityX) player.position.x = player.position.x - 10;
		}

		void playerInput()
		{
			if (IsKeyPressed(playerKeys[GRAVITY]) && !player.activatedGravity)
			{
				//PlaySound(slimeSplash);
				PlaySound(slimeJump);
				currentFrame = 2;
					if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare].pos.x,obstacles[obMiddleSquare].pos.y,obstacles[obMiddleSquare].size.x,obstacles[obMiddleSquare].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare2].pos.x,obstacles[obMiddleSquare2].pos.y,obstacles[obMiddleSquare2].size.x,obstacles[obMiddleSquare2].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare3].pos.x,obstacles[obMiddleSquare3].pos.y,obstacles[obMiddleSquare3].size.x,obstacles[obMiddleSquare3].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare4].pos.x,obstacles[obMiddleSquare4].pos.y,obstacles[obMiddleSquare4].size.x,obstacles[obMiddleSquare4].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare5].pos.x,obstacles[obMiddleSquare5].pos.y,obstacles[obMiddleSquare5].size.x,obstacles[obMiddleSquare5].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare6].pos.x,obstacles[obMiddleSquare6].pos.y,obstacles[obMiddleSquare6].size.x,obstacles[obMiddleSquare6].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare7].pos.x,obstacles[obMiddleSquare7].pos.y,obstacles[obMiddleSquare7].size.x,obstacles[obMiddleSquare7].size.y }))
					{
						playerGravityExec();
					}
					else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare8].pos.x,obstacles[obMiddleSquare8].pos.y,obstacles[obMiddleSquare8].size.x,obstacles[obMiddleSquare8].size.y }))
					{
						playerGravityExec();
					}
					else if (player.isPlayerStickedOnWall)
					{
						if (player.position.x < obBackground.pos.x + (obBackground.size.x / 2)) player.isInvertedGravityX = true; // true
						else if (player.position.x > obBackground.pos.x + (obBackground.size.x / 2)) player.isInvertedGravityX = false; // false

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
						//currentFrame = 2;
					}
					
			}

			if (IsKeyDown(playerKeys[UP]) && (player.isPlayerStickedOnWall || player.isPlayerStickedOnWall2))
			{
				PlayMusicStream(slimeMove);

				if (player.position.y <= obBackground.pos.y) player.position.y = obBackground.pos.y;
				else if (currentLevel == 1 && player.position.y <= obstacles[obMiddleSquare3].pos.y + obstacles[obMiddleSquare3].size.y && player.position.x + player.size.x >= obstacles[obMiddleSquare3].pos.x && player.position.x + player.size.x <= obstacles[obMiddleSquare3].pos.x + obstacles[obMiddleSquare3].size.x)
				{
					player.position.y = obstacles[obMiddleSquare3].pos.y + obstacles[obMiddleSquare3].size.y;
					playerAccelerationUp = 0;
				}
				else if (currentLevel == 2 && player.position.y <= obstacles[obMiddleSquare6].pos.y + obstacles[obMiddleSquare6].size.y && player.position.x >= obstacles[obMiddleSquare6].pos.x && player.position.x + player.size.x <= obstacles[obMiddleSquare6].pos.x + obstacles[obMiddleSquare6].size.x)
				{
					player.position.y = obstacles[obMiddleSquare6].pos.y + obstacles[obMiddleSquare6].size.y;
					playerAccelerationUp = 0;
				}
				else if (currentLevel == 3 && player.position.y <= obstacles[obMiddleSquare4].pos.y + obstacles[obMiddleSquare4].size.y && player.position.y >= obstacles[obMiddleSquare4].pos.y + (obstacles[obMiddleSquare4].size.y/2) && player.position.x + player.size.x >= obstacles[obMiddleSquare4].pos.x && player.position.x + player.size.x <= obstacles[obMiddleSquare4].pos.x + obstacles[obMiddleSquare4].size.x)
				{
					player.position.y = obstacles[obMiddleSquare4].pos.y + obstacles[obMiddleSquare4].size.y;
					playerAccelerationUp = 0;
				}
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
				PlayMusicStream(slimeMove);

				if (player.position.y + player.size.y > obBackground.pos.y + obBackground.size.y) player.position.y = obBackground.pos.y + obBackground.size.y - player.size.y;
				else if (currentLevel == 2 && player.position.y + player.size.y >= obstacles[obMiddleSquare7].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare7].pos.y + obstacles[obMiddleSquare7].size.y - 0.1f && player.position.x + player.size.x >= obstacles[obMiddleSquare7].pos.x && player.position.x + player.size.x <= obstacles[obMiddleSquare7].pos.x + obstacles[obMiddleSquare7].size.x)
				{
					player.position.y = obstacles[obMiddleSquare7].pos.y - player.size.y;
					playerAccelerationDown = 0;
				}
				else if (currentLevel == 3 && player.position.y + player.size.y >= obstacles[obMiddleSquare2].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare2].pos.y + obstacles[obMiddleSquare2].size.y - 0.1f && player.position.x + player.size.x >= obstacles[obMiddleSquare2].pos.x + 0.2f && player.position.x + player.size.x <= obstacles[obMiddleSquare2].pos.x + obstacles[obMiddleSquare2].size.x)
				{
					player.position.y = obstacles[obMiddleSquare2].pos.y - player.size.y - 0.1f;
					playerAccelerationDown = 0;
				}
				else if (currentLevel == 3 && player.position.y + player.size.y >= obstacles[obMiddleSquare4].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare4].pos.y + obstacles[obMiddleSquare4].size.y && player.position.x + player.size.x >= obstacles[obMiddleSquare4].pos.x + 0.3f && player.position.x + player.size.x <= obstacles[obMiddleSquare4].pos.x + obstacles[obMiddleSquare4].size.x)
				{
					player.position.y = obstacles[obMiddleSquare4].pos.y - player.size.y;
					playerAccelerationDown = 0;
				}
				else 
				{
					playerAccelerationDown = playerAccelerationDown + 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.25f;

					player.position.y += playerAccelerationDown * GetFrameTime();
				}	
			}
			else if (IsKeyDown(playerKeys[RIGHT]) && !player.activatedGravity)
			{
				PlayMusicStream(slimeMove);
				//currentFrame = 1;
			if (currentLevel == 3 && player.position.y + player.size.y >= obstacles[obMiddleSquare7].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare7].pos.y + obstacles[obMiddleSquare7].size.y && player.position.x + player.size.x >= obstacles[obMiddleSquare7].pos.x + 0.5f && player.position.x <= obstacles[obMiddleSquare7].pos.x + obstacles[obMiddleSquare7].size.x - 0.5f)
			{
				player.position.x = obstacles[obMiddleSquare7].pos.x - player.size.x;
				playerAccelerationRight = 0;
			}
			else
			{
				playerAccelerationRight = playerAccelerationRight + 0.25f;

				if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;
			}

			}
			else if (IsKeyDown(playerKeys[LEFT]) && !player.activatedGravity)
			{
				PlayMusicStream(slimeMove);
				//currentFrame = 1;
			if (currentLevel == 3 && player.position.y + player.size.y >= obstacles[obMiddleSquare5].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare5].pos.y + obstacles[obMiddleSquare5].size.y && player.position.x + player.size.x >= obstacles[obMiddleSquare5].pos.x + 0.2f && player.position.x <= obstacles[obMiddleSquare5].pos.x + obstacles[obMiddleSquare5].size.x)
			{
				player.position.x = obstacles[obMiddleSquare5].pos.x + obstacles[obMiddleSquare5].size.x;
				playerAccelerationLeft = 0;
			}
			else if (currentLevel == 3 && player.position.y + player.size.y >= obstacles[obMiddleSquare7].pos.y && player.position.y + player.size.y <= obstacles[obMiddleSquare7].pos.y + obstacles[obMiddleSquare7].size.y && player.position.x + player.size.x >= obstacles[obMiddleSquare7].pos.x + 0.5f && player.position.x <= obstacles[obMiddleSquare7].pos.x + obstacles[obMiddleSquare7].size.x - 0.5f)
			{
				player.position.x = obstacles[obMiddleSquare7].pos.x + obstacles[obMiddleSquare7].size.x;
				playerAccelerationLeft = 0;
			}
			else
			{
				playerAccelerationLeft = playerAccelerationLeft + 0.25f;

				if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
				else playerAccelerationRight = playerAccelerationRight - 0.25f;
			}
				
			}
			else 
			{
				//currentFrame = 0;

				if(playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;

				if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
				else playerAccelerationRight = playerAccelerationRight - 0.25f;

				if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
				else playerAccelerationUp = playerAccelerationUp - 0.25f;

				if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
				else playerAccelerationDown = playerAccelerationDown - 0.25f;

				player.rotation = 0;

				StopMusicStream(slimeMove);
			}
		}

		void playerCollisions(int obstacle)
		{
			player.textureTint = PURPLE;

			if (player.position.x <= obstacles[obstacle].pos.x + obstacles[obstacle].size.x && player.position.x > obstacles[obstacle].pos.x + obstacles[obstacle].size.x - 10)
			{
				player.isInvertedGravityX = true;
				player.textureTint = BLUE;
				
				
			}
			else if (player.position.x + player.size.x >= obstacles[obstacle].pos.x && player.position.x + player.size.x <= obstacles[obstacle].pos.x + 10)
			{
				player.isInvertedGravityX = false;
				player.textureTint = YELLOW;
				
			}

			if (player.position.y + player.size.y >= obstacles[obstacle].pos.y && player.position.y + player.size.y <= obstacles[obstacle].pos.y + 10)
			{
				player.isPlayerStickedOnWall = false;
				player.isPlayerStickedOnWall2 = true;
				player.activatedGravity = false;
				player.position.y = obstacles[obstacle].pos.y - player.size.y;
				currentFrame = 0;
				buttonSelect = obstacle;
				//playerAccelerationUp = 0;
			}
			else if (player.position.y <= obstacles[obstacle].pos.y + obstacles[obstacle].size.y && player.position.y >= obstacles[obstacle].pos.y + obstacles[obstacle].size.y - 10)
			{
				player.isPlayerStickedOnWall = false;
				player.isPlayerStickedOnWall2 = true;
				player.activatedGravity = false;
				player.position.y = obstacles[obstacle].pos.y + obstacles[obstacle].size.y;
				currentFrame = 5;
				buttonSelect = obstacle;
				
				//playerAccelerationDown = 0;
			}
			else if (player.position.x + player.size.x >= obstacles[obstacle].pos.x && player.position.x + player.size.x <= obstacles[obstacle].pos.x + 10 && player.position.y + player.size.y >= obstacles[obstacle].pos.y && player.position.y <= obstacles[obstacle].pos.y + obstacles[obstacle].size.y)
			{
				player.isPlayerStickedOnWall = false;
				player.isPlayerStickedOnWall2 = true;
				player.activatedGravity = false;
				player.position.x = obstacles[obstacle].pos.x - player.size.x + 0.1f;
				currentFrame = 6;
				buttonSelect = obstacle;
				//playerAccelerationRight = 0;
			}
			else if (player.position.x <= obstacles[obstacle].pos.x + obstacles[obstacle].size.x && player.position.x > obstacles[obstacle].pos.x + obstacles[obstacle].size.x - 10 && player.position.y + player.size.y >= obstacles[obstacle].pos.y && player.position.y <= obstacles[obstacle].pos.y + obstacles[obstacle].size.y)
			{
				player.isPlayerStickedOnWall = false;
				player.isPlayerStickedOnWall2 = true;
				player.activatedGravity = false;
				player.position.x = obstacles[obstacle].pos.x + obstacles[obstacle].size.x - 0.1f;
				currentFrame = 4;
				buttonSelect = obstacle;
				//playerAccelerationLeft = 0;
			}
			else
			{
				buttonSelect = -1;
			}

			if (buttonSelect != buttonSelectSaveNumber && buttonSelect != -1)
			{
				isButtonSoundPlaying = false;
			}

			if (buttonSelect == obstacle)
			{
				if (!(isButtonSoundPlaying))
				{
					PlaySound(slimeSplash);
					isButtonSoundPlaying = true;
					buttonSelectSaveNumber = obstacle;
				}
			}
		}

		void playerUpdate()
		{
			UpdateMusicStream(slimeMove);
			slimeSource.x = (float)currentFrame*(float)slime.width / 8;

			if (playerAccelerationLeft >= player.defaultSpeed) playerAccelerationLeft = player.defaultSpeed;
			if (playerAccelerationRight >= player.defaultSpeed) playerAccelerationRight = player.defaultSpeed;
			if (playerAccelerationDown >= player.defaultSpeed) playerAccelerationDown = player.defaultSpeed;
			if (playerAccelerationUp >= player.defaultSpeed) playerAccelerationUp = player.defaultSpeed;

			if (!player.isPlayerStickedOnWall2 && !player.isPlayerStickedOnWall && !player.isPlayerStickedOnWallY && player.position.y < obBackground.pos.y + obBackground.size.y && !player.isInvertedGravityY && !player.activatedGravity) player.position.y += player.defaultSpeed*1.5f * GetFrameTime();
			else if (!player.isPlayerStickedOnWall2 && !player.isPlayerStickedOnWall && !player.isPlayerStickedOnWallY && player.position.y > obBackground.pos.y && player.isInvertedGravityY && !player.activatedGravity) player.position.y -= player.defaultSpeed*1.5f * GetFrameTime();

			if (!player.isPlayerStickedOnWall && player.position.x < obBackground.pos.x + obBackground.size.x && player.isInvertedGravityX && player.activatedGravity) player.position.x += player.defaultSpeed*3.0f * GetFrameTime();
			else if (!player.isPlayerStickedOnWall && player.position.x > obBackground.pos.x && !player.isInvertedGravityX && player.activatedGravity) player.position.x -= player.defaultSpeed*3.0f * GetFrameTime();

			//////////////////////////////////--------------------------
			
			if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { exit.pos.x,exit.pos.y,exit.size.x,exit.size.y }))
			{
				if (currentLevel < 4) currentLevel++;
				
				InitGameplayVariables();
				//playerCollisions(obMiddleSquare7);
			}

			for (int i = 0; i < maxSpikes; i++)
			{
				if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { spikes[i].pos.x,spikes[i].pos.y,spikes[i].size.x,spikes[i].size.y }))
				{
					createPlayer();
					//playerCollisions(obMiddleSquare7);
				}
			}

				if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare].pos.x,obstacles[obMiddleSquare].pos.y,obstacles[obMiddleSquare].size.x,obstacles[obMiddleSquare].size.y }))
				{
					playerCollisions(obMiddleSquare);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare2].pos.x,obstacles[obMiddleSquare2].pos.y,obstacles[obMiddleSquare2].size.x,obstacles[obMiddleSquare2].size.y }))
				{
					playerCollisions(obMiddleSquare2);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare3].pos.x,obstacles[obMiddleSquare3].pos.y,obstacles[obMiddleSquare3].size.x,obstacles[obMiddleSquare3].size.y }))
				{
					playerCollisions(obMiddleSquare3);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare4].pos.x,obstacles[obMiddleSquare4].pos.y,obstacles[obMiddleSquare4].size.x,obstacles[obMiddleSquare4].size.y }))
				{
					playerCollisions(obMiddleSquare4);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare5].pos.x,obstacles[obMiddleSquare5].pos.y,obstacles[obMiddleSquare5].size.x,obstacles[obMiddleSquare5].size.y }))
				{
					playerCollisions(obMiddleSquare5);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare6].pos.x,obstacles[obMiddleSquare6].pos.y,obstacles[obMiddleSquare6].size.x,obstacles[obMiddleSquare6].size.y }))
				{
					playerCollisions(obMiddleSquare6);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare7].pos.x,obstacles[obMiddleSquare7].pos.y,obstacles[obMiddleSquare7].size.x,obstacles[obMiddleSquare7].size.y }))
				{
					playerCollisions(obMiddleSquare7);
				}
				else if (CheckCollisionRecs({ player.position.x, player.position.y, player.size.x, player.size.y }, { obstacles[obMiddleSquare8].pos.x,obstacles[obMiddleSquare8].pos.y,obstacles[obMiddleSquare8].size.x,obstacles[obMiddleSquare8].size.y }))
				{
					playerCollisions(obMiddleSquare8);
				}
				else if ((player.position.x <= obBackground.pos.x || player.position.x + player.size.x >= obBackground.pos.x + obBackground.size.x) && !player.isInvertedGravityY && !player.isPlayerStickedOnWallY)
				{
					player.isPlayerStickedOnWall = true;
					player.isPlayerStickedOnWall2 = false;
					player.activatedGravity = false;
					player.textureTint = RED;
				}
				else if (player.position.y <= obBackground.pos.y && !player.isInvertedGravityY)
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
				}

			
				


			//////////////////////////////////--------------------------

			if (player.position.y + player.size.y > obBackground.pos.y + obBackground.size.y)
			{
				playerAccelerationDown = 0;
				player.position.y = obBackground.pos.y + obBackground.size.y - player.size.y;
				currentFrame = 0;
			}
			else
			{
				player.position.y += playerAccelerationDown * GetFrameTime();
			}

			if (player.position.y <= obBackground.pos.y)
			{
				playerAccelerationUp = 0;
				player.position.y = obBackground.pos.y;
				currentFrame = 5;
			}
			else
			{
				player.position.y -= playerAccelerationUp * GetFrameTime();
			}

			if (player.position.x + player.size.x > obBackground.pos.x + obBackground.size.x)
			{
				playerAccelerationRight = 0;
				player.position.x = obBackground.pos.x + obBackground.size.x - player.size.x;
				currentFrame = 6;
			}
			else
			{
				player.position.x += playerAccelerationRight * GetFrameTime();
			}

			if (player.position.x <= obBackground.pos.x)
			{
				playerAccelerationLeft = 0;
				player.position.x = obBackground.pos.x;
				player.activatedGravity = false;
				currentFrame = 4;

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
				slimeDestination = { player.position.x,player.position.y, 75,60 };
				
				DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, BLANK); //player.textureTint {150,150,150,150}
				DrawTexturePro(slime, slimeSource, slimeDestination, slimeOrigin, player.rotation, WHITE);
				
			}
			else if (resolutionSmall)
			{

				DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.textureTint);
			}
		}
	}
}