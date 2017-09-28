#ifndef MAINMENU_HPP
# define MAINMENU_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
# include <iostream>

#include "Window.hpp"
#include "shader.hpp"
#include "settings.hpp"

struct Input
{
    enum GameCommands{
        Start,
        Continue,
        Settings,
        HighScore,
        Exit,
        ToggleSound,
        ToggleScreen,
    };
};

class MainMenu
{
    public:
		MainMenu();
        MainMenu(GLFWwindow *window, Window &, Graphics *g);
        ~MainMenu();

        MainMenu(MainMenu & obj);
        MainMenu& operator=(MainMenu& obj);

        void gameStart();
        void gameSettings(int input);
        void gameContinue();
        void modSound();
        int getSoundVal();
        void gameExit();
        Window getGameWindow();
        void toggleCommands(int input);
        void executeCommand(int command);
        void setGraphics(Graphics *g);
        void gameHighScore();
        void initMenuImage();
        void LoadMainMenuImage();
        void menuCleanup();

        int getInput();
    
    private:
        int _input;
        GLFWwindow* _window;
        Window _gameWindow;
        Graphics *graphics;
        int _sound_val;
        Settings *settings;
        GLuint menuVAO, menuTexture, menuEBO, menuVBO, programID;
};

#endif
