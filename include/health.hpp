#ifndef HEALTH_HPP
#define HEALTH_HPP

#define STATIC_WALLS 64

#include "Bomberman.hpp"
#include "Player.hpp"

class Health{
public:
    Health();
    ~Health();
     
    void init();
    //void test();
    void draw();

private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS], vao, vbo;

};
#endif