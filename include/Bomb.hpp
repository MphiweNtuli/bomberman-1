#ifndef BOMB_HPP
#define BOMB_HPP

#include "Bomberman.hpp" 
#include "camera.hpp"
#include "loader.hpp"
#include <GLUT/glut.h>


class Bomb
{
	private:
		int countdown;
		int radius;
		int time_dropped;

		GLfloat x;
		GLfloat y;
		/////////////////////////////////////////////////////////////////////////////
		//GLfloat xPos, yPos;
		GLuint bomb_programID, pUVO, pVAO, pVBO, pEBO, pBombId;
		glm::mat4 _view;
	    glm::mat4 _model;
	    glm::mat4 _projection;
		unsigned int _modelLoc;
		unsigned int _vmodelLoc;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec2> _uvbuffer;
		std::vector<glm::vec3> normals;
		/////////////////////////////////////////////////////////////////////////////

		
	
	public:
		Bomb(int radius, GLfloat x, GLfloat y);
		Bomb(void);
		~Bomb(void);
		void display(void);
		void updateLocation(void);

		int get_countdown(void);
		int get_radius(void);
		int get_bombStatus(void);
		GLfloat get_x(void);
		GLfloat get_y(void);

		void set_countdown(int countdown);
		void set_radius(int radius);
		void set_x(GLfloat x);
		void set_y(GLfloat y);

		void explode(void);
		void drop(void);
};

#endif
