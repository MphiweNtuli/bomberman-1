#ifndef _STATICWALL_HPP
#define _STATICWALL_HPP

#define STATIC_WALLS 64

#include "Player.hpp"
#include "Maze.hpp"

class StaticWall
{
public:
    StaticWall();
    ~StaticWall();
    
    void init();
    void draw();
    Maze getMaze();
    
private:
    GLuint VertexArrayID, wallTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS];
    Maze maze;

};

#endif
