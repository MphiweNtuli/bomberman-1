#ifndef _WALL_HPP
#define _WALL_HPP

#include "Bomberman.hpp"
#include "serialize.hpp"

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

private:
	GLfloat xPos, yPos;
	bool isDestructable;
	GLuint VertexArrayID, vertexbuffer, wallTexture;
	GLuint	elementBuffer;
    template <class archive> friend
    void boost::serialization::serialize(archive &ar, Wall &w, const unsigned int version);
};

#endif

