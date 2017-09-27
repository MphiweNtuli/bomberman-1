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

void Text::Init(void)
{
    if (this->status == TEXT_ERR || this->status == TEXT_READY)
        return;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &(this->tex));
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glUniform1i(uniform_tex, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenBuffers(1, &(this->vbo));
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
    this->status = TEXT_READY;
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

int Text::Render(const char *text, float x, float y, float sx, float sy)
{
    int loop;
  
    loop = 0;
    if (this->status == TEXT_ERR)
        return TEXT_ERR;
    this->Init();
    while (text[loop] != '\0')
    {
      if(this->LoadChar(text[loop]) == TEXT_ERR)
          continue;
      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        this->gs->bitmap.width,
        this->gs->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        this->gs->bitmap.buffer
      );
      float x2 = x + this->gs->bitmap_left * sx;
      float y2 = -y - this->gs->bitmap_top * sy;
      float w = this->gs->bitmap.width * sx;
      float h = this->gs->bitmap.rows * sy;
      GLfloat box[4][4] = {
          {x2,     -y2    , 0, 0},
          {x2 + w, -y2    , 1, 0},
          {x2,     -y2 - h, 0, 1},
          {x2 + w, -y2 - h, 1, 1},
      };
      glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
      x += (this->gs->advance.x/64) * sx;
      y += (this->gs->advance.y/64) * sy;
      loop++;
    }
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