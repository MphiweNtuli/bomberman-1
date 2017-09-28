#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#define TEXT_OK 1
#define TEXT_ERR 2
#define TEXT_READY 3
#define TEXT_NOT_READY 4

#include "Bomberman.hpp" 
#include "ft2build.h"
#include FT_FREETYPE_H

class Text
{
    private:
        FT_Library ft;
        FT_Face font;
        FT_GlyphSlot gs;
        GLuint tex;
        GLuint vbo;
        GLuint programID;
        GLint attribute_coord;
        GLint uniform_tex;
        int font_size;
        int status;

        void Init(void);
        int LoadChar(char c);
    public:
        Text(void);
        ~Text(void);
        
        int Render(const char *text, float x, float y, float sx, float sy);

        int GetFontSize(void);
        int GetStatus(void);
        
        int SetFontSize(int font_size);
};

#endif