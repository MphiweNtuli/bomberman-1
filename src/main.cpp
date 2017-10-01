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
#include "Levels.hpp"
#include "enemy.hpp"

GLFWwindow* window;
MainMenu *mainMenu;
Graphics *graphics;
std::vector<Enemy> enemies;
std::vector<Enemy>::iterator it;
Player *player;
Bomb *bomb;
std::vector <GLfloat> listOfWalls;

bool clockTimer = false;

static bool timeout(int seconds)
{
    static int time = glfwGetTime();
    
    if (glfwGetTime() - time >= seconds)
        return (true);
    return (false);
}

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
    (void) scancode;
    (void) mods;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{
		mainMenu->toggleCommands(key);
		if (mainMenu->getInput() == 0 && key == GLFW_KEY_ENTER)
		{
			glEnable(GL_DEPTH_TEST);
		}	
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	Sound *sound;
    int soundVal;
    GameState gs;

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

    Camera camera(cameraPos, cameraFront, cameraUp, window);
	graphics = new Graphics();
    bomb = new Bomb(3);
	mainMenu = new MainMenu(window, myWindow, graphics);
	Wall wall;
	StaticWall staticWall;
	player = new Player(staticWall.getWalls(), bomb);

	Portal portal;
    Health health;
    Timer timer;
    Floor floor;
	Destructible destructible;

	Levels level(destructible, player,enemies, portal, staticWall);

	// enemies.push_back(Enemy(level.getStaticWall().getWalls(), -0.75f,  0.16f));
	// enemies.push_back(Enemy(level.getStaticWall().getWalls(), 0.6f,  0.56f));
	// enemies.push_back(Enemy(level.getStaticWall().getWalls(), -0.75f,  0.30f));
	// enemies.push_back(Enemy(level.getStaticWall().getWalls(), -0.75f,  -0.60f));
	// enemies.push_back(Enemy(level.getStaticWall().getWalls(), -0.05f,  0.0f));
	// enemies.push_back(Enemy(level.getStaticWall().getWalls(), -0.07f,  0.0f));

	for (it = enemies.begin(); it != enemies.end(); ++it)
		it->setDestructible(level.getDestructible());

	for (it = enemies.begin(); it != enemies.end(); ++it)
		it->setWalls(level.getDestructible().getWalls());
    
    mainMenu->initMenuImage();
	wall.init();
    health.init();
    timer.init();
	//staticWall.init();
    floor.init();
    // portal.init();
	// destructible.init1();
 //    player->setDestructible(destructible);
 //    listOfWalls = player->getDestructible().getDestructibles();
	// player->setWalls(destructible.getWalls());
    
    
    
	//======== load game state ========
	gs.loadPlayerState(player);
	//=================================
	//set the initial sound value
    soundVal = mainMenu->getSoundVal();
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
        //only reset the sound setting if the value is different
        if (soundVal != mainMenu->getSoundVal())
        {
            std::cout << "vol " << mainMenu->getSoundVal() << std::endl;
            soundVal = mainMenu->getSoundVal();
            Mix_VolumeMusic(soundVal);
        }
        bomb->explode();
		keyEvents->keyEventsWrapper(window, sound, graphics);
		switch (graphics->getDrawMode())
		{
			case MAINMENU:
				sound->playMusicForvever(MUSIC_MENU1);
				mainMenu->LoadMainMenuImage();
                myWindow = mainMenu->getGameWindow();
                window = myWindow.getWindow();
                glfwSetKeyCallback(window, key_callback);
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
                health.draw();
                timer.draw();
                if (level.getLevel() == 1)
                {
                	std::cout << "level 1 baby\n";
                	if (level.getStart() == 1)
                	{
                		level.levelOneInit();
                		level.setStart(0);
                		timeout(0);
                	}
                	level.advanceToLevelTwo();
                	level.getStaticWall().draw();
                	level.getPortal().draw();
					level.getPlayer()->getDestructible().draw(level.getListOfWalls());

	                if (timeout(1000) == true)
	                    graphics->setDrawMode(MAINMENU);
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
					std::cout << "level 2 baby\n";
                	if (level.getStart() == 1)
                	{
                		level.levelTwoInit();
                		timeout(0);
                		level.setStart(0);
                	}
                	level.advanceToLevelThree();
                	level.getStaticWall().draw();
                	level.getPortal().draw();
					level.getPlayer()->getDestructible().draw(level.getListOfWalls());

	                if (timeout(1000) == true)
	                    graphics->setDrawMode(MAINMENU);
	                if (bomb->get_bombStatus() != 0)
						bomb->display();
					else if (bomb->getBombPlanted())
					{
						removeWalls = level.getPlayer()->getDestructible().destroy(level.getListOfWalls());
						std::cout << "level 2 baby5\n";
                   		bomb->setBombPlanted(false);
                   		std::cout << "level 2 baby6\n";
                    	level.getPlayer()->remove(removeWalls);

                    	for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
							it->remove(removeWalls);

						level.getPlayer()->bomb_colision(bomb->get_x(), bomb->get_y());

						for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
							it->bomb_colision(bomb->get_x(), bomb->get_y());

					}
				}
				else if (level.getLevel() == 3)
				{
					std::cout << "level 3 baby\n";
                	if (level.getStart() == 1)
                	{
                		level.levelThreeInit();
                		timeout(0);
                		level.setStart(0);
                	}
                	level.advanceToLevelWin();
                	level.getStaticWall().draw();
                	level.getPortal().draw();
					level.getPlayer()->getDestructible().draw(level.getListOfWalls());

	                if (timeout(1000) == true)
	                    graphics->setDrawMode(MAINMENU);
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
				else
				{
					graphics->setDrawMode(MAINMENU);
					std::cout << "gameover baby\n";
				}

/*                if (timeout(1000) == true)
                    graphics->setDrawMode(MAINMENU);
                if (bomb->get_bombStatus() != 0)
					bomb->display();
				else if (bomb->getBombPlanted())
				{
					removeWalls = player->getDestructible().destroy(listOfWalls);
                    bomb->setBombPlanted(false);
                    player->remove(removeWalls);
				}*/

				//std::cout << "player xpos = " << level.getPlayer()->get_xPos() << std::endl;
				//std::cout << "player ypos = " << level.getPlayer()->get_yPos() << std::endl;
                
				 //player->init();
				level.getPlayer()->init();
				level.getPlayer()->player_callback(window);
				for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
					if(!it->get_isdead())
						it->init();

				for (it = level.getEnemies().begin(); it != level.getEnemies().end(); ++it)
					it->enemy_callback();

				Player_colision(level.getPlayer(), level.getEnemies());
				// if(level.getPlayer()->get_isdead())
				// 	graphics->setDrawMode(MAINMENU);
				//player->player_callback(window);

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
    delete bomb;
	
	mainMenu->menuCleanup();
	//glDeleteProgram(programID);
    glDeleteProgram(shadersID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
