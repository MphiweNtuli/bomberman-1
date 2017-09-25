#ifndef _STATICWALL_HPP
#define _STATICWALL_HPP

#define STATIC_WALLS 64

#include "Player.hpp"
#include "Wall.hpp"
#include <list>

class StaticWall
{
public:
    StaticWall();
    ~StaticWall();
    
    void init();
    void draw();
    std::list<Wall> getWalls() const;
    
private:
    GLuint VertexArrayID, wallTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS];
    std::list<Wall> walls;

};

#endif
