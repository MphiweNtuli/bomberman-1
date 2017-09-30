
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <cassert>
#include <iostream>

class Texture 
{

    private:
        GLuint _mtexture;
        Texture(const Texture& other) {}
        void operator=(const Texture& other) {}
    public:
        Texture(const std::string& filename);
        ~Texture(void);
        void Bind(unsigned int unit);
};
