#ifndef _DESTRUCTIBLE_HPP
#define _DESTRUCTIBLE_HPP

#define STATIC_WALLS 64

#include "Bomberman.hpp"
#include "Player.hpp"
#include "Maze.hpp"

class Destructible
{
public:
    Destructible();
    ~Destructible();
    
    void init1();
    void init2();
    void init3();
    void test();
    void draw();
    
    Maze getMaze();
    
private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS], vao, vbo;
    Maze maze;

};

#endif
