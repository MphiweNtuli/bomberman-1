#include "Window.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"

//Error checking         :Cradebe
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

Window::Window(){
    _width  = WIDTH;
    _window = nullptr;
    _fullWindow = nullptr;
    _height  = HEIGHT;
    _sound = new Sound();
    _keyEvents = new WindowKeyEvents();
}
Window::~Window(){
    // delete graphics;
    // delete _sound;
    // delete _keyEvents;
}

//Runs Game         :Cradebe
void Window::runGame()
{
    int     win;
    // _sound->playMusicForvever(MUSIC_BEAR);
    std::cout << "PLEASE SELECT WINDOW MODE: [1] Windowed OR [0] FullScreen" << std::endl;
    std::cin >> win;
    
    while (win != 1 || win != 0){
        if (win == 1 || win == 0)
            break;
        else
        {
            std::cout << win;
            std::cout << " IS NOT A VALID OPTION" << std::endl;
            std::cout << "PLEASE SELECT WINDOW MODE: [1] Windowed OR [0] FullScreen" << std::endl;
            std::cin >> win;
        }
    }
    
    if (win == 1)
        initiateSystems2();
    else
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
    
    //Keeps screen open
    /*while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);*/
}

//Initiates Screen  :Cradebe
void Window::initiateSystems2()
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
    
    //std::cout << "window no full" << std::endl;
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

bool Window::initializeGlew()
{
    glewExperimental = true; // Needed for core profile
    
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        //return -1;
        return false;
    }
    else
        return true;
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

Sound* Window::getSound()
{
    return (_sound);
}

GLFWwindow* Window::getWindow()
{
    if (!_window)
        return (_fullWindow);
    return _window;}

WindowKeyEvents* Window::getEvents()
{
    return (_keyEvents);
}

