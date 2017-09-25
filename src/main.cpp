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
#include "Gamestate.hpp"
#include "Bomb.hpp"
#include "health.hpp"
#include "timer.hpp"

GLFWwindow* window;
MainMenu *mainMenu;
Graphics *graphics;
Player *player;
Bomb *bomb;
Health health;
Timer timer;

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

//move player callback
static void player_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE)
    {
        bomb->set_x(player->get_xPos());
        bomb->set_y(player->get_yPos());
        bomb->updateLocation();
        bomb->drop();
        std::cout << "Space pressed\n";
    }
}

//Key Checking input        :Cradebe
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{
		mainMenu->toggleCommands(key);
		if (mainMenu->getInput() == 0 && key == GLFW_KEY_ENTER)
        {
			glfwSetKeyCallback(window, player_callback);
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

	myWindow.runGame();
	sound = myWindow.getSound();
	window = myWindow.getWindow();
	keyEvents = myWindow.getEvents();

	glfwSetKeyCallback(window, key_callback);

    // Initialize GLEW
    if (myWindow.initializeGlew() == false)
        return -1;

	graphics = new Graphics();
	// player = new Player();
    bomb = new Bomb(3, 0, 0);
    // Health = new Token("Health");
    // Timer = new Token("Timer");
	Wall wall;
	StaticWall staticWall;
	Portal portal;
    Health health;
    Timer timer;
	Destructible destructible;
	Destructible destructible01;
    Floor floor;
    Camera camera(cameraPos, cameraFront, cameraUp, window);

    gs.loadPlayerState(player);
	graphics->initGlArrays();
	mainMenu = new MainMenu(window, myWindow, graphics);
	mainMenu->initMenuImage();
	wall.init();
    health.init();
    timer.init();
	staticWall.init();
	player = new Player(staticWall.getWalls());
	portal.init();
    health.init();
    timer.init();
	destructible.init1();
	destructible01.init1();
	player->setWalls(destructible.getWalls());
    floor.init();
	//player->init();
	//Mix_VolumeMusic(10);
    
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
				// Use our shader
				//glUseProgram(programID);
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
				destructible.draw();
				destructible01.draw();
                
                if (timeout(100) == true)
                    graphics->setDrawMode(MAINMENU);
                if (bomb->get_bombStatus() != 0)
                    bomb->display();
                
                
               // glUseProgram(player->getProgramId());
				//camera.cameraFunction(player->getProgramId());
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
