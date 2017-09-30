#ifndef SCREEN_HPP
# define SCREEN_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
# include <iostream>

#include "Window.hpp"
#include "shader.hpp"


struct screenInput
{
    enum GameCommands{
        Full,
        Windowed,
        Medium,
        Large,
        ReturnMenu,
        ReturnSetting

    };
};
 
class Screen
{
    public:
		Screen();
        Screen(GLFWwindow *window, Window &, Graphics *g);
        ~Screen();
 
        Screen(Screen& obj);
        Screen& operator=(Screen& obj);
        // void Music();
        // void Screen(/*int input*/);
        // void gameContinue();
        // void modSound();
        // int getSoundVal();
        void Return();
        void modSound();
        void modDisplay();
        int getSoundVal();
        bool getDispChange();
        void setWindow(GLFWwindow *, Window &, Graphics *);
        Window getGameWindow();
        void toggleCommands(/*GLFWwindow* window, */int key);
        void executeCommand(int command);
        void setGraphics(Graphics *g);
        // void gameHighScore();
        void initScreenImage();
        void LoadScreenImage();
        void ScreenCleanup();
        int getInput();
    
    private:
        int _input;
        bool _dispChange;
        int _sound_val;      
        GLFWwindow* _window;
        Window _gameWindow;
        Graphics *graphics;
        GLuint menuVAO, menuTexture, menuEBO, menuVBO, programID;
};

#endif
