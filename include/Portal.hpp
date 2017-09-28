#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "Bomberman.hpp"
#include "Player.hpp"

class Portal
{
public:
    Portal();
    ~Portal();
    
    void init();
    void draw();

private:
    GLuint portalTexture, vao, vbo;

};
#endif
