#include "MainMenu.hpp"
#include "Texture.hpp"

MainMenu::MainMenu() {}

MainMenu::MainMenu(GLFWwindow *window, Window &gameWindow, Graphics *g)
{
   Input command;
   this->_input = command.Start;
   this->_window = window;
    this->_gameWindow = gameWindow;
   graphics = g;
    _sound_val = 100;
}

MainMenu::~MainMenu(){
	delete graphics;
}

void MainMenu::gameStart(){
    
}

void MainMenu::gameContinue(){

}

Window MainMenu::getGameWindow()
{
    return (_gameWindow);
}

void MainMenu::gameSettings(int input)
{
    Input command;
    switch (input)
    {
        case command.ToggleSound:
            modSound();
            if (getSoundVal() > 0)
                std::cout << "Sound is ON" << std::endl;
            else
                std::cout << "Sound is OFF" << std::endl;
            break;
    }
}

void MainMenu::executeCommand(int input){
    Input command;
    switch(input){
        case command.Start :
            glClear(GL_COLOR_BUFFER_BIT);
			graphics->setDrawMode(GAMEPLAY);
        break;
        case command.Continue :
            std::cout << "Continue" << std::endl;
        break;
        case command.Settings :
             gameSettings(5);
            _gameWindow.changeWindowSize();
        break;
        case command.Exit :
            glfwSetWindowShouldClose(_window, GL_TRUE);
        break;
    }
}

void MainMenu::toggleCommands(int key){
    Input command;
    switch(key){
        case GLFW_KEY_DOWN :
            this->_input++;
            if(_input > command.Exit)
                this->_input = command.Start;
            break;
        
        case GLFW_KEY_UP :
            this->_input--;
            if(_input < command.Start)
                this->_input = command.Exit;
            break;
        case GLFW_KEY_ENTER :
               executeCommand(_input);
    }
    initMenuImage();
}

void MainMenu::setGraphics(Graphics *g)
{
    graphics = g;
}

void MainMenu::modSound()
{
    if (_sound_val == 100)
        _sound_val = 0;
    else if (_sound_val == 0)
        _sound_val = 100;
}
int MainMenu::getSoundVal()
{
    return (_sound_val);
}

void MainMenu::initMenuImage()
{
    glGenVertexArrays(1, &menuVAO);
    glBindVertexArray(menuVAO);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "MenuVertexShader.vertexshader", "MenuFragmentShader.fragmentshader" );
    Texture texture("main.png", &menuTexture);

    static const GLfloat g_vertex_buffer_start[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, 0.0f, 0.25f,    0.0f, 0.90f,
        -0.55f, 0.05f, 0.25f,   0.0f, 0.10f,
        -0.65f, 0.10f, 0.25f,   1.0f, 0.10f,
        
    };

    static const GLfloat g_vertex_buffer_continue[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        

        -0.65f, -0.11f, 0.25f,        0.0f, 0.90f,
        -0.55f, -0.07f, 0.25f,       0.0f, 0.10f, //continue
        -0.65f, -0.04f, 0.25f,      1.0f, 0.10f,
    };

    static const GLfloat g_vertex_buffer_settings[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.12f, 0.35f,   0.90f, 0.0f,
        -0.55f, -0.16f, 0.35f,  0.10f, 0.0f, //settings
        -0.65f, -0.19f, 0.35f,  0.10f, 1.0f
    };

    static const GLfloat g_vertex_buffer_score[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f

        -0.65f, -0.25f, 0.35f,   0.90f, 0.0f,
        -0.55f, -0.30f, 0.35f,  0.10f, 0.0f, //Settings
        -0.65f, -0.35f, 0.35f,  0.10f, 1.0f
    };

    static const GLfloat g_vertex_buffer_exit[] = { 
        
        -1.0f, -1.0f, 0.0f,       0.0f, 1.0f, //1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f,      0.0f, 0.0f, //1.0f, 0.0f
        1.0f, 1.0f, 0.0f,       1.0f, 0.0f, //0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, //0.0f, 1.0f
        
        -0.65f, -0.37f, 0.35f,   0.90f, 0.0f,
        -0.55f, -0.43f, 0.35f,  0.10f, 0.0f, //Exit
        -0.65f, -0.47f, 0.35f,  0.10f, 1.0f,
        
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
    switch(this->_input)
    {
        case 0:
            //std::cout << "Start" << std::endl;
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_start), g_vertex_buffer_start, GL_STATIC_DRAW);
        break;  

        case 1:
            //std::cout << "continue" << std::endl;
             glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_continue), g_vertex_buffer_continue, GL_STATIC_DRAW);
        break;
       
        case 2:
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_settings), g_vertex_buffer_settings, GL_STATIC_DRAW);
        break;
    
        case 3:
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_score), g_vertex_buffer_score, GL_STATIC_DRAW);
        break;
    
        case 4:
            glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_exit), g_vertex_buffer_exit, GL_STATIC_DRAW);
        break;          
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

void MainMenu::LoadMainMenuImage()
{       
   // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, menuTexture);
	// Use our shader
    glUseProgram(programID);   
    
    // Draw the triangle !
	glBindVertexArray(menuVAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

int MainMenu::getInput()
{
	return _input;
}

void MainMenu::menuCleanup()
{
    // Cleanup VBO
    glDeleteBuffers(1, &menuVBO);
    glDeleteBuffers(1, &menuEBO);
    glDeleteVertexArrays(1, &menuVAO);
    glDeleteProgram(programID);
}
