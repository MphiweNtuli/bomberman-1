#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Bomberman.hpp" 
#include "camera.hpp"
#include "loader.hpp"

class Enemy
{
	private:
		// int countdown;
		// int radius;
		// int time_dropped;
        bool load_result;
  //   bool _bombPlanted;

		GLfloat x;
		GLfloat y;
		/////////////////////////////////////////////////////////////////////////////
		//GLfloat xPos, yPos;
		GLuint enemy_programID, pUVO, pVAO, pVBO, pEBO, enemyTextId;
		glm::mat4 _view;
	    glm::mat4 _model;
	    glm::mat4 _projection;
		unsigned int _modelLoc;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec2> _uvbuffer;
		std::vector<glm::vec3> normals;
		/////////////////////////////////////////////////////////////////////////////

		
	
	public:
		// Enemy(int radius);
		Enemy(void);
		~Enemy(void);
		void display(void);
		void updateLocation(void);

		// int get_countdown(void);
		// int get_radius(void);
		// int get_bombStatus(void);
		GLfloat get_x(void);
		GLfloat get_y(void);
    	//bool getBombPlanted(void);
    	// void setBombPlanted(bool bombPlanted);

		// void set_countdown(int countdown);
		// void set_radius(int radius);
		void set_x(GLfloat x);
		void set_y(GLfloat y);

		// void explode(void);
		// void drop(void);
};

#endif
