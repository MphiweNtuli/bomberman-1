#include "screen.hpp"
#include "Texture.hpp"

Screen::Screen() {}

Screen::Screen(GLFWwindow *window, Window &gameWindow, Graphics *g)
{
   screenInput command;

   this->_input = command.Full;
   this->_window = window;
    this->_gameWindow = gameWindow;
    this->_dispChange = false;    
   graphics = g;
    // _sound_val = 100;
}

Screen::~Screen(){
	delete graphics;
}

// void Settings::Music(){
    
// }

// void Settings::Screen(){

// } 

Window Screen::getGameWindow()
{
    return (_gameWindow);
}
// void Settings::modSound()
// {
//     if (_sound_val == 100)
//         _sound_val = 0;
//     else if (_sound_val == 0)
//         _sound_val = 100;
// }
void Screen::modDisplay()
{
    _gameWindow.changeWindowSize();
    _dispChange = !(_dispChange);
}
int Screen::getSoundVal()
{ 
    return (_sound_val);
}
bool Screen::getDispChange(){
    return (_dispChange);
}

void Screen::executeCommand(int input){
    screenInput command;
    switch(input){ 
        case command.Full :
            std::cout << "Full" << std::endl;
            // this->_gameWindow.switchToFull(this->_window);
            // modSound();
            glClear(GL_COLOR_BUFFER_BIT);
        break;
        case command.Windowed :
            std::cout << "Windowed" << std::endl;
            this->_gameWindow.switchToWindowed(this->_window);
        break;
        case command.Medium :
            // graphics->setDrawMode(MAINMENU);
            std::cout << "Medium" << std::endl;
            this->_gameWindow.switchToMedium(this->_window, 800 , 600);
            
        break;
         case command.Large :
            std::cout << " Large" << std::endl;
             this->_gameWindow.switchToLarge(this->_window, 1026, 768);
            modSound();
            glClear(GL_COLOR_BUFFER_BIT);
        break;
        case command.ReturnSetting :
            graphics->setDrawMode(SETTINGS);
            // modDisplay();
        break;
        case command.ReturnMenu :
            graphics->setDrawMode(SETTINGS);
            
        break;
    }
}
void Screen::setWindow(GLFWwindow *nWindow, Window &nGameWindow, Graphics *g){
    this->_window = nWindow;
    this->_gameWindow = nGameWindow;
    graphics = g;
}

void Screen::toggleCommands(/*GLFWwindow* window,*/ int key)
{
     screenInput command;
      switch(key){
        case GLFW_KEY_DOWN :
            this->_input++;
            if(_input > command.ReturnMenu)
                this->_input = command.Full;
            std::cout << _input << std::endl;
            break;
        
        case GLFW_KEY_UP :
            this->_input--;
            if(_input < command.Full)
                this->_input = command.ReturnMenu;
            std::cout << _input << std::endl;
            break;
        case GLFW_KEY_ENTER :
               executeCommand(_input);
    }
    initScreenImage();
    
}


void Screen::setGraphics(Graphics *g)
{
    graphics = g;
}

void Screen::modSound()
{
    if (_sound_val == 100)
        _sound_val = 0;
    else if (_sound_val == 0)
        _sound_val = 100;
}
// int Settings::getSoundVal()
// {
//     return (_sound_val);
// }

void Screen::initScreenImage()
{
    glGenVertexArrays(1, &menuVAO);
    glBindVertexArray(menuVAO);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "MenuVertexShader.vertexshader", "MenuFragmentShader.fragmentshader" );
    Texture texture("BombermanModels/screen.png", &menuTexture);

        static const GLfloat g_vertex_buffer_full[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, 0.0f, -0.25f,    0.0f, 0.0f,
        -0.55f, 0.05f, -0.25f,   0.0f, 0.0f,
        -0.65f, 0.10f, -0.25f,   0.0f, 0.0f,
        
    };

    static const GLfloat g_vertex_buffer_windowed[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        

        -0.65f, -0.11f, -0.25f,      0.0f, 0.0f,
        -0.55f, -0.07f, -0.25f,      0.0f, 0.0f, //continue
        -0.65f, -0.04f, -0.25f,      0.0f, 0.0f,
    };

    static const GLfloat g_vertex_buffer_medium[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.12f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.16f, -0.35f,  0.0f, 0.0f, //settings
        -0.65f, -0.19f, -0.35f,  0.0f, 0.0f
    };

    static const GLfloat g_vertex_buffer_large[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.25f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.30f, -0.35f,  0.0f, 0.0f, //Settings
        -0.65f, -0.35f, -0.35f,  0.0f, 0.0f
    };

    static const GLfloat g_vertex_buffer_returnMenu[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, -0.37f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.43f, -0.35f,  0.0f, 0.0f, //Exit
        -0.65f, -0.47f, -0.35f,  0.0f, 0.0f,
        
    };

    GLuint indeces[] =
    {
        0,1,3,
        1,2,3,
        4,5,6,
        //7,8,9
    };

    glGenBuffers(1, &menuEBO);
    glGenBuffers(1, &menuVBO);

    glBindBuffer(GL_ARRAY_BUFFER, menuVBO);

    if (this->_input == 0)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_full), g_vertex_buffer_full, GL_STATIC_DRAW);
    }
    else if (this->_input == 1)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_windowed), g_vertex_buffer_windowed, GL_STATIC_DRAW);
    }
    else if (this->_input == 2)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_medium), g_vertex_buffer_medium, GL_STATIC_DRAW);   
    }
    else if (this->_input == 3)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_large), g_vertex_buffer_large, GL_STATIC_DRAW);
    }
    else if (this->_input == 4)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_returnMenu), g_vertex_buffer_returnMenu, GL_STATIC_DRAW);   
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, menuEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
     // 1rst attribute buffer : vertices   
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        5 * sizeof(GL_FLOAT),                  // stride
        (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    // 1rst attribute buffer : texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Screen::LoadScreenImage()
{       
   // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, menuTexture);
	// Use our shader
    glUseProgram(programID);   
    
    // Draw the triangle !
	glBindVertexArray(menuVAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

int Screen::getInput()
{
	return _input;
}

void Screen::ScreenCleanup()
{
    // Cleanup VBO
    glDeleteBuffers(1, &menuVBO);
    glDeleteBuffers(1, &menuEBO);
    glDeleteVertexArrays(1, &menuVAO);
    glDeleteProgram(programID);
}
