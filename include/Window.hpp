#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Sound.hpp"
#include "Graphics.hpp"
#include "WindowKeyEvents.hpp"

class Window
{
public:
    Window();
    ~Window();

    void runGame();
    void initiateSystems();
    void initiateSystems2();
    void terminateSystems();
    void setGraphics(Graphics g);
    bool initializeGlew();
    void changeWindowSize();

    Sound* getSound();
    GLFWwindow* getWindow();
    WindowKeyEvents* getEvents();

private:
    int _width;
    int _height;
    Sound *_sound;
    Graphics *graphics;
    GLFWwindow* _window;
    GLFWwindow* _fullWindow;
    WindowKeyEvents *_keyEvents;
};

#endif
