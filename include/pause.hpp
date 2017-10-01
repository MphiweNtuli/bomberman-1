#ifndef PAUSE_HPP
# define PAUSE_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
# include <iostream>

#include "Window.hpp"
#include "shader.hpp"
#include "Player.hpp"
#include "GameState.hpp"

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
        void setWindow(GLFWwindow *, Window &, Graphics *);
        void toggleCommands(/*GLFWwindow* window, */int key);
        void executeCommand(int command);
        void setGraphics(Graphics *g);
        // void gameHighScore();
        void initPauseImage();
        void LoadPauseImage();
        void PauseCleanup();
        void updateVals(Player *p, std::vector<GLfloat> *w);

        int getInput();
    
    private:
        int _input;
        GLFWwindow* _window;
        Window _gameWindow;
        Graphics *graphics;
        int _sound_val;
        GLuint menuVAO, menuTexture, menuEBO, menuVBO, programID;
        Player *p;
        GameState gs;
        std::vector<GLfloat> *walls;
};

#endif
