#include "MainMenu.hpp"

MainMenu::MainMenu() {}

MainMenu::MainMenu(GLFWwindow* window, Graphics *g)
{
   Input command;
   this->_input = command.Start;
   this->_window = window;
   graphics = g;
}

MainMenu::~MainMenu(){
	delete graphics;
}

void MainMenu::gameStart(){
    
}

void MainMenu::gameContinue(){

}
void MainMenu::gameSettings(){

}

void MainMenu::executeCommand(int input){
    Input command;
    switch(input){
        case command.Start :
            std::cout << "Start" << std::endl;
			graphics->drawElements();
        break;
        case command.Continue :
            std::cout << "Continue" << std::endl;
        break;
        case command.Settings :
             std::cout << "Settings" << std::endl;
        break;
        case command.Exit :
            std::cout << "Exit" << std::endl;      
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
            std::cout << _input << std::endl;
            break;
        
        case GLFW_KEY_UP :
            this->_input--;
            if(_input < command.Start)
                this->_input = command.Exit;
            std::cout << _input << std::endl;
            break;
        case GLFW_KEY_ENTER :
               executeCommand(_input);
    }
}

void MainMenu::setGraphics(Graphics *g)
{
    graphics = g;
}

int MainMenu::getInput()
{
    return _input;
}
