#ifndef TIMER_HPP
#define TIMER_HPP

#define STATIC_WALLS 64

#include "Bomberman.hpp"
#include "Player.hpp"

class Timer{
public:
    Timer();
    ~Timer();
     
    void init();
    //void test();
    void draw();
    void    displayTime();
    void    icreaseTime();
    int     time;

private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS], vao, vbo;

};
#endif