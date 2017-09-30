#include "Window.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"

//Error checking         :Cradebe
static void error_callback(int error, const char* description)
{
    (void)error;
    fputs(description, stderr);
}

Window::Window(){
    latestHeight = HEIGHT;
    latestWidth = WIDTH;
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

void Window::runGame()
{
    /*int     win;
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
    else */
        // initiateSystemsFullscreen();
    initiateSystemsWindowed();
}

//Initiates Screen  :Cradebe
void Window::initiateSystemsFullscreen(){
    
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
}

void Window::switchToLarge(GLFWwindow* win , int wantedWidth, int wantedHeight)
{
    if (wantedHeight != latestHeight && wantedWidth !=  latestWidth)
    {
        glfwSetWindowSize(win, wantedWidth, wantedHeight);
        latestHeight = wantedHeight;
        latestWidth = wantedWidth;
    }
    
}

void Window::switchToMedium(GLFWwindow* win , int wantedWidth, int wantedHeight)
{
    if (wantedHeight != latestHeight && wantedWidth !=  latestWidth)
    {
        glfwSetWindowSize(win, wantedWidth, wantedHeight);
        latestHeight = wantedHeight;
        latestWidth = wantedWidth;
    }
}

void Window::switchToWindowed(GLFWwindow* win)
{
    if (HEIGHT != latestHeight && WIDTH !=  latestWidth)
    {
        glfwSetWindowSize(win, WIDTH, HEIGHT);
        latestHeight = HEIGHT;
        latestWidth = WIDTH;
    }
    
}

void Window::switchToFull(GLFWwindow* win)
{
    (void)win;
    // if (FULLHEIGHT != latestHeight && FULLWIDTH !=  latestWidth)
    // {
    //     glfwSetWindowSize(win, FULLWIDTH, FULLHEIGHT);
    //     latestHeight = FULLHEIGHT;
    //     latestWidth = FULLWIDTH;
    // }
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
    
    _window = glfwCreateWindow(900, 750, "Bomberman", NULL, NULL);
    
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
        initiateSystemsWindowed();
        glfwDestroyWindow(_fullWindow);
        _fullWindow = nullptr;
    }
    else if (_window)
    {
        initiateSystemsFullscreen();
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
        return _fullWindow;
    return _window;
}

WindowKeyEvents* Window::getEvents()
{
    return (_keyEvents);
}

