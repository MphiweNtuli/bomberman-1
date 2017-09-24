#include "Window.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"

//Error checking         :Cradebe
static void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

Window::Window()
{
	_width = WIDTH;
	_window = nullptr;
	_height = HEIGHT;
	_sound = new Sound();
	_keyEvents = new WindowKeyEvents();
}
Window::~Window()
{
	// delete graphics;
	// delete _sound;
	// delete _keyEvents;
}

//Runs Game         :Cradebe
void Window::runGame()
{
	// _sound->playMusicForvever(MUSIC_BEAR);
	initiateSystems();
}

//Initiates Screen  :Cradebe
void Window::initiateSystemsFullScreen()
{

	glfwSetErrorCallback(error_callback);

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//check if window rendered
	std::cout << "Fullscreen Window" << std::endl;

	_fullWindow = glfwCreateWindow(1920, 1080, "Bomberman", glfwGetPrimaryMonitor(), NULL);

	if (!_fullWindow)
	{
		terminateSystems();
	}

	glfwMakeContextCurrent(_fullWindow);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_fullWindow, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark green background
	glClearColor(0.0f, 0.3f, 0.0f, 0.0f);

}

void Window::initiateSystemsWindowed()
{

	glfwSetErrorCallback(error_callback);

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "Windowed Screen" << std::endl;
	_window = glfwCreateWindow(800, 600, "Bomberman", NULL, NULL);
	if (!_window)
	{
		terminateSystems();
	}

	glfwMakeContextCurrent(_window);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark green background
	glClearColor(0.0f, 0.3f, 0.0f, 0.0f);
}
void Window::setGraphics(Graphics g)
{
	this->graphics = &g;
}

//Terminates initialised system
void Window::terminateSystems()
{
	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
	getchar();
	//glfwDestroyWindow(_window);
	glfwTerminate();
	exit(EXIT_FAILURE);
}

void Window::changeWindowSize()
{
	//int width, height;
	//glfwGetWindowSize(_window, &width, &height);
	if (_fullWindow)
	{
		initiateSystems2();
		glfwDestroyWindow(_fullWindow);        
		_fullWindow = nullptr;
	}
	else if (_window)
	{
		initiateSystems();
		glfwDestroyWindow(_window);        
		_window = nullptr;
	}
}

Sound *Window::getSound()
{
	return (_sound);
}

GLFWwindow *Window::getWindow()
{
	if (!_window)
		return (_fullWindow);
	return _window;
}

WindowKeyEvents *Window::getEvents()
{
	return (_keyEvents);
}
