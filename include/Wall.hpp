#ifndef _WALL_HPP
#define _WALL_HPP
#include "Bomberman.hpp"

class Wall
{
public:
	Wall();
	Wall(GLfloat x, GLfloat y, bool isDec);
	~Wall();

	void init();
	void draw();
    GLfloat getXPos();
    GLfloat getYPos();
    void    setIsDestroyed(bool isDestroyed);
    bool	isDestroyed();

private:
	GLfloat xPos, yPos;
	bool isDestructable, destroyed;
	GLuint VertexArrayID, vertexbuffer, wallTexture;

};

#endif

