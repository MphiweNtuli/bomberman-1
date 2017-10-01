#include "Pause.hpp"
#include "Texture.hpp"

PauseMenu::PauseMenu() {}

PauseMenu::PauseMenu(GLFWwindow *window, Window &gameWindow, Graphics *g)
{
   pauseInput command;

    
    this->_input = command.Resume;
    this->_window = window;
    this->_gameWindow = gameWindow;
   graphics = g;
    // _sound_val = 100;
}

PauseMenu::~PauseMenu(){
	delete graphics;
}

void PauseMenu::Resume(){
}

void PauseMenu::SaveGame(){
    gs.saveGameState(*p, *walls);
} 

void PauseMenu::updateVals(Player *_p, std::vector<GLfloat> *w)
{
    p = _p;
    walls = w;
}

Window PauseMenu::getGameWindow()
{
    return (_gameWindow);
} 

void PauseMenu::setWindow(GLFWwindow *nWindow, Window &nGameWindow, Graphics *g){
    this->_window = nWindow;
    this->_gameWindow = nGameWindow;
    graphics = g;
}

void PauseMenu::executeCommand(int input){
    pauseInput command;
    switch(input){ 
       case command.Resume :
            graphics->setDrawMode(GAMEPLAY);
            glClear(GL_COLOR_BUFFER_BIT);
        break;
        case command.SaveGame :
            SaveGame();
            std::cout << "Save" << std::endl;
        break;
        case command.Return :
            graphics->setDrawMode(MAINMENU);
            
        break;
    }
}


void PauseMenu::toggleCommands( int key)
{
    // std::cout  << this->_input << " input : \n";
     pauseInput command;
      switch(key){
        case GLFW_KEY_DOWN :
            this->_input++;
            if(_input > command.Return)
                this->_input = command.Resume;
            std::cout << _input << std::endl;
            break;
        
        case GLFW_KEY_UP :
            this->_input--;
            if(_input < command.Resume)
                this->_input = command.Return;
            std::cout << _input << std::endl;
            break;
        case GLFW_KEY_ENTER :
               executeCommand(_input);
    }
    initPauseImage();
    
}


void PauseMenu::setGraphics(Graphics *g)
{
    graphics = g;
}


void PauseMenu::initPauseImage()
{
    glGenVertexArrays(1, &menuVAO);
    glBindVertexArray(menuVAO);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "MenuVertexShader.vertexshader", "MenuFragmentShader.fragmentshader" );
    Texture texture("BombermanModels/pause.png", &menuTexture);

    static const GLfloat g_vertex_buffer_resume[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,//sound
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, 0.0f, -0.25f,    0.0f, 0.0f,
        -0.55f, 0.05f, -0.25f,   0.0f, 0.0f,
        -0.65f, 0.10f, -0.25f,   0.0f, 0.0f,
        
    };

    static const GLfloat g_vertex_buffer_save[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f 
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        

        -0.65f, -0.11f, -0.25f,       0.0f, 0.0f,
        -0.55f, -0.07f, -0.25f,       0.0f, 0.0f, //screen
        -0.65f, -0.04f, -0.25f,       0.0f, 0.0f,
    };

    static const GLfloat g_vertex_buffer_return[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.25f, -0.35f,   0.0f, 0.0f,
        -0.55f, -0.30f, -0.35f,  0.0f, 0.0f, //return
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
    
    glEnable(GL_BLEND); //Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

    glGenBuffers(1, &menuEBO);
    glGenBuffers(1, &menuVBO);

    glBindBuffer(GL_ARRAY_BUFFER, menuVBO);

    if (this->_input == 0)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_resume), g_vertex_buffer_resume, GL_STATIC_DRAW);
    }
    else if (this->_input == 1)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_save), g_vertex_buffer_save, GL_STATIC_DRAW);
    }
    else if (this->_input == 2)
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

void PauseMenu::LoadPauseImage()
{       
   // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, menuTexture);
	// Use our shader
    glUseProgram(programID);   
    
    // Draw the triangle !
	glBindVertexArray(menuVAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

int PauseMenu::getInput()
{
	return _input;
}

void PauseMenu::PauseCleanup()
{
    // Cleanup VBO
    glDeleteBuffers(1, &menuVBO);
    glDeleteBuffers(1, &menuEBO);
    glDeleteVertexArrays(1, &menuVAO);
    glDeleteProgram(programID);
}
