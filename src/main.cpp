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
#include "screen.hpp"
#include "PowerUp.hpp"

GLFWwindow *window;
MainMenu *mainMenu;
Settings *settings;
PauseMenu *pauseMenu;
Screen *screen;

Text *text;
Enemy *enemy;
Graphics *graphics;
Player *player;
Bomb *bomb;
Health health;
PowerUp power;
Destructible destructible;
std::vector <GLfloat> listOfWalls;

bool clockTimer = false;
static int prev_time = glfwGetTime();

static bool timeout(int seconds, int prev_time)
{
	if (glfwGetTime() - prev_time >= seconds)
		return (true);
	return (false);
}

// camera
glm::vec3 cameraPos   = glm::vec3(-1.0f, 2.0f,  2.76f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); 
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  1.0f);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{	
		if (graphics->getDrawMode() == MAINMENU)
		{
			mainMenu->toggleCommands(key);
			if (mainMenu->getInput() == 0 && key == GLFW_KEY_ENTER)
        	    glEnable(GL_DEPTH_TEST);
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
        else if (graphics->getDrawMode() == SCREEN)
        {
        	std::cout << "inside \n";
        	screen->toggleCommands(/*window,*/ key);
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
	float time;

	Window myWindow;
	WindowKeyEvents *keyEvents;
	std::vector<int> removeWalls;

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
	sprintf(pauseText, "Press P");

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

	screen = new Screen(window, myWindow, graphics);
	screen->initScreenImage();

	wall.init();
	health.init();
	timer.init();
	staticWall.init();
	player = new Player(staticWall.getWalls(), bomb);
	portal.init();
    health.init();
	destructible.init3();
    player->setDestructible(destructible);
    listOfWalls = player->getDestructible().getDestructibles();
	player->setWalls(destructible.getWalls());
	// glfwSetKeyCallback(window, player->player_callback(window));
    floor.init();
    
	//======== load game state ========
	gs.loadGameState(player, listOfWalls);
	//=================================
	//set the initial sound value
	soundVal = mainMenu->getSoundVal();
	dispVal = settings->getDispChange();
    //=========================================================================================
    //build and compile our shader program
    GLuint shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
    glUseProgram(shadersID);
    camera.perspectiveView(shadersID);
    //====================================================================================
    
    do {
		// Clear the screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		bomb->explode(sound);
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
				destructible.init3();
				// destructible01.init1();
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
		case SCREEN:
			sound->playMusicForvever(MUSIC_MENU1);
			// settings->toggleCommands(window);
			//settings->initSettingsImage();
			screen->LoadScreenImage();
			myWindow = screen->getGameWindow();

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
                
			// IMPORTANT
			if ((player->get_yPos() > 0.708 && player->get_yPos() < 0.8124)
				&& (player->get_xPos() > 0.5556 && player->get_xPos() < 0.7284))
			{
				(power.timeUsed == false) ? timer.increaseTime() : timer.displayTime();
				power.TimerDisplay(0);
			}
			else
			{
				if (power.TimerDisplay(1) == 1)
					timer.draw();
			}
			
			if ((player->get_yPos() < -0.5592 && player->get_yPos() > -0.7212)
				&& (player->get_xPos() > -0.9312 && player->get_xPos() < -0.7728))
				power.HealthDisplay(0);	
			else
			{
				if (power.HealthDisplay(1) == 1)
					health.draw();
			}
			// IMPORTANT
			
			// Time displayed
			time = timer.returnTime();
                
			player->getDestructible().draw(listOfWalls);
			enemy->display();
			if (timeout(100, prev_time) == true)
			{
				sound->stopMusic(MUSIC_BACK);
				sound->playMusicForvever(MUSIC_MENU1);
				graphics->setDrawMode(MAINMENU);
				prev_time = glfwGetTime();
			}
			if (bomb->get_bombStatus() != 0)
				bomb->display();
			else if (bomb->getBombPlanted())
			{
				std::cout << "i am here" << std::endl;
				removeWalls = player->getDestructible().destroy(listOfWalls);
				bomb->setBombPlanted(false);
				player->remove(removeWalls);
			}
			sprintf(bomberman, "Your Quest has started  %.1f ", time); //Replaced glfwGetTime() with time variable
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
	gs.saveGameState(*player, listOfWalls);
	//==========================================================
	// Cleanup VBO
	delete graphics;
	delete player;
    delete bomb;
	
	mainMenu->menuCleanup();
	//glDeleteProgram(programID);
	glDeleteProgram(shadersID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
