#ifndef SCORE_HPP
#define SCORE_HPP

#define ERRLIB 1
#define ERRFONT 2
#define ERRUNIF 3

#include "Bomberman.hpp"
#include "shader_utils.hpp"

// struct point {
// 	GLfloat x;
// 	GLfloat y;
// 	GLfloat s;
// 	GLfloat t;
// };

class ScoreBar {
    public:
        int init();
        ScoreBar();
        ~ScoreBar();
        void display();
        int getLevel();
        int getScore();
        int getGameTime();
        GLuint getProgramId();
        void render_text(const char *text, float x, float y, float sx, float sy);

    private:
        int score;
        int gameTime;
        int gameLevel;

        GLuint tex;
        GLuint vbo;
        GLuint program;
        FT_Library ft;
        FT_Face fontface;
        GLint uniform_tex;
        // struct point point;
        GLint uniform_color;
        GLint attribute_coord;
        FT_GlyphSlot gslot;
};

#endif