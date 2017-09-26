#include "Text.hpp"

Text::Text(void)
{
    this->status = TEXT_ERR;
    if(FT_Init_FreeType(&(this->ft)))
        return;
    if(FT_New_Face(this->ft, "text/FreeSans.ttf", 0, &(this->font)))
        return;
    this->status = TEXT_OK;
    this->gs = NULL;
}

Text::~Text(void)
{
    return;
}

int Text::LoadChar(char c)
{
    if (this->GetStatus() == TEXT_ERR)
        return TEXT_ERR;
    if(FT_Load_Char(this->font, c, FT_LOAD_RENDER))
        return TEXT_ERR;
    this->gs = this->font->glyph;
    return TEXT_OK;
}

int Text::GetFontSize(void)
{
    return this->font_size;
}

int Text::GetStatus(void)
{
    return this->status;
}

int Text::SetFontSize(int font_size)
{
    if (this->GetStatus() == TEXT_ERR)
        return TEXT_ERR;
    this->font_size = font_size;
    FT_Set_Pixel_Sizes(this->font, 0, font_size);
    return TEXT_OK;
}