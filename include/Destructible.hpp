#ifndef _DESTRUCTIBLE_HPP
#define _DESTRUCTIBLE_HPP

#define STATIC_WALLS 64
#define OFS_X 0.017f
#define OFS_Y -0.02f

#include "Bomberman.hpp"

class Destructible
{
public:
    Destructible();
    ~Destructible();
    
    void init1();
    void init2();
    void init3();
    void draw(std::vector<GLfloat> destructibleToDraw);
    std::list<int> destroy(std::vector<GLfloat> &dest);
    void set_xy(GLfloat x, GLfloat y);
    std::list<Wall> getWalls() const;
    std::vector<GLfloat> getDestructibles(void);
    void removeDestructible(std::vector<GLfloat> &dest, int destNo);
    
private:
    GLuint destructibleTexture, vao, vbo;
    GLfloat x,y;
    std::list<Wall> walls;
    int _counter, _dataSize;
    std::vector<GLfloat> _destructibleList;
};

#endif
