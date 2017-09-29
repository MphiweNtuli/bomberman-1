// Include standard headers
#include "Wall.hpp"
#include "shader.hpp"
#include "Graphics.hpp"
#include "Window.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "Floor.hpp"
#include "Portal.hpp"
#include "StaticWall.hpp"
#include "Destructible.hpp"
#include "camera.hpp"
#include "GameState.hpp"
#include "Bomb.hpp"
#include "health.hpp"
#include "timer.hpp"
#include "settings.hpp"
#include "text.hpp"
#include "enemy.hpp"
#include "pause.hpp"

GLFWwindow *window;
MainMenu *mainMenu;
Settings *settings;
PauseMenu *pauseMenu;

Text *text;
Enemy *enemy;
Graphics *graphics;
Player *player;
Bomb *bomb;
Health health;
Timer timer;
Destructible destructible;
Destructible destructible01;

bool clockTimer = false;

static bool timeout(int seconds)
{
	static int time = glfwGetTime();

	if (glfwGetTime() - time >= seconds)
		return (true);
	return (false);
}

// camera
glm::vec3 cameraPos = glm::vec3(-1.0f, 2.0f, 2.76f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 1.0f);

//Key Checking input        :Cradebe
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{	
		if (graphics->getDrawMode() == MAINMENU)
		{
			mainMenu->toggleCommands(key);
			if (mainMenu->getInput() == 0 && key == GLFW_KEY_ENTER)
        	{
				//glfwSetKeyCallback(window, player_callback);
        	    glEnable(GL_DEPTH_TEST);
        	}
        }
        else if (graphics->getDrawMode() == SETTINGS)
        {
        	std::cout << "inside \n";
        	settings->toggleCommands(/*window,*/ key);
        }
        else if (graphics->getDrawMode() == PAUSE)
        {
        	std::cout << "inside \n";
        	pauseMenu->toggleCommands(/*window,*/ key);
        }
	}
	else if (key == GLFW_KEY_P)
	{
		graphics->setDrawMode(PAUSE);
		glEnable(GL_DEPTH_TEST);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	Sound *sound;
	int soundVal;
	bool dispVal;
	GameState gs;

	Window myWindow;
	WindowKeyEvents *keyEvents;
	std::list<int> removeWalls;

	myWindow.runGame();
	sound = myWindow.getSound();
	window = myWindow.getWindow();
	keyEvents = myWindow.getEvents();

	glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW
	if (myWindow.initializeGlew() == false)
		return -1;

	graphics = new Graphics();
	bomb = new Bomb(3);
	enemy = new Enemy();
	text = new Text();

	char bomberman[256];

	char level[256];
	int level_num = 1;
	sprintf(level, " Level : %d", level_num);

	char hearts[256];
	int hearts_num = 3;
	sprintf(hearts, "Hearts: %d", hearts_num);

	char pauseText[256];
	// int hearts_num = 3;
	sprintf(pauseText, "Prss P");

	char pausePress[256];
	// int hearts_num = 3;
	sprintf(pausePress, "Pause");
	// Health = new Token("Health");
	// Timer = new Token("Timer");
	Wall wall;
	StaticWall staticWall;
	Portal portal;
	Health health;
	Timer timer;
	Floor floor;

	Camera camera(cameraPos, cameraFront, cameraUp, window);
	mainMenu = new MainMenu(window, myWindow, graphics);
	mainMenu->initMenuImage();

	settings = new Settings(window, myWindow, graphics);
	settings->initSettingsImage();

	pauseMenu = new PauseMenu(window, myWindow, graphics);
	pauseMenu->initPauseImage();

	wall.init();
	health.init();
	timer.init();
	staticWall.init();
	player = new Player(staticWall.getWalls(), bomb);
	portal.init();
	health.init();
	timer.init();
	destructible.init1();
	destructible01.init1();
	player->setDestructible(destructible);
	player->setDestructible01(destructible01);

	player->setWalls(destructible.getWalls());
	// glfwSetKeyCallback(window, player->player_callback(window));
	floor.init();

	//======== load game state ========
	gs.loadPlayerState(player);
	//=================================

	//=========================================================================================
	//build and compile our shader program
	GLuint shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
	glUseProgram(shadersID);
	camera.perspectiveView(shadersID);
	//====================================================================================

	soundVal = settings->getSoundVal();
	dispVal = settings->getDispChange();
	Mix_VolumeMusic(soundVal);

	do
	{
		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//only reset the sound setting if the value is different
		// if (soundVal != mainMenu->getSoundVal())
		// {
		// 	//std::cout << "vol " << mainMenu->getSoundVal() << std::endl;
		// 	soundVal = mainMenu->getSoundVal();
		// 	Mix_VolumeMusic(soundVal);
		// }
		bomb->explode();
		keyEvents->keyEventsWrapper(window, sound, graphics);
		switch (graphics->getDrawMode())
		{
		case MAINMENU:
			sound->playMusicForvever(MUSIC_MENU1);
			mainMenu->LoadMainMenuImage();
			myWindow = mainMenu->getGameWindow();
			window = myWindow.getWindow();
			// glfwSetKeyCallback(window, key_callback);
			break;
		case SETTINGS:
			sound->playMusicForvever(MUSIC_MENU1);
			settings->LoadSettingsImage();
			myWindow = settings->getGameWindow();
			//only reset the sound setting if the value is different
			if (soundVal != settings->getSoundVal())
			{
				soundVal = settings->getSoundVal();
				Mix_VolumeMusic(soundVal);
			}
			//only reset the display setting if the value is different
			if (dispVal != settings->getDispChange())
			{
				myWindow = settings->getGameWindow();
				window = myWindow.getWindow();
				keyEvents->keyEventsWrapper(window, sound, graphics);
				glfwSetKeyCallback(window, key_callback);
				//reload the shaders each time the loop itarates in the main menu;
				shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
				dispVal = settings->getDispChange();
				glUseProgram(shadersID);
				camera.perspectiveView(shadersID);

				settings->setWindow(window, myWindow, graphics);
				pauseMenu->setWindow(window, myWindow, graphics);
				mainMenu->setWindow(window, myWindow, graphics);
				wall.init();
				health.init();
				timer.init();
				staticWall.init();
				player = new Player(staticWall.getWalls(), bomb);
				//portal.init();
				//health.init();
				//timer.init();
				destructible.init1();
				destructible01.init1();
			}
			break;
		case PAUSE:
			sound->playMusicForvever(MUSIC_MENU1);
			// settings->toggleCommands(window);
			//settings->initSettingsImage();
			pauseMenu->LoadPauseImage();
			myWindow = pauseMenu->getGameWindow();

			// window = myWindow.getWindow();
			// glfwSetKeyCallback(window, key_callback);
			break;
		case GAMEPLAY:
			sound->playMusicForvever(MUSIC_BACK);
			//------------------------------
			camera.processKeyInput();
			glUseProgram(shadersID);
			camera.cameraTimeLogic();
			camera.cameraFunction(shadersID);
			floor.draw();
			//---------------------------------
			wall.draw();

			staticWall.draw();
			portal.draw();
			health.draw();
			timer.draw();
			player->getDestructible().draw();
			player->getDestructible01().draw();
			enemy->display();
			if (timeout(100) == true)
				graphics->setDrawMode(MAINMENU);
			if (bomb->get_bombStatus() != 0)
				bomb->display();
			else if (bomb->getBombPlanted())
			{
				std::cout << "i am here" << std::endl;
				removeWalls = player->getDestructible().destroy();
				removeWalls = player->getDestructible01().destroy();
				bomb->setBombPlanted(false);
				player->remove(removeWalls);
			}
			sprintf(bomberman, "Your Quest has started  %.1f ", glfwGetTime());
			text->loadText(pauseText, 0, 450, 12);
			text->loadText(pausePress, 0, 460, 16);
			text->loadText(bomberman, 30, 580, 15); //(location left /right,location up / down ,size)
			text->loadText(level, 450, 580, 15);
			text->loadText(hearts, 670, 380, 15);

			player->init();
			player->player_callback(window);

		default:
			break;
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0);

	//======================= save game state ==================
	gs.savePlayerState(*player);
	//==========================================================
	// Cleanup VBO
	delete graphics;
	delete player;

	mainMenu->menuCleanup();
	//glDeleteProgram(programID);
	glDeleteProgram(shadersID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
