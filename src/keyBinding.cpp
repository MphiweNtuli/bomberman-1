#include "keyBinding.hpp"
#include "Texture.hpp"

Keys::Keys() {}

Keys::Keys(GLFWwindow *window, Window &gameWindow, Graphics *g, Player *_player)
{
   keyInput command;

   this->_input = command.Arrows;
   this->_window = window;
    this->_gameWindow = gameWindow;
    this->_dispChange = false;    
   graphics = g;
   player = _player;
    // _sound_val = 100;
}

Keys::~Keys(){
	delete graphics;
}


 void Keys::ArrowKeys()
 {
    player->keySet = KEY_ARROWS;
 }


void Keys::WASDKeys()
{
    player->keySet = KEY_WASD;
    std::cout << "inside the fun\n";
}


void Keys::IJKLKeys()
{
        player->keySet = KEY_IJKL;
}

Window Keys::getGameWindow()
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
// void Settings::modDisplay()
// {
//     _gameWindow.changeWindowSize();
//     _dispChange = !(_dispChange);
// }
// int Settings::getSoundVal()
// {
//     return (_sound_val);
// }
// bool Settings::getDispChange(){
//     return (_dispChange);
// }
void Keys::executeCommand(int input){
    keyInput command;
    switch(input){ 
        case command.Arrows :
            std::cout << "Arrows:" << std::endl;
            ArrowKeys();
            glClear(GL_COLOR_BUFFER_BIT);
        break;
        case command.WASD :
            std::cout << "WASD" << std::endl;
            player->keySet = KEY_WASD;//WASDKeys();
            std::cout << "out side \n";
            // modDisplay(); 
            // graphics->setDrawMode(SCREEN);
        break;
        case command.IJKL:
            std::cout << "IJKL\n";
            IJKLKeys();
            // graphics->setDrawMode(MAINMENU);
            // std::cou
        case command.Return :
            graphics->setDrawMode(MAINMENU);
            // std::cout << "Settings" << std::endl;
            
        break;
    }
}
void Keys::setWindow(GLFWwindow *nWindow, Window &nGameWindow, Graphics *g){
    this->_window = nWindow;
    this->_gameWindow = nGameWindow;
    graphics = g;
}

void Keys::toggleCommands(/*GLFWwindow* window,*/ int key)
{
     keyInput command;
      switch(key){
        case GLFW_KEY_DOWN :
            this->_input++;
            if(_input > command.Return)
                this->_input = command.Arrows;
            std::cout << _input << std::endl;
            break;
        
        case GLFW_KEY_UP :
            this->_input--;
            if(_input < command.Arrows)
                this->_input = command.Return;
            std::cout << _input << std::endl;
            break;
        case GLFW_KEY_ENTER :
               executeCommand(_input);
    }
    initKeysImage();
    
}


void Keys::setGraphics(Graphics *g)
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

void Keys::initKeysImage()
{
    glGenVertexArrays(1, &menuVAO);
    glBindVertexArray(menuVAO);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "MenuVertexShader.vertexshader", "MenuFragmentShader.fragmentshader" );
    Texture texture("BombermanModels/keys.png", &menuTexture);


    static const GLfloat g_vertex_buffer_arrow[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, 0.0f, -0.25f,    0.0f, 0.0f,
        -0.55f, 0.05f, -0.25f,   0.0f, 0.0f,
        -0.65f, 0.10f, -0.25f,   0.0f, 0.0f,
        
    };

    static const GLfloat g_vertex_buffer_wasd[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        

        -0.65f, -0.11f, -0.25f,      0.0f, 0.0f,
        -0.55f, -0.07f, -0.25f,      0.0f, 0.0f, //continue
        -0.65f, -0.04f, -0.25f,      0.0f, 0.0f,
    };

    static const GLfloat g_vertex_buffer_ijkl[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.12f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.16f, -0.35f,  0.0f, 0.0f, //settings
        -0.65f, -0.19f, -0.35f,  0.0f, 0.0f
    };

    static const GLfloat g_vertex_buffer_exit[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.25f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.30f, -0.35f,  0.0f, 0.0f, //Settings
        -0.65f, -0.35f, -0.35f,  0.0f, 0.0f
    }; 
    // };

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
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_arrow), g_vertex_buffer_arrow, GL_STATIC_DRAW);
    }
    else if (this->_input == 1)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_wasd), g_vertex_buffer_wasd, GL_STATIC_DRAW);
    }
    else if (this->_input == 2)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_ijkl), g_vertex_buffer_ijkl, GL_STATIC_DRAW);   
    }
    else if (this->_input == 3)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_exit), g_vertex_buffer_exit, GL_STATIC_DRAW);   
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

void Keys::LoadKeysImage()
{       
   // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, menuTexture);
	// Use our shader
    glUseProgram(programID);   
    
    // Draw the triangle !
	glBindVertexArray(menuVAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

int Keys::getInput()
{
	return _input;
}

void Keys::KeysCleanup()
{
    // Cleanup VBO
    glDeleteBuffers(1, &menuVBO);
    glDeleteBuffers(1, &menuEBO);
    glDeleteVertexArrays(1, &menuVAO);
    glDeleteProgram(programID);
}
