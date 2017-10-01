#ifndef KEYBINDING_HPP
# define KEYBINDING_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
# include <iostream>

#include "Window.hpp"
#include "shader.hpp"
#include "Graphics.hpp"
#include "Bomberman.hpp"
#include "Player.hpp"

#define KEY_ARROWS -100
#define KEY_WASD -101
#define KEY_IJKL -102

struct keyInput
{
    enum GameCommands{
        Arrows,
        WASD,
        IJKL,
        Return,
    };
};
 
class Keys
{
    public:
		Keys();
        Keys(GLFWwindow *window, Window &, Graphics *g, Player *_player);
        ~Keys();
 
        Keys(Keys& obj);
        Keys& operator=(Keys& obj);
        void ArrowKeys();
        void WASDKeys();
        void IJKLKeys();
        // void Screen(/*int input*/);
        // void gameContinue();
        // void modSound();
        // // int getSoundVal();
        // void Return();
        // void modSound();
        // void modDisplay();
        // int getSoundVal();
        // bool getDispChange();
        void setWindow(GLFWwindow *, Window &, Graphics *);
        Window getGameWindow();
        void toggleCommands(/*GLFWwindow* window, */int key);
        void executeCommand(int command);
        void setGraphics(Graphics *g);
        // void gameHighScore();
        void initKeysImage();
        void LoadKeysImage();
        void KeysCleanup();
        int getInput();
    
    private:
        int _input;
        bool _dispChange;
        int _sound_val;      
        GLFWwindow* _window;
        Player *player;
        Window _gameWindow;
        Graphics *graphics;
        GLuint menuVAO, menuTexture, menuEBO, menuVBO, programID;
};

#endif
