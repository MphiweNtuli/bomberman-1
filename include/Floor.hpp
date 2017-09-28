#ifndef _FLOOR_HPP
#define _FLOOR_HPP

//#include <GL/glew.h>
#include "Player.hpp"

class Floor
{
public:
    Floor();
    ~Floor();
    
    void init();
    void draw();
    
private:
    GLuint VAO, VBO, EBO, floorTexture;
};

#endif