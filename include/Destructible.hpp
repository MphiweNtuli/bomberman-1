#ifndef _DESTRUCTIBLE_HPP
#define _DESTRUCTIBLE_HPP

#define STATIC_WALLS 64

#include "Bomberman.hpp"
#include "Player.hpp"

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
    std::list<Wall> getWalls() const;
    
private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS], vao, vbo;
    std::list<Wall> walls;

};

#endif
