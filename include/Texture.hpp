#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include "glew.h"
#include "glfw3.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

class Texture 
{
    private:
        GLuint _mtexture;
    Texture(const Texture& other);
    void operator=(const Texture& other);
    public:
        Texture(const std::string& filename, GLuint *texture);
        ~Texture(void);
        void Bind(unsigned int unit);
};

#endif
