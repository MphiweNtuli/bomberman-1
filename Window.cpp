#include "Window.hpp"
#include "MainMenu.hpp"

MainMenu *mainMenu;

//Error checking         :Cradebe
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

//Key Checking input        :Cradebe
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{          
    if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_UP || key == GLFW_KEY_ENTER ) && action == GLFW_PRESS)
         mainMenu->toggleCommands(key);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

Window::Window(){
    _window = nullptr;
}
Window::~Window(){
	//delete graphics;
}

//Runs Game         :Cradebe
void Window::runGame(){
    initiateSystems();
}

//Initiates Screen  :Cradebe
void Window::initiateSystems(){
    
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
    
    _window = glfwCreateWindow(800, 600, "Bomberman", NULL, NULL);
    mainMenu = new MainMenu(_window, graphics);
    
    if (!_window)
    {
        terminateSystems();
    }
    
    glfwMakeContextCurrent(_window);
    glfwSetKeyCallback(_window, key_callback);
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark green background
    glClearColor(0.0f, 0.3f, 0.0f, 0.0f);
    
    //Keeps screen open
    /*while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);*/
}

void Window::setGraphics(Graphics g)
{
    this->graphics = &g;
    mainMenu->setGraphics(graphics);
}

//Terminates initialised system
void Window::terminateSystems()
{
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwDestroyWindow(_window);    
    glfwTerminate();
    exit(EXIT_FAILURE);
}

GLFWwindow* Window::getWindow()
{
    return _window;
}
