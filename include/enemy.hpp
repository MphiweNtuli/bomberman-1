#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Bomberman.hpp" 
#include "camera.hpp"
#include "loader.hpp"
#include "Destructible.hpp"


#define WALL 0.08f
#define ENEMY 0.1f
#define OFS_X 0.017f
#define OFS_Y -0.02f

class Enemy
{
	public:
		
		Enemy(std::vector<Wall> walls);
		~Enemy(void);
		void init(void);
		void updateLocation(void);
		
		void set_x(GLfloat x);
		void set_y(GLfloat y);
		void setWalls(std::vector<Wall> walls);

		void checkCollision();
		bool moveUp(); 
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		void enemy_callback();
		void setDestructible(Destructible destructible);
		Destructible getDestructible(void);
		void setDestructible01(Destructible destructible01);
		Destructible getDestructible01(void);
		void remove(std::vector<int> removeWalls);
		
		

		GLfloat get_xPos(void) const;
		GLfloat get_yPos(void) const;
		int getX() const;
		int getY() const;

	private:
        bool load_result;

		/////////////////////////////////////////////////////////////////////////////
		Destructible _des, _des01;		
		GLfloat xPos;
		GLfloat yPos;
		GLuint enemy_programID, pUVO, pVAO, pVBO, pEBO, enemyTextId;
		glm::mat4 _view;
	    glm::mat4 _model;
	    glm::mat4 _projection;
		unsigned int _modelLoc;
		std::vector<glm::vec3> _vertices;
		std::vector<glm::vec2> _uvbuffer;
		std::vector<glm::vec3> normals;

		int x;
		int y;
		std::vector<Wall> walls;
		/////////////////////////////////////////////////////////////////////////////
		
};

#endif
