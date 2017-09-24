#ifndef _WALL_HPP
#define _WALL_HPP

#include "Player.hpp"

class Wall
{
public:
	Wall();
	Wall(int x, int y, bool isDec);
	~Wall();

	void init();
	void draw();
    GLfloat getXPos();
    GLfloat getYPos();

private:
	int xPos;
	int yPos;
	bool isDestructable;
	GLuint VertexArrayID, vertexbuffer, wallTexture;
   	GLuint	elementBuffer;

};

#endif

