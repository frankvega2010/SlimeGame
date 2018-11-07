#include "gameplay.h"

#include "setup/game.h"
#include "setup/player.h"
#include "screens/settings.h"
#include "screens/menu.h"
#include "setup/level.h"

namespace Juego
{
	bool gameON = true;

	int playerKeys[MAX];

	static const int maxButtons = 3;
	static Buttons buttons[maxButtons];
	static Buttons pauseButton;
	static int buttonDistance = 0;
	static int buttonSelect = 0;
	static Color optionColor = RED;

	static bool gamePaused = false;
	
	static bool timerON = true;

	static Rectangle pauseBoxRec;

	static bool isButtonSoundPlaying = false;
	static int buttonSelectSaveNumber = 0;

	Sound slimeJump;
	Sound slimeSplash;
	Music slimeMove;
	Music backgroundSong;

	static Image slimeImage;
	static Image enemyImage;
	//static Image levelBackgound01Image;

	Texture2D slime;
	Texture2D enemy01;
	static Texture2D levelBackground;
	static Texture2D levelBackground01;
	static Texture2D levelBackground02;
	static Texture2D levelBackground03;

	static int speedEnemy = 200.0f;
	static int speedEnemy2 = 200.0f;
	static int speedEnemy3 = 260.0f;

	static int currentFrameEnemy01a = 0;
	static int currentFrameEnemy02a = 0;
	static int currentFrameEnemy03a = 0;
	static int currentFrameEnemy01b = 2;

	static Rectangle enemy01Destination;
	static Rectangle enemy02Destination;
	static Rectangle enemy03Destination;

	static Vector2 enemy01Origin = { 30,10 };

	namespace Gameplay_Section
	{
		static void createPauseButtons()
		{

			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.5f;
				buttons[i].position.y = (float)screenHeight / 3.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;

				if (resolutionNormal) buttons[i].height = (float)screenHeight / 12.0f;
				else if (resolutionSmall) buttons[i].height = (float)screenHeight / 14.0f;

				buttons[i].selected = false;
				buttons[i].defaultColor = GOLD;
				buttons[i].messageColor = BLANK;

				if (resolutionNormal && !(resolutionBig)) buttonDistance = buttonDistance + 100;
				else if (resolutionSmall) buttonDistance = buttonDistance + 60;
				else if (resolutionBig && resolutionNormal) buttonDistance = buttonDistance + 125;
			}

			pauseButton.position.x = (float)screenWidth / 1.4f;
			pauseButton.position.y = (float)screenHeight / 14.0f;
			pauseButton.width = (float)screenWidth / 18.0f;


			pauseBoxRec = { buttons[0].position.x - (screenWidth / 50), buttons[0].position.y - (screenHeight / 30), (float)screenWidth / 4.2f, (float)screenHeight / 2.5f };
			pauseButton.height = (float)screenHeight / 12.0f;

			pauseButton.selected = false;
			pauseButton.defaultColor = DARKGREEN;
			pauseButton.messageColor = BLANK;
		}

		void InitGameplayVariables()
		{
			timerON = true;
			createPauseButtons();
			createLevelBackground();
			createLevelObstacles();
			createPlayer();
		}

		void InitGameplayParallax()
		{

		}

		void InitGameplayScreen()
		{
			currentLevel = 1;

			if (resolutionNormal)
			{
				slimeJump = LoadSound("res/assets/sounds/slimejump.wav");
				slimeSplash = LoadSound("res/assets/sounds/slimesplash.wav");
				slimeMove = LoadMusicStream("res/assets/sounds/slimemove.ogg");
				backgroundSong = LoadMusicStream("res/assets/sounds/song.ogg");

				levelBackground = LoadTexture("res/assets/textures/levelbackground.png");
				levelBackground01 = LoadTexture("res/assets/textures/levelbackground01.png");
				levelBackground02 = LoadTexture("res/assets/textures/levelbackground02.png");
				levelBackground03 = LoadTexture("res/assets/textures/levelbackground03.png");

				slimeImage = LoadImage("res/assets/textures/playerspritesheet.png");
				ImageResize(&slimeImage, 600, 60);// 300 50
				slime = LoadTextureFromImage(slimeImage);

				enemyImage = LoadImage("res/assets/textures/enemyspritessheet.png");
				ImageResize(&enemyImage, 400, 60);// 150 60 mitad
				enemy01 = LoadTextureFromImage(enemyImage);

				//enemyShipImage = LoadImage("res/assets/textures/enemy01.png");
				//ImageResize(&enemyShipImage, 180, 70);
				//enemyShip = LoadTextureFromImage(enemyShipImage);

				//pauseMenuImage = LoadImage("res/assets/textures/pausemenu.png");
				//ImageResize(&pauseMenuImage, pauseBoxRec.width, pauseBoxRec.height);
				//pauseMenu = LoadTextureFromImage(pauseMenuImage);

				//UnloadImage(pauseMenuImage);
				UnloadImage(slimeImage);
				UnloadImage(enemyImage);
				//UnloadImage(enemyShipImage);

			}
			else if (resolutionSmall)
			{
				//shipImage = LoadImage("res/assets/textures/player_ship01v2.png");
				//ImageResize(&shipImage, 300/1.5f, 70/1.5f);// 150 70
				//ship = LoadTextureFromImage(shipImage);

				//enemyShipImage = LoadImage("res/assets/textures/enemy01.png");
				//ImageResize(&enemyShipImage, 180 / 1.5f, 70 / 1.5f);
				//enemyShip = LoadTextureFromImage(enemyShipImage);

				//pauseMenuImage = LoadImage("res/assets/textures/pausemenu.png");
				//ImageResize(&pauseMenuImage, pauseBoxRec.width, pauseBoxRec.height);
				//pauseMenu = LoadTextureFromImage(pauseMenuImage);

				//UnloadImage(pauseMenuImage);
				//UnloadImage(shipImage);
				//UnloadImage(enemyShipImage);
			}

			#ifdef AUDIO
			ship_shoot01 = LoadSound("res/assets/sounds/shoot01.wav");
			SetSoundVolume(ship_shoot01, soundVolume);

			enemy_explode01 = LoadSound("res/assets/sounds/explosion1.wav");
			SetSoundVolume(enemy_explode01, soundVolume);

			SetSoundVolume(button_select01, soundVolume);
			SetSoundVolume(button_navigate01, soundVolume);
			#endif

			PlayMusicStream(backgroundSong);
			isScreenFinished = false;
		}

		static void GameplayInput()
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pauseButton.selected)
			{
				//PlaySound(button_select01);
				gamePaused = true;
				gameON = false;
			}

			// Player Input
			if (gameON)
			{
				timerON = true;
				playerInput();
			}
			else ShowCursor();

			if (!gamePaused)
			{
				if (IsKeyPressed(KEY_ESCAPE))
				{
					//PlaySound(button_select01);
					//crosshairColor = BLANK;
					gamePaused = true;
					gameON = false;
				}
			}
			else
			{

				for (int i = 0; i < maxButtons; i++)
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttons[i].selected || IsKeyPressed(KEY_ENTER) && buttons[i].selected)
					{
						//PlaySound(button_select01);
						switch (i)
						{
						case 0:
							gamePaused = false;
							timerON = true;
							gameON = true;
							break;
						case 1:
							RestartPhase();
							break;
						case 2:
							buttonOption = buttonQuitToMenu;
							isScreenFinished = true;
							break;
						}
						buttons[i].selected = false;
					}
				}

				if (IsKeyPressed(KEY_ESCAPE))
				{
					//PlaySound(button_select01);
					gamePaused = false;
					timerON = true;
					gameON = true;
				}
			}
		}

		void UpdateGameplayScreen()
		{	
			UpdateMusicStream(backgroundSong);

			enemy01Source.x = (float)currentFrameEnemy01a*(float)enemy01.width / 4;
			enemy02Source.x = (float)currentFrameEnemy02a*(float)enemy01.width / 4;
			enemy03Source.x = (float)currentFrameEnemy03a*(float)enemy01.width / 4;

			player.inputActive = false;

			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };
			GameplayInput();

			if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { pauseButton.position.x, pauseButton.position.y, pauseButton.width, pauseButton.height }))
			{
				pauseButton.defaultColor = GREEN;
				pauseButton.selected = true;
			}
			else
			{
				pauseButton.defaultColor = DARKGREEN;
				pauseButton.selected = false;
			} 

			if (gameON)
			{		
				SetMusicVolume(backgroundSong, 0.90f);
				playerUpdate();

				if (spikes[3].pos.x + spikes[3].size.x >= obstacles[obMiddleSquare2].pos.x + obstacles[obMiddleSquare2].size.x + 325)
				{
					speedEnemy = speedEnemy * (-1);
					currentFrameEnemy02a++;
				}
				else if (spikes[3].pos.x <= obstacles[obMiddleSquare2].pos.x + obstacles[obMiddleSquare2].size.x)
				{
					speedEnemy = speedEnemy * (-1);
					currentFrameEnemy02a--;
				}

				spikes[3].pos.x += speedEnemy * GetFrameTime();

				if (spikes[6].pos.x + spikes[6].size.x >= obstacles[obMiddleSquare2].pos.x + obstacles[obMiddleSquare2].size.x + 325)
				{
					speedEnemy3 = speedEnemy3 * (-1);
					currentFrameEnemy03a++;
				}
				else if (spikes[6].pos.x <= obstacles[obMiddleSquare2].pos.x + obstacles[obMiddleSquare2].size.x)
				{
					speedEnemy3 = speedEnemy3 * (-1);
					currentFrameEnemy03a--;
				}

				spikes[6].pos.x += speedEnemy3 * GetFrameTime();

				if (spikes[5].pos.x + spikes[5].size.x >= obstacles[obMiddleSquare2].pos.x + 1)
				{
					speedEnemy2 = speedEnemy2 * (-1);
					currentFrameEnemy01a++;
					//currentFrameEnemy01b--;
				}
				else if (spikes[5].pos.x <= obstacles[obMiddleSquare2].pos.x - 255)
				{
					speedEnemy2 = speedEnemy2 * (-1);
					//currentFrameEnemy01b++;
					currentFrameEnemy01a--;
				}

				spikes[5].pos.x += speedEnemy2 * GetFrameTime();

			}
			else if (gamePaused)
			{
				SetMusicVolume(backgroundSong, 0.30f);
				timerON = false;

				for (int i = 0; i < maxButtons; i++)
				{
					if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }) || buttonSelect == i)
					{
						buttonSelect = i;
						buttons[i].defaultColor = GREEN;
						buttons[i].selected = true;
					}
					else
					{
						buttons[i].defaultColor = DARKGREEN;
						buttons[i].selected = false;
						buttonSelect = -1;
					}

					if (buttonSelect != buttonSelectSaveNumber && buttonSelect != -1)
					{
						isButtonSoundPlaying = false;
					}

					if (buttonSelect == i)
					{
						if (!(isButtonSoundPlaying))
						{
							//PlaySound(button_navigate01);
							isButtonSoundPlaying = true;
							buttonSelectSaveNumber = i;
						}
					}
				}
			}

			//---- GAME OVER CONDITION

			/*if (targetsLeft == 0)
			{
				gameON = false;
				timerON = false;
				buttonOption = buttonGameOver;
				isScreenFinished = true;
			}*/
		}

		void DrawGameplay()
		{
			DrawLevel();

			
			switch (currentLevel)
			{
			case 1:
				DrawTexture(levelBackground, 0, 0, WHITE);
				DrawTexture(levelBackground01, 0, 0, WHITE);
				break;
			case 2:
				DrawTexture(levelBackground, 0, 0, WHITE);
				DrawTexture(levelBackground02, 0, 0, WHITE);
				break;
			case 3:
				DrawTexture(levelBackground, 0, 0, WHITE);
				DrawTexture(levelBackground03, 0, 0, WHITE);
				break;
			default:
				break;
			}

			
			playerDraw();

			if (currentLevel == 3)
			{
				enemy01Destination = { spikes[5].pos.x,spikes[5].pos.y, 100,60 };
				enemy02Destination = { spikes[3].pos.x,spikes[3].pos.y, 100,60 };
				enemy03Destination = { spikes[6].pos.x,spikes[6].pos.y, 100,60 };

				DrawTexturePro(enemy01, enemy01Source, enemy01Destination, enemy01Origin, 0, WHITE);
				DrawTexturePro(enemy01, enemy02Source, enemy02Destination, enemy01Origin, 0, WHITE);
				DrawTexturePro(enemy01, enemy03Source, enemy03Destination, enemy01Origin, 0, WHITE);
			}


			DrawRectangleLines(pauseButton.position.x, pauseButton.position.y, pauseButton.width, pauseButton.height, pauseButton.defaultColor);

			//DrawTextEx(sideFont, FormatText("Targets:%i", targetsLeft), { 20, 20 }, defaultFontSize / 1.5f, 1.0f, GREEN);

			DrawTextEx(mainFont,"II", { pauseButton.position.x + 13, pauseButton.position.y + 7 }, defaultFontSize, 1.0f, pauseButton.defaultColor);
			

			if (!(gameON))
			{
				if (gamePaused)
				{
					DrawRectangleRec(pauseBoxRec, DARKPURPLE);
					//DrawTexturePro(pauseMenu, { 0, 0, (float)screenWidth / 4.2f, (float)screenHeight / 2.5f }, pauseBoxRec, { 0,0 }, 0, WHITE);
					//if(resolutionNormal) DrawTexturePro(pauseMenu, { 0, 0, (float)screenWidth / 4.2f, (float)screenHeight / 2.5f }, pauseBoxRec, { 0,0 }, 0, WHITE);
					//else if(resolutionSmall) DrawTexturePro(pauseMenu, { 0, 0, (float)screenWidth / 4.2f, (float)screenHeight / 2.5f }, pauseBoxRec, { 0,0 }, 0, WHITE);
					
					for (int i = 0; i < maxButtons; i++)
					{
						DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);
					}
					DrawTextEx(mainFont, "PAUSED", { buttons[0].position.x - (screenWidth * 0.04f), 20 }, defaultFontSize, 1.0f, GREEN);
					DrawTextEx(sideFont, "CONTINUE", { buttons[0].position.x + 10, buttons[0].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[0].defaultColor);
					DrawTextEx(sideFont, "RESTART", { buttons[1].position.x + 8, buttons[1].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[1].defaultColor);
					DrawTextEx(sideFont, "MENU", { buttons[2].position.x + 10, buttons[2].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[2].defaultColor);
				}
			}
		}

		void RestartPhase()
		{
			InitGameplayVariables();
			player.isAlive = true;
			buttonDistance = 0;
			gameON = true;
			timerON = true;
			//targetsLeft = 50;
		}

		bool FinishGameplayScreen()
		{
			buttonDistance = 0;
			return isScreenFinished;
		}

		void DeInitGameplayParallax()
		{
		}

		void DeInitGameplayResources()
		{
			UnloadTexture(slime);
			UnloadTexture(enemy01);
			UnloadTexture(levelBackground);
			UnloadTexture(levelBackground01);
			UnloadTexture(levelBackground02);
			UnloadTexture(levelBackground03);
			UnloadSound(slimeJump);
			UnloadSound(slimeSplash);
			UnloadMusicStream(slimeMove);
			UnloadMusicStream(backgroundSong);
			#ifdef AUDIO
			StopSound(enemy_explode01);
			StopSound(ship_shoot01);
			UnloadSound(enemy_explode01);
			UnloadSound(ship_shoot01);
			#endif
		}
	}
}