#include "settings.hpp"
#include "Texture.hpp"

Settings::Settings() {}

Settings::Settings(GLFWwindow *window, Window &gameWindow, Graphics *g)
{
   settingsInput command;

   this->_input = command.Sound;
   this->_window = window;
    this->_gameWindow = gameWindow;
    this->_dispChange = false;    
   graphics = g;
    _volumeLevel = 100;
}

Settings::~Settings(){
	delete graphics;
}

void Settings::Music(){
    
}

void Settings::Screen(){

} 

Window Settings::getGameWindow()
{
    return (_gameWindow);
}
void Settings::modSound()
{
    if (_sound_val > 0)
        _sound_val = 0;
<<<<<<< Updated upstream
    else
        _sound_val = _volumeLevel;
}
void Settings::modVolume()
{
    if (_volumeLevel >= 100)
        _volumeLevel = 0;
    else
        _volumeLevel += 25;
    _sound_val = _volumeLevel;
}
=======
    else if (_sound_val == 0)
        _sound_val = 100;
} 
>>>>>>> Stashed changes
void Settings::modDisplay()
{
    _gameWindow.changeWindowSize();
    _dispChange = !(_dispChange);
}
int Settings::getSoundVal()
{
    return (_sound_val);
}
bool Settings::getDispChange(){
    return (_dispChange);
}
void Settings::executeCommand(int input){
    settingsInput command;
    switch(input){ 
        case command.Sound :
            std::cout << "Sound:" << std::endl;
            modSound();
            glClear(GL_COLOR_BUFFER_BIT);
        break;
        case command.Screen :
            std::cout << "Screen" << std::endl;
            // modDisplay(); 
            graphics->setDrawMode(KEYS);
        break;
        // case command.Screen :
        //     std::cout << "Screen" << std::endl;
        //     // modDisplay(); 
        //     graphics->setDrawMode(SCREEN);
        break;
        case command.Volume :
            std::cout << "Volume:" << std::endl;
            modVolume();
            //glClear(GL_COLOR_BUFFER_BIT);
            break;
        case command.Return :
            graphics->setDrawMode(MAINMENU);
            std::cout << "Settings" << std::endl;
            
        break;
    }
}
void Settings::setWindow(GLFWwindow *nWindow, Window &nGameWindow, Graphics *g){
    this->_window = nWindow;
    this->_gameWindow = nGameWindow;
    graphics = g;
}

void Settings::toggleCommands(/*GLFWwindow* window,*/ int key)
{
     settingsInput command;
      switch(key){
        case GLFW_KEY_DOWN :
            this->_input++;
            if(_input > command.Return)
                this->_input = command.Sound;
            std::cout << _input << std::endl;
            break;
        
        case GLFW_KEY_UP :
            this->_input--;
            if(_input < command.Sound)
                this->_input = command.Return;
            std::cout << _input << std::endl;
            break;
        case GLFW_KEY_ENTER :
               executeCommand(_input);
    }
    initSettingsImage();
    
}


void Settings::setGraphics(Graphics *g)
{
    graphics = g;
}

// void Settings::modSound()
// {
//     if (_sound_val == 100)
//         _sound_val = 0;
//     else if (_sound_val == 0)
//         _sound_val = 100;
// }
// int Settings::getSoundVal()
// {
//     return (_sound_val);
// }

void Settings::initSettingsImage()
{
    glGenVertexArrays(1, &menuVAO);
    glBindVertexArray(menuVAO);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "MenuVertexShader.vertexshader", "MenuFragmentShader.fragmentshader" );
    Texture texture("BombermanModels/settings_new.png", &menuTexture);

    static const GLfloat g_vertex_buffer_sound[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,//sound
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, 0.0f, -0.25f,    0.0f, 0.0f,
        -0.55f, 0.05f, -0.25f,   0.0f, 0.0f,
        -0.65f, 0.10f, -0.25f,   0.0f, 0.0f,
        
    };

    static const GLfloat g_vertex_buffer_screen[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f 
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        

        -0.65f, -0.11f, -0.25f,       0.0f, 0.0f,
        -0.55f, -0.07f, -0.25f,       0.0f, 0.0f, //screen
        -0.65f, -0.04f, -0.25f,       0.0f, 0.0f,
    };

    static const GLfloat g_vertex_buffer_volume[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.12f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.16f, -0.35f,  0.0f, 0.0f, //volume
        -0.65f, -0.19f, -0.35f,  0.0f, 0.0f
    };

    static const GLfloat g_vertex_buffer_return[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.25f, -0.35f,  0.0f, 0.0f,
        -0.55f, -0.30f, -0.35f,  0.0f, 0.0f, //return
        -0.65f, -0.35f, -0.35f,  0.0f, 0.0f
    };

    // };

    GLuint indeces[] =
    {
        0,1,3,
        1,2,3,
        4,5,6,
        //7,8,9,
    };

    glGenBuffers(1, &menuEBO);
    glGenBuffers(1, &menuVBO);

    glBindBuffer(GL_ARRAY_BUFFER, menuVBO);

    if (this->_input == 0)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_sound), g_vertex_buffer_sound, GL_STATIC_DRAW);
    }
    else if (this->_input == 1)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_screen), g_vertex_buffer_screen, GL_STATIC_DRAW);
    }
    else if (this->_input == 2)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_volume), g_vertex_buffer_volume, GL_STATIC_DRAW);   
    }
    else if (this->_input == 3)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_return), g_vertex_buffer_return, GL_STATIC_DRAW);   
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

void Settings::LoadSettingsImage()
{       
   // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, menuTexture);
	// Use our shader
    glUseProgram(programID);   
    
    // Draw the triangle !
	glBindVertexArray(menuVAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

int Settings::getInput()
{
	return _input;
}

void Settings::SettingsCleanup()
{
    // Cleanup VBO
    glDeleteBuffers(1, &menuVBO);
    glDeleteBuffers(1, &menuEBO);
    glDeleteVertexArrays(1, &menuVAO);
    glDeleteProgram(programID);
}
