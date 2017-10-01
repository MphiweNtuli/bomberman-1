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
#include "keyBinding.hpp"
#include "Levels.hpp"

GLFWwindow *window;
MainMenu *mainMenu;
Settings *settings;
PauseMenu *pauseMenu;
Screen *screen;
Keys *keys;

Text *text;
Enemy *enemy;
Graphics *graphics;
std::vector<Enemy> enemies;
std::vector<Enemy>::iterator it;
Player *player;
Bomb *bomb;
Health health; 
Timer timer;
PowerUp power;
Destructible destructible;
std::vector <GLfloat> listOfWalls;

bool clockTimer = false;

void Player_colision(Player *player1, std::vector<Enemy> enemies1)
{

	for (it = enemies1.begin(); it != enemies1.end(); ++it)
		if(glm::distance(glm::vec2(player1->get_xPos(),  player1->get_yPos()) , glm::vec2(it->get_xPos(), it->get_yPos())) <= 0.065f)
			player1->set_isdead(true);

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
         else if (graphics->getDrawMode() == KEYS)
        {
        	std::cout << "inside \n";
        	keys->toggleCommands(/*window,*/ key);
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

    // static int    window_state = 0;//0 for fullscreen mode
	Window myWindow;
	WindowKeyEvents *keyEvents;
	std::vector<int> removeWalls;

	myWindow.initiateSystemsWindowed();
	sound = myWindow.getSound();
	window = myWindow.getWindow();
	keyEvents = myWindow.getEvents();

	glfwSetKeyCallback(window, key_callback);

	// Initialize GLEW
	if (myWindow.initializeGlew() == false)
		return -1;

    Camera camera(cameraPos, cameraFront, cameraUp, window);
	graphics = new Graphics();
	bomb = new Bomb(3);
	text = new Text();

	char bomberman[256];

	char level_[256];
	int level_num = 1;
	sprintf(level_, " level_ : %d", level_num);

	char hearts[256];
	int hearts_num = 3;
	sprintf(hearts, "Lives: %d", hearts_num);

	char pauseText[256];
	// int hearts_num = 3;
	sprintf(pauseText, "Press P To Pause");

	Wall wall;
	StaticWall staticWall;
	player = new Player(staticWall.getWalls(), bomb);

	Portal portal;
    Health health;
    Timer timer;
    Floor floor;
	mainMenu = new MainMenu(window, myWindow, graphics);
	mainMenu->initMenuImage();

	settings = new Settings(window, myWindow, graphics);
	settings->initSettingsImage();

	pauseMenu = new PauseMenu(window, myWindow, graphics);
	pauseMenu->initPauseImage();

	screen = new Screen(window, myWindow, graphics);
	screen->initScreenImage();
    keys = new Keys(window, myWindow, graphics, player);
	keys->initKeysImage();
	Destructible destructible;

	Levels level(destructible, player,enemies, portal, staticWall);

	for (it = enemies.begin(); it != enemies.end(); ++it)
		it->setDestructible(level.getDestructible());

	for (it = enemies.begin(); it != enemies.end(); ++it)
		it->setWalls(level.getDestructible().getWalls());
    
    mainMenu->initMenuImage();
	wall.init();
    health.init();
    timer.init();
    floor.init();
    
    
	//======== load game state ========
	// gs.loadGameState(player, listOfWalls);
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
		pauseMenu->updateVals(player, &level.getListOfWalls());

		switch (graphics->getDrawMode())
		{
		case MAINMENU:
			sound->playMusicForvever(MUSIC_MENU1);
			mainMenu->LoadMainMenuImage();
			myWindow = mainMenu->getGameWindow();
			window = myWindow.getWindow();
			mainMenu->loadSave(player, &level.getListOfWalls());
			break;
		case SETTINGS:
			sound->playMusicForvever(MUSIC_MENU1);
			settings->LoadSettingsImage();
			myWindow = settings->getGameWindow();
			if (soundVal != settings->getSoundVal())
			{
				soundVal = settings->getSoundVal();
				Mix_VolumeMusic(soundVal);
			}
			if (dispVal != settings->getDispChange())
			{
				myWindow = settings->getGameWindow();
				window = myWindow.getWindow();
				keyEvents->keyEventsWrapper(window, sound, graphics);
				glfwSetKeyCallback(window, key_callback);
				shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
				std::cout << "1\n";
				dispVal = settings->getDispChange();
				std::cout << "2\n";
				glUseProgram(shadersID);
				std::cout << "3\n";
				camera.perspectiveView(shadersID);

				settings->setWindow(window, myWindow, graphics);
				pauseMenu->setWindow(window, myWindow, graphics);
				mainMenu->setWindow(window, myWindow, graphics);
				wall.init();
				health.init();
				timer.init();
				staticWall.init();
				player = new Player(staticWall.getWalls(), bomb);
				destructible.init3();
			}
			break;
		case PAUSE:
			sound->playMusicForvever(MUSIC_MENU1);
			pauseMenu->LoadPauseImage();
			myWindow = pauseMenu->getGameWindow();

			break;
		case SCREEN:
			sound->playMusicForvever( MUSIC_MENU1);
			screen->LoadScreenImage();
			myWindow = screen->getGameWindow();

			break;
		case KEYS:
			sound->playMusicForvever( MUSIC_MENU1);
			keys->LoadKeysImage();
			myWindow = keys->getGameWindow();

			break;
		case GAMEPLAY:
			sound->playMusicForvever(MUSIC_BACK);
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
			time = timer.returnTime();

			sprintf(bomberman, "Time Left %.1f ", time); //Replaced glfwGetTime() with time variable
			text->loadText(pauseText, 0, 580, 13);
			text->loadText(bomberman, 250, 580, 15); //(location left /right,location up / down ,size)
			text->loadText(level_, 470, 580, 15);
			text->loadText(hearts, 660, 580, 15);
			sound->playMusicForvever(MUSIC_BACK);
			//------------------------------
			camera.processKeyInput();
			glUseProgram(shadersID);
			camera.cameraTimeLogic();
			camera.cameraFunction(shadersID);
			floor.draw();
			//---------------------------------
			wall.draw();			
			health.draw();
			timer.draw();
			if (level.getLevel() == 1)
			{
				if (level.getStart() == 1)
				{
					level.levelOneInit();
					level.setStart(0);
					timer.setTime(90);
				}
				level.advanceToLevelTwo();
				level.getStaticWall().draw();
				level.getPortal().draw();
				level.getPlayer()->getDestructible().draw(level.getListOfWalls());

				if (time == 90)
					graphics->setDrawMode(MAINMENU); // waiting for billy
				if (bomb->get_bombStatus() != 0)
					bomb->display();
				else if (bomb->getBombPlanted())
				{
					removeWalls = level.getPlayer()->getDestructible().destroy(level.getListOfWalls());
					   bomb->setBombPlanted(false);
					level.getPlayer()->remove(removeWalls);

					for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
						it->remove(removeWalls);

					level.getPlayer()->bomb_colision(bomb->get_x(), bomb->get_y());

					for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
						it->bomb_colision(bomb->get_x(), bomb->get_y());
				}
			}
			else if (level.getLevel() == 2)
			{
				if (level.getStart() == 1)
				{
					level.levelTwoInit();
					timer.setTime(90);
					level.setStart(0);
				}
				level.advanceToLevelThree();
				level.getStaticWall().draw();
				level.getPortal().draw();
				level.getPlayer()->getDestructible().draw(level.getListOfWalls());

				if (time == 90)
					graphics->setDrawMode(MAINMENU);
				if (bomb->get_bombStatus() != 0)
					bomb->display();
				else if (bomb->getBombPlanted())
				{
					removeWalls = level.getPlayer()->getDestructible().destroy(level.getListOfWalls());
					   bomb->setBombPlanted(false);
					level.getPlayer()->remove(removeWalls);
				}
			}
			else if (level.getLevel() == 3)
			{
				if (level.getStart() == 1)
				{
					level.levelThreeInit();
					timer.setTime(90);
					level.setStart(0);
				}
				level.advanceToLevelWin();
				level.getStaticWall().draw();
				level.getPortal().draw();
				level.getPlayer()->getDestructible().draw(level.getListOfWalls());

				if (time == 90)
					graphics->setDrawMode(MAINMENU);
				if (bomb->get_bombStatus() != 0)
					bomb->display();
				else if (bomb->getBombPlanted())
				{
					removeWalls = level.getPlayer()->getDestructible().destroy(level.getListOfWalls());
					   bomb->setBombPlanted(false);
					level.getPlayer()->remove(removeWalls);
				}
			}
			else
			{
				graphics->setDrawMode(MAINMENU);
				std::cout << "gameover baby\n";
			}
			level.getPlayer()->init();
			level.getPlayer()->player_callback(window);
			for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
				if(!it->get_isdead())
					it->init();

			for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
				it->enemy_callback();

			Player_colision(level.getPlayer(), level.getEnemies());
                if(level.getPlayer()->getPlayerLife() == 0)
                    graphics->setDrawMode(MAINMENU);

	default:
		break;
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);//
	
	//======================= save game state ==================
	// gs.saveGameState(*player, listOfWalls);
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
