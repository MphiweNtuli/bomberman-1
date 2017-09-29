#ifndef TIMER_HPP
#define TIMER_HPP

#include "Bomberman.hpp"
#include "Player.hpp"

class Timer{
public:
    Timer();
    ~Timer();
     
    void init();
    void draw();

private:
    GLuint timerTexture, vao, vbo;

};
#endif