#ifndef WINDOW_HPP
# define WINDOW_HPP

//# include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Graphics.hpp"

class Window
{
public:
    Window();
    ~Window();

    void runGame();
    void initiateSystems();
    void terminateSystems();
    void setGraphics(Graphics g);

    GLFWwindow* getWindow();

private:
    GLFWwindow* _window;
    Graphics *graphics;     
};

#endif