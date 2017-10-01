//Gary
#include "enemy.hpp"
//#include "Player.hpp"
#include "Bomberman.hpp"

Enemy::Enemy(std::vector<Wall> walls, GLfloat x_in, GLfloat y_in)
{	
	x = 0;
	y = 0;
	direction = "left";
	direction1 = "up";
	isdead = false;
	
	enemy_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	Texture text("BombermanModels/enemies/e1/enemy1Text.png", &enemyTextId);

	_model = glm::mat4(1.0);
	initX = x_in;
	initY = y_in;

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
	//_model = glm::translate(_model, glm::vec3(-0.75f,  0.16f, -3.82f));
	_model = glm::translate(_model, glm::vec3(x_in,  y_in, -3.82f));
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	yPos = _model[3][1];
	xPos = _model[3][0];
	_model2 = _model;
	_model = glm::scale(_model, glm::vec3(0.8));
	// _model2 = _model;
 
	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );

   load_result = loadOBJ("BombermanModels/enemies/e1/enemy1.obj", _vertices, _uvbuffer, normals);
   //load_result = loadOBJ("BombermanModels/bomberman.obj", _vertices, _uvbuffer, normals);
   if (load_result != true)
	   std::cout << "failed to load Enemy object model" << std::endl;

   this->walls = walls;
}

void Enemy::bomb_colision(GLfloat bx, GLfloat by)
{
	if(glm::distance(glm::vec2(bx,  by) , glm::vec2(xPos, yPos)) <= 0.12f)
		set_isdead(true);
}

void Enemy::refresh()
{
	x = 0;
	y = 0;
	isdead = false;
	std::vector<Wall> v;
	walls.swap(v);
	_model = _model2;//glm::translate(_model, glm::vec3(initX,  initY, -3.82f));
	yPos = _model[3][1];
	xPos = _model[3][0];
}

bool	Enemy::get_isdead(void)const
{
	return this->isdead;
}

void	Enemy::set_isdead(bool death)
{
	this->isdead = death;
}

void	Enemy::remove(std::vector<int> removeWalls)
{
	std::vector<Wall>::iterator it;
	std::vector<int>::iterator iter;

	int wall_it = 0;
	for (it = walls.begin(); it != walls.end(); ++it)
	{
		wall_it++;
		if(wall_it > 64)
    		for (iter = removeWalls.begin(); iter != removeWalls.end(); ++iter)
				if (wall_it - 64 == *iter)
					it->setIsDestroyed(true);
	}
}


Enemy::~Enemy(void)
{
	return ;
}

int Enemy::getX() const{
	return this->x;
}

int Enemy::getY() const{
	return this->y;
}

GLfloat Enemy::get_xPos(void) const
{
    return this->xPos;
}

GLfloat Enemy::get_yPos(void) const
{
    return this->yPos;
}

void Enemy::updateLocation(void)
{
	_model = glm::mat4(1.0);

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);

	_model = glm::translate(_model, glm::vec3(this->x, this ->y , -3.82f));
	
	_model = glm::scale(_model, glm::vec3(1.0));
 
	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );
}

bool Enemy::moveUp()
{
	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((yPos + 0.098 > it->getYPos() + OFS_Y && yPos + 0.098 < it->getYPos() + OFS_Y + 0.09) && !it->isDestroyed())
			if(xPos + 0.03 > it->getXPos() + OFS_X && xPos < it->getXPos() + OFS_X + 0.09)
					return false;
		}
		if (yPos + 0.098 > 0.87)
			return false;
		
	
	
		return true;
	
}

bool Enemy::moveDown()
{
	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((yPos + 0.04 > it->getYPos() + OFS_Y && yPos + 0.03 < it->getYPos() + OFS_Y + 0.09) && !it->isDestroyed())
			if(xPos + 0.03 > it->getXPos() + OFS_X && xPos < it->getXPos() + OFS_X + 0.09)
				return false;
		}
		if (yPos - 0.098 < -0.98)
			return false;
	
		return true;

}

bool Enemy::moveLeft()
{

	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((xPos - 0.03 > it->getXPos() + OFS_X && xPos + 0.05 < it->getXPos() + OFS_X + 0.2) && !it->isDestroyed())
			if(yPos - 0.03 < it->getYPos() + OFS_Y && yPos + 0.03 > it->getYPos() + OFS_Y - 0.06)
						return false;
		}
		if (xPos - 0.1 < -0.1)
			return false;
		
		return true;
			
}

bool Enemy::moveRight()
{

	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((xPos + 0.05 > it->getXPos() + OFS_X && xPos - 0.02 < it->getXPos() + OFS_X + 0.07) && !it->isDestroyed())
			if(yPos - 0.03 < it->getYPos() + OFS_Y && yPos + 0.03 > it->getYPos() + OFS_Y - 0.06)
				return false;
		}
		if (xPos + 0.098 > 0.88)
			return false;
	
		return true;
}

void Enemy::init(void)
{
	// Initialise Enemy
		glUseProgram(enemy_programID);
	
		_view = getViewMatrix();

		glm::mat4 ProjectionMatrix = _projection;
		glm::mat4 ViewMatrix = _view;
		glm::mat4 ModelMatrix = _model;

		glUniformMatrix4fv(glGetUniformLocation(enemy_programID, "transform"), 1, GL_FALSE, &_projection[0][0]);
		
		if(y == 1 && x != 1)
		{
			_model = glm::rotate(_model, glm::radians(90.0f * (x - y)), glm::vec3(0.0f, 1.0f, 0.0f));
			x = y;
		}
		else if(y == 2 && x != 2)
		{
			_model = glm::rotate(_model, glm::radians(90.0f * (x - y)), glm::vec3(0.0f, 1.0f, 0.0f));
			x = y;
		}
		else if(y == 3 && x != 3)
		{
			_model = glm::rotate(_model, glm::radians(90.0f * (x - y)), glm::vec3(0.0f, 1.0f, 0.0f));
			x = y;
		}
		else if(y == 4 && x != 4)
		{
			_model = glm::rotate(_model, glm::radians(90.0f * (x - y)), glm::vec3(0.0f, 1.0f, 0.0f));
			x = y;
		}

		_modelLoc = glGetUniformLocation(enemy_programID, "model");
		glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(glGetUniformLocation(enemy_programID, "view"), 1, GL_FALSE, &_view[0][0]);

		glGenBuffers(1, &pVAO);
		glBindBuffer(GL_ARRAY_BUFFER, pVAO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &pUVO);
		glBindBuffer(GL_ARRAY_BUFFER, pUVO);
		glBufferData(GL_ARRAY_BUFFER, _uvbuffer.size() * sizeof(glm::vec2), &_uvbuffer[0], GL_STATIC_DRAW);
		

		glBindTexture(GL_TEXTURE_2D, enemyTextId);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, pUVO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, pVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0 );
		
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size() );

		glDeleteBuffers(1, &pVAO);
		glDeleteBuffers(1, &pVBO);
		glDeleteBuffers(1, &pEBO);
}

void	Enemy::setWalls(std::vector<Wall> walls)
{
	std::vector<Wall>::iterator it;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		this->walls.push_back(*it);
	}
}

void Enemy::enemy_callback()
{
	glm::vec3 bills(0.0,0.0,0.006);
	if(moveRight() && direction == "right") {
		_model = glm::translate(_model, bills);
		xPos = _model[3][0];

		if (x != 3)
		y = 3;
	}
	else
		direction = "left";

	if(moveLeft() && direction == "left") {
		_model = glm::translate(_model, bills);
		xPos = _model[3][0];

		if (x != 1)
		y = 1; 
	}
	else 
		direction = "right";

	if(moveUp() && direction1 == "up"){
		_model = glm::translate(_model, bills);
		yPos = _model[3][1];

		if (x != 2)
		y = 2;
	}
	else 
		direction1 = "down";

	if(moveDown() && direction1 == "down") {
		_model = glm::translate(_model, bills);
		yPos = _model[3][1];

		if (x != 4)
		y = 4;
	}
	else 
	direction1 = "up";
   

}

void Enemy::setDestructible(Destructible destructible)
{
	std::cout << "set destructible" << std::endl;
    _des = destructible;
}

Destructible Enemy::getDestructible(void)
{
    return _des;
}

void Enemy::setDestructible01(Destructible destructible01)
{
    _des01 = destructible01;
}

Destructible Enemy::getDestructible01(void)
{
    return _des01;
}
