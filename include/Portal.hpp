#ifndef PORTAL_HPP
#define PORTAL_HPP

#define STATIC_WALLS 64

#include "Bomberman.hpp"
#include "Player.hpp"

class Portal{
public:
    Portal();
    ~Portal();
    
    void init();
    void test();
    void draw();

private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS], vao, vbo;

};
#endif