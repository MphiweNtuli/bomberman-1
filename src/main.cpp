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

GLFWwindow *window;
MainMenu *mainMenu;
Graphics *graphics;
Player *player;
Portal *portal;
Window *myWindow;

// camera
glm::vec3 cameraPos = glm::vec3(-1.0f, 2.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 1.0f);

//move player callback        :Trinity
static void player_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		player->moveDown();
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		player->moveUp();
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		player->moveLeft();
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
		player->moveRight();
	if (key == GLFW_KEY_SPACE)
	{
		std::cout << "Call the Bomb Class \n";
	}
}

//Key Checking input        :Cradebe
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
	{
		mainMenu->toggleCommands(key);
		if (mainMenu->getInput() == 0 && key == GLFW_KEY_ENTER)
		{
			glEnable(GL_DEPTH_TEST);
			glfwSetKeyCallback(window, player_callback);
		}
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void initClasses(WindowKeyEvents &keyEvents, Sound *sound)
{
	myWindow.runGame();
	sound = myWindow.getSound();
	window = myWindow.getEvents();
	keyEvents = myWindow.getEvents();
	glfwSetKeyCallback(window, key_callback);
}

void initEntities()
{

}

int main(void)
{
	Sound *sound;
	int soundVal;
	WindowKeyEvents *keyEvents;

	//initialise the required classes
	initClasses(keyEvents, sound);

	// Initialize GLEW
	//reuben to revisit to create a function
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	graphics = new Graphics();
	player = new Player();
	portal = new Portal();
	Wall wall;
	StaticWall staticWall;
	Destructible destructible;
	Floor floor;
	Camera camera(cameraPos, cameraFront, cameraUp);

	graphics->initGlArrays();
	//graphics->initPlayerVertices(&pVBO, &pVAO, &pEBO);
	mainMenu = new MainMenu(window, myWindow, graphics);
	mainMenu->initMenuImage();
	wall.init();
	staticWall.init();
	destructible.init();
	floor.init();
	portal->init();
	player->init();

	//=========================================================================================
	//build and compile our shader program
	GLuint shadersID = LoadShaders("shaderVertexCoordinate.vs", "shaderFragCoordinate.fs");
	glUseProgram(shadersID);
	camera.perspectiveView(shadersID);
	//====================================================================================

	//set the initial sound value
	soundVal = mainMenu->getSoundVal();
	Mix_VolumeMusic(soundVal);

	do
	{
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
		keyEvents->keyEventsWrapper(window, sound, graphics);
		switch (graphics->getDrawMode())
		{
			case MAINMENU:
				sound->playMusicForvever(MUSIC_MENU1);
				mainMenu->LoadMainMenuImage();
				myWindow = mainMenu->getGameWindow();
				window = myWindow.getWindow();
				keyEvents->keyEventsWrapper(window, sound, graphics);
				glfwSetKeyCallback(window, key_callback);
				wall.init();
				staticWall.init();
				destructible.init();
				floor.init();
				//portal->init();
				//player->init();
				break;

			case GAMEPLAY:
				sound->playMusicForvever(MUSIC_BACK);
				// Use our shader
				//glUseProgram(programID);
				//------------------------------
				camera.processKeyInput(window);
				glUseProgram(shadersID);
				camera.cameraTimeLogic();
				camera.cameraFunction(shadersID);
				floor.draw();
				//---------------------------------
				wall.draw();
				staticWall.draw();
				destructible.draw();
				//graphics->drawElements();

				//player transformations
				//player->transform();
				//draw player
				//player->draw();

				//Portal trans and draw
				//	portal->transform();
				//	portal->draw();
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
	delete portal;

	mainMenu->menuCleanup();
	//glDeleteProgram(programID);
	glDeleteProgram(shadersID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
