#ifndef PAUSE_HPP
# define PAUSE_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
# include <iostream>

#include "Window.hpp"
#include "shader.hpp"

struct pauseInput
{
    enum commands{
        Resume,
        SaveGame,
        Return
    };
};
 
class PauseMenu
{
    public:
		PauseMenu();
        PauseMenu(GLFWwindow *window, Window &, Graphics *g);
        ~PauseMenu ();
 
        PauseMenu (PauseMenu& obj);
        PauseMenu &operator=(PauseMenu & obj);

        void Resume();
        void SaveGame(/*int input*/);
        // void gameContinue();
        // void modSound();
        // int getSoundVal();
        void Return();
        Window getGameWindow();
        void toggleCommands(/*GLFWwindow* window, */int key);
        void executeCommand(int command);
        void setGraphics(Graphics *g);
        // void gameHighScore();
        void initPauseImage();
        void LoadPauseImage();
        void PauseCleanup();

        int getInput();
    
    private:
        int _input;
        GLFWwindow* _window;
        Window _gameWindow;
        Graphics *graphics;
        int _sound_val;
        GLuint menuVAO, menuTexture, menuEBO, menuVBO, programID;
};

#endif
