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
    void    displayTime();
    float returnTime();
    void setTime(float time);
	float getTime();
    void    increaseTime();
    float     time;

private:
    GLuint timerTexture, vao, vbo;

};
#endif
