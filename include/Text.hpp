#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#define TEXT_OK 1
#define TEXT_ERR 2

#include <iostream>

#include "ft2build.h"
#include FT_FREETYPE_H

class Text
{
    private:
        FT_Library ft;
        FT_Face font;
        FT_GlyphSlot gs;
        int font_size;
        int status;
    public:
        Text(void);
        ~Text(void);
        
        int LoadChar(char c);

        int GetFontSize(void);
        int GetStatus(void);
        
        int SetFontSize(int font_size);
};

#endif