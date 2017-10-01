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
#include "enemy.hpp"

GLFWwindow* window;
MainMenu *mainMenu;
Graphics *graphics;
Player *player;
std::vector<Enemy> enemies;
std::vector<Enemy>::iterator it;
Enemy *enemy;
Enemy *enemy01;
Enemy *enemy02;
Enemy *enemy03;
Enemy *enemy04;
Bomb *bomb;
Health health;
Timer timer;
Destructible destructible;
std::vector <GLfloat> listOfWalls;

bool clockTimer = false;

static bool timeout(int seconds)
{
    static int time = glfwGetTime();
    
    if (glfwGetTime() - time >= seconds)
        return (true);
    return (false);
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

void Player_colision()
{
	// if(glm::distance(glm::vec2(player->get_xPos(),  player->get_yPos()) , glm::vec2(enemy->get_xPos(), enemy->get_yPos())) <= 0.065f)
	// 	player->set_isdead(true);
	// if(glm::distance(glm::vec2(player->get_xPos(),  player->get_yPos()) , glm::vec2(enemy01->get_xPos(), enemy01->get_yPos())) <= 0.065f)
	// 	player->set_isdead(true);
	// if(glm::distance(glm::vec2(player->get_xPos(),  player->get_yPos()) , glm::vec2(enemy02->get_xPos(), enemy02->get_yPos())) <= 0.065f)
	// 	player->set_isdead(true);
	// if(glm::distance(glm::vec2(player->get_xPos(),  player->get_yPos()) , glm::vec2(enemy03->get_xPos(), enemy03->get_yPos())) <= 0.065f)
	// 	player->set_isdead(true);
	// if(glm::distance(glm::vec2(player->get_xPos(),  player->get_yPos()) , glm::vec2(enemy04->get_xPos(), enemy04->get_yPos())) <= 0.065f)
	// 	player->set_isdead(true);

	for (it = enemies.begin(); it != enemies.end(); ++it)
		if(glm::distance(glm::vec2(player->get_xPos(),  player->get_yPos()) , glm::vec2(it->get_xPos(), it->get_yPos())) <= 0.065f)
			player->set_isdead(true);


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

	graphics = new Graphics();
    bomb = new Bomb(3);
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
    
	wall.init();
    health.init();
    timer.init();
	staticWall.init();
	player = new Player(staticWall.getWalls(), bomb);
	// enemy = new Enemy(staticWall.getWalls(), -0.75f,  0.16f);
	// enemy01 = new Enemy(staticWall.getWalls(), 0.6f,  0.56f);
	// enemy02 = new Enemy(staticWall.getWalls(), -0.75f,  0.30f);	
	// enemy03 = new Enemy(staticWall.getWalls(), -0.75f,  -0.60f);	
	// enemy04 = new Enemy(staticWall.getWalls(), -0.05f,  0.0f);

	enemies.push_back(Enemy(staticWall.getWalls(), -0.75f,  0.16f));
	enemies.push_back(Enemy(staticWall.getWalls(), 0.6f,  0.56f));
	enemies.push_back(Enemy(staticWall.getWalls(), -0.75f,  0.30f));
	enemies.push_back(Enemy(staticWall.getWalls(), -0.75f,  -0.60f));
	enemies.push_back(Enemy(staticWall.getWalls(), -0.05f,  0.0f));

	for (it = enemies.begin(); it != enemies.end(); ++it)
		std::cout << "I am an enemy" << std::endl;
	
	portal.init();
    health.init();
    timer.init();
	destructible.init3();
	player->setDestructible(destructible);
	// enemy->setDestructible(destructible);
	// enemy01->setDestructible(destructible);
	// enemy02->setDestructible(destructible);
	// enemy03->setDestructible(destructible);
	// enemy04->setDestructible(destructible);
	
    listOfWalls = player->getDestructible().getDestructibles();
	player->setWalls(destructible.getWalls());
	// enemy->setWalls(destructible.getWalls());
	// enemy01->setWalls(destructible.getWalls());
	// enemy02->setWalls(destructible.getWalls());	
	// enemy03->setWalls(destructible.getWalls());	
	// enemy04->setWalls(destructible.getWalls());

	// std::vector<Enemy>::iterator it;

	for (it = enemies.begin(); it != enemies.end(); ++it)
		it->setDestructible(destructible);

	for (it = enemies.begin(); it != enemies.end(); ++it)
		it->setWalls(destructible.getWalls());
	
	// glfwSetKeyCallback(window, player->player_callback(window));
    floor.init();
    
	//======== load game state ========
	gs.loadGameState(player, listOfWalls);
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
				
				staticWall.draw();
				portal.draw();
                health.draw();
                timer.draw();
				player->getDestructible().draw(listOfWalls);
                
                if (timeout(1000) == true)
                    graphics->setDrawMode(MAINMENU);
                if (bomb->get_bombStatus() != 0)
					bomb->display();
				else if (bomb->getBombPlanted())
				{
					removeWalls = player->getDestructible().destroy(listOfWalls);
                    bomb->setBombPlanted(false);
					player->remove(removeWalls);
					// enemy->remove(removeWalls);
					// enemy01->remove(removeWalls);
					// enemy02->remove(removeWalls);
					// enemy03->remove(removeWalls);
					// enemy04->remove(removeWalls);
					for (it = enemies.begin(); it != enemies.end(); ++it)
						it->remove(removeWalls);

					player->bomb_colision(bomb->get_x(), bomb->get_y());
					// enemy->bomb_colision(bomb->get_x(), bomb->get_y());
					// enemy01->bomb_colision(bomb->get_x(), bomb->get_y());
					// enemy02->bomb_colision(bomb->get_x(), bomb->get_y());
					// enemy03->bomb_colision(bomb->get_x(), bomb->get_y());
					// enemy04->bomb_colision(bomb->get_x(), bomb->get_y());
					for (it = enemies.begin(); it != enemies.end(); ++it)
						it->bomb_colision(bomb->get_x(), bomb->get_y());

				}
                
				player->init();
				// if(!enemy->get_isdead())
				// 	enemy->init();
				// if(!enemy01->get_isdead())
				// 	enemy01->init();
				// if(!enemy02->get_isdead())
				// 	enemy02->init();
				// if(!enemy03->get_isdead())
				// 	enemy03->init();
				// if(!enemy04->get_isdead())
				// 	enemy04->init();
				for (it = enemies.begin(); it != enemies.end(); ++it)
					if(!it->get_isdead())
						it->init();
				
				
				player->player_callback(window);
				// enemy->enemy_callback();
				// enemy01->enemy_callback();	
				// enemy02->enemy_callback();
				// enemy03->enemy_callback();
				// enemy04->enemy_callback();

				for (it = enemies.begin(); it != enemies.end(); ++it)
					it->enemy_callback();

				Player_colision();
				if(player->get_isdead())
					graphics->setDrawMode(MAINMENU);
				

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
	delete enemy;
	delete enemy01;
	delete enemy02;
	delete enemy03;
	delete enemy04;
	
	mainMenu->menuCleanup();
	//glDeleteProgram(programID);
    glDeleteProgram(shadersID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
