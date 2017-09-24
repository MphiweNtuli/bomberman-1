#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Texture.hpp"
#include "shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "serialize.hpp"

class Player
{
public:
	Player();
	~Player();
	void init();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void transform();
	void draw();

	/* emsimang: experimental code*/
	GLuint getPVAO() const;
	GLuint getPVBO() const;
	GLuint getPEBO() const;
	GLuint getPTextureId() const;
	void operator=(const Player &p);
	void setCoordinates(GLfloat x, GLfloat y);
	/* emsimang: experimental code*/

	GLfloat getXPos() const;
	GLfloat getYPos() const;
	GLuint getProgramId() const;

private:
	GLfloat xPos, yPos;
	GLuint programID, pVAO, pVBO, pEBO, pTextureId;
	template <class archive> friend
	void boost::serialization::serialize(archive &ar, Player &p, const unsigned int version);
};

#endif
