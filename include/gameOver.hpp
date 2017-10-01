#ifndef SETTINGS_HPP
# define SETTINGS_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
# include <iostream>

#include "Window.hpp"
#include "shader.hpp"

struct settingsInput
{
    enum GameCommands{
        Sound,
        Screen,
        Return,
    };
};
 
class Settings
{
    public:
		Settings();
        Settings(GLFWwindow *window, Window &, Graphics *g);
        ~Settings();
 
        Settings(Settings& obj);
        Settings& operator=(Settings& obj);
        void Music();
        void Screen(/*int input*/);
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
        void initSettingsImage();
        void LoadSettingsImage();
        void SettingsCleanup();
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
