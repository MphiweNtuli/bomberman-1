#ifndef _TEXT_BACK_HPP
#define _TEXT_BACK_HPP

//#include <GL/glew.h>
#include "Player.hpp"

class Text_Back
{
public:
    Text_Back();
    ~Text_Back();
    
    void init();
    void draw();
    
private:
    GLuint VAO, VBO, EBO, Text_BackTexture;
};

#endif