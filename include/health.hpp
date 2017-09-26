#ifndef HEALTH_HPP
#define HEALTH_HPP

#include "Bomberman.hpp"
#include "Player.hpp"

class Health{
public:
    Health();
    ~Health();
     
    void init();
    void draw();

private:
    GLuint healthTexture, vao, vbo;

};
#endif
