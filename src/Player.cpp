#include "Player.hpp"
#include "Bomberman.hpp"

Player::Player(std::list<Wall> walls)
{
	x = 0;
	y = 0;
	texture_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	Texture* text = new Texture("BombermanModels/bombermanText.png", &pTextureId);
	this->xPos = 0.0f;
	this->yPos = 0.0f;
	_model = glm::mat4(1.0);
	//_model = glm::translate(_model, glm::vec3(0.4f,  -0.4f, -0.4f));

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
	//_model = glm::translate(_model, glm::vec3(-0.6f,  0.6f, -4.356f));
	//_model = glm::rotate(_model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_model = glm::translate(_model, glm::vec3(-0.6f,  0.6f, -3.82f));
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//_model = glm::rotate(_model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	yPos = _model[3][1];
	xPos = _model[3][0];
	
	_model = glm::scale(_model, glm::vec3(0.12));

	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );

   bool res = loadOBJ("BombermanModels/bomberman.obj", _vertices, _uvbuffer, normals);
   this->walls = walls;
}

void	Player::setWalls(std::list<Wall> walls)
{
	std::list<Wall>::iterator it;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		this->walls.push_back(*it);
	}
}

Player::~Player()
{
	glDeleteBuffers(1, &pVAO);
	glDeleteBuffers(1, &pVBO);
	glDeleteBuffers(1, &pEBO);
	glDeleteProgram(texture_programID);
}

void Player::init()
{
		glUseProgram(texture_programID);
	
		_view = getViewMatrix();

		glm::mat4 ProjectionMatrix = _projection;
		glm::mat4 ViewMatrix = _view;
		glm::mat4 ModelMatrix = _model;

		glUniformMatrix4fv(glGetUniformLocation(texture_programID, "transform"), 1, GL_FALSE, &_projection[0][0]);

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
		_modelLoc = glGetUniformLocation(texture_programID, "model");
		glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(glGetUniformLocation(texture_programID, "view"), 1, GL_FALSE, &_view[0][0]);

		glGenBuffers(1, &pVAO);
		glBindBuffer(GL_ARRAY_BUFFER, pVAO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

		GLuint pUVO;
		glGenBuffers(1, &pUVO);
		glBindBuffer(GL_ARRAY_BUFFER, pUVO);
		glBufferData(GL_ARRAY_BUFFER, _uvbuffer.size() * sizeof(glm::vec2), &_uvbuffer[0], GL_STATIC_DRAW);
		
		//pTextureId = Texture;

		glBindTexture(GL_TEXTURE_2D, pTextureId);

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

bool Player::moveUp()
{
	std::list<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			//std::cout << it->getXPos() + OFS_X << "  ,  " << it->getYPos() + OFS_Y << "   Player Player! " << xPos << "   ,  " << yPos << "\n ";
			if(yPos + 0.098 > it->getYPos() + OFS_Y && yPos + 0.098 < it->getYPos() + OFS_Y + 0.09)
				if(xPos  > it->getXPos() + OFS_X && xPos < it->getXPos() + OFS_X + 0.09)
				{
					if(wall_it > 64)
						std::cout << wall_it - 64 << "  : Wall number\n";
					//std::cout << "Player:" << xPos << "," << yPos << " Walls:" << it->getXPos() + OFS_X << "," << it->getYPos() + OFS_Y << "   COLISSION" << std::endl;
					return false;
				}
		}
		
	
	
		return true;
	
}

bool Player::moveDown()
{
	std::list<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
		//std::cout << it->getXPos() + OFS_X << "  ,  " << it->getYPos() + OFS_Y << "   Player Player! " << xPos << "   ,  " << yPos << "\n ";
			if(yPos + 0.04 > it->getYPos() + OFS_Y && yPos + 0.03 < it->getYPos() + OFS_Y + 0.09)
				if(xPos + 0.03 > it->getXPos() + OFS_X && xPos < it->getXPos() + OFS_X + 0.09)
				{
					if(wall_it > 64)
						std::cout << wall_it - 64 << "  : Wall number\n";
					//std::cout << "Player:" << xPos << "," << yPos << " Walls:" << it->getXPos() + OFS_X << "," << it->getYPos() + OFS_Y << "   COLISSION" << std::endl;
					return false;
				}
		}
		
	
	
		return true;

}

bool Player::moveLeft()
{

	std::list<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			//std::cout << it->getXPos() + OFS_X << "  ,  " << it->getYPos() + OFS_Y << "   Player Player! " << xPos << "   ,  " << yPos << "\n ";
				if(xPos - 0.03 > it->getXPos() + OFS_X && xPos + 0.05 < it->getXPos() + OFS_X + 0.15)
					if(yPos - 0.03 < it->getYPos() + OFS_Y && yPos + 0.03 > it->getYPos() + OFS_Y - 0.06)
					{
						if(wall_it > 64)
							std::cout << wall_it - 64 << "  : Wall number\n";
						//std::cout << "Player:" << xPos << "," << yPos << " Walls:" << it->getXPos() + OFS_X << "," << it->getYPos() + OFS_Y << "   COLISSION" << std::endl;
						return false;
					}
		}
		
		return true;
			
}

bool Player::moveRight()
{

	std::list<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			//std::cout << it->getXPos() + OFS_X << "  ,  " << it->getYPos() + OFS_Y << "   Player Player! " << xPos << "   ,  " << yPos << "\n ";
			if(xPos + 0.05 > it->getXPos() + OFS_X && xPos - 0.02 < it->getXPos() + OFS_X + 0.07)
				if(yPos - 0.03 < it->getYPos() + OFS_Y && yPos + 0.03 > it->getYPos() + OFS_Y - 0.06)
				{
					if(wall_it > 64)
						std::cout << wall_it - 64 << "  : Wall number\n";
					return false;
				}
		}
	
		return true;
}

void Player::player_callback(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
		glm::vec3 bills(0.0,0.0,0.03);
		if(moveLeft()) {
			//xPos -= 0.03f;
			_model = glm::translate(_model, bills);
			xPos = _model[3][0];
		}
		if (x != 1)
			y = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {

		glm::vec3 bills(0.0,0.0,0.03);
		
		if(moveRight()) {
			//xPos += 0.03f;
			_model = glm::translate(_model, bills);
			xPos = _model[3][0];
		}
		// std::cout << _model[0][0] << " : " << _model[0][1] << " : " << _model[0][2] << "  :  " << _model[0][3] << " : \n" ;
		// std::cout << _model[1][0] << " : " << _model[1][1] << " : " << _model[1][2] << " : \n" ;
		// std::cout << _model[2][0] << " : " << _model[2][1] << " : " << _model[2][2] << " : \n" ;
		// std::cout << _model[3][0] << " : " << _model[3][1] << " : " << _model[3][2] << " : \n\n" ;
		if (x != 3)
		y = 3;
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
		glm::vec3 bills(0.0,0.0,0.03);
		
		if(moveUp()){
			//yPos -= 0.03f;
			_model = glm::translate(_model, bills);
			yPos = _model[3][1];
		}
		if (x != 2)
		y = 2;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
		glm::vec3 bills(0.0,0.0,0.03);
		
		if(moveDown()) {
			//yPos += 0.03f;
			_model = glm::translate(_model, bills);
			yPos = _model[3][1];
		}
		if (x != 4)
		y = 4;
    }
 //   switch 
    
}

GLfloat Player::get_xPos(void)
{
    return this->xPos;
}

GLfloat Player::get_yPos(void)
{
    return this->yPos;
}

void Player::draw()
{
	glUseProgram(texture_programID);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() );
}
