#ifndef _DESTRUCTIBLE_HPP
#define _DESTRUCTIBLE_HPP

#define STATIC_WALLS 64
#define OFS_X 0.017f
#define OFS_Y -0.02f

#include "Bomberman.hpp"

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
    bool destroy();
    void set_xy(GLfloat x, GLfloat y);
    std::list<Wall> getWalls() const;
    
private:
    GLuint VertexArrayID, destructibleTexture;
    GLuint programID, VAOs[STATIC_WALLS], VBOs[STATIC_WALLS], EBOs[STATIC_WALLS], vao, vbo;
    GLfloat x,y;
    std::list<Wall> walls;

};

#endif
