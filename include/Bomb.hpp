#ifndef BOMB_HPP
#define BOMB_HPP

#include "Bomberman.hpp" 
#include "camera.hpp"
#include "loader.hpp"

class Bomb
{
	private:
		int countdown;
		int radius;
		int time_dropped;
        bool load_result;
    bool _bombPlanted;

		GLfloat x;
		GLfloat y;
		/////////////////////////////////////////////////////////////////////////////
		//GLfloat xPos, yPos;
		GLuint bomb_programID, pUVO, pVAO, pVBO, pEBO, pBombId;
		glm::mat4 _view;
	    glm::mat4 _model;
	    glm::mat4 _projection;
		unsigned int _modelLoc;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec2> _uvbuffer;
		std::vector<glm::vec3> normals;
		/////////////////////////////////////////////////////////////////////////////

		
	
	public:
		Bomb(int radius);
		Bomb(void);
		~Bomb(void);
		void display(void);
		void updateLocation(void);

		int get_countdown(void);
		int get_radius(void);
		int get_bombStatus(void);
		GLfloat get_x(void);
		GLfloat get_y(void);
    bool getBombPlanted(void);
    void setBombPlanted(bool bombPlanted);

		void set_countdown(int countdown);
		void set_radius(int radius);
		void set_x(GLfloat x);
		void set_y(GLfloat y);

		void explode(void);
		void drop(void);
};

#endif
