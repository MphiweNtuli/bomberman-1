#include "Texture.hpp"


Texture::Texture(const std::string& filename)
{
    int width;
    int height;
    int numComponents;
    unsigned char* image_data;
    char const *flnm = filename.c_str();

    image_data = stbi_load(flnm, &width, &height, &numComponents, 4);

    if(image_data == NULL)
    {
        std::cout << "image loading failed in texture.cpp \n";
    }
    else
        std::cout << "image loaded fine in texture.cpp \n";

    glGenTextures(1, &_mtexture);
    glBindTexture(GL_TEXTURE_2D, _mtexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
   
    stbi_image_free(image_data);
    std::cout << "done in texture \n";
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &_mtexture);
}

void Texture::Bind(unsigned int unit)
{
    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, _mtexture);
}
