#include "Player.hpp"
#include "Bomberman.hpp"

Player::Player()
{
}

Player::Player(std::vector<Wall> walls, Bomb *bomb)
{
    _bomb = bomb;
	x = 0;
	y = 0;
	texture_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	Texture text("BombermanModels/bombermanText.png", &pTextureId);
	this->xPos = 0.0f;
	this->yPos = 0.0f;
	_model = glm::mat4(1.0);

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
	_model = glm::translate(_model, glm::vec3(-0.6f,  0.6f, -3.82f));
	_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	yPos = _model[3][1];
	xPos = _model[3][0];
	
	_model = glm::scale(_model, glm::vec3(0.12));

	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );

   load_result = loadOBJ("BombermanModels/bomberman.obj", _vertices, _uvbuffer, normals);
    if (load_result != true)
        std::cout << "failed to load model" << std::endl;
   this->walls = walls;
}

void	Player::setWalls(std::vector<Wall> walls)
{
	std::vector<Wall>::iterator it;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		this->walls.push_back(*it);
	}
}

void	Player::remove(std::vector<int> removeWalls)
{
	std::vector<Wall>::iterator it;
	std::vector<int>::iterator iter;

	std::cout <<  "Is inside player function";
	int wall_it = 0;
	for (it = walls.begin(); it != walls.end(); ++it)
	{
		wall_it++;
		if(wall_it > 64)
		{
    		for (iter = removeWalls.begin(); iter != removeWalls.end(); ++iter)
				if (wall_it - 64 == *iter)
				{
					std::cout << wall_it - 64 << "  : Destroy Wall number\n";
					std::cout <<"X->"<< it->getXPos() <<", Y->" << it->getYPos() << "  : DOWN WALL IS Player!!!!!!!!!!!!!!!!!!!!!!\n";
					it = walls.erase(it);
					// it->setIsDestroyed(true);
					std::cout <<"X->"<< it->getXPos() <<", Y->" << it->getYPos() << "  : DOWN WALL IS Player!!!!!!!!!!!!!!!!!!!!!!\n";
				}
		}
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
		glDeleteBuffers(1, &pUVO);
		glDeleteBuffers(1, &pEBO);

}

bool Player::moveUp()
{
	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((yPos + 0.098 > it->getYPos() + OFS_Y && yPos + 0.098 < it->getYPos() + OFS_Y + 0.09) && !it->isDestroyed())
				if(xPos + 0.03 > it->getXPos() + OFS_X && xPos < it->getXPos() + OFS_X + 0.09)
				{
					if(wall_it > 64)
						std::cout << wall_it - 64 << "  : Wall number\n";
					return false;
				}
		}
		if (yPos + 0.098 > 0.87)
			return false;
		
	
	
		return true;
	
}

bool Player::moveDown()
{
	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((yPos + 0.04 > it->getYPos() + OFS_Y && yPos + 0.03 < it->getYPos() + OFS_Y + 0.09) && !it->isDestroyed())
				if(xPos + 0.03 > it->getXPos() + OFS_X && xPos < it->getXPos() + OFS_X + 0.09)
				{
					if(wall_it > 64)
						std::cout << wall_it - 64 << "  : Wall number\n";
					return false;
				}
		}
		if (yPos - 0.098 < -0.98)
			return false;
	
		return true;

}

bool Player::moveLeft()
{

	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
				if((xPos - 0.03 > it->getXPos() + OFS_X && xPos + 0.05 < it->getXPos() + OFS_X + 0.15) && !it->isDestroyed())
					if(yPos - 0.03 < it->getYPos() + OFS_Y && yPos + 0.03 > it->getYPos() + OFS_Y - 0.06)
					{
						if(wall_it > 64)
							std::cout << wall_it - 64 << "  : Wall number\n";
						return false;
					}
		}
		if (xPos - 0.098 < -0.98)
			return false;
		
		return true;
			
}

bool Player::moveRight()
{

	std::vector<Wall>::iterator it;
	int wall_it = 0;
		for (it = walls.begin(); it != walls.end(); ++it)
		{
			wall_it++;
			if((xPos + 0.05 > it->getXPos() + OFS_X && xPos - 0.02 < it->getXPos() + OFS_X + 0.07) && !it->isDestroyed())
				if(yPos - 0.03 < it->getYPos() + OFS_Y && yPos + 0.03 > it->getYPos() + OFS_Y - 0.06)
				{
					if(wall_it > 64)
						std::cout << wall_it - 64 << "  : Wall number\n";
					return false;
				}
		}
		if (xPos + 0.098 > 0.88)
			return false;
	
		return true;
}

void Player::player_callback(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
		glm::vec3 bills(0.0,0.0,0.03);
		if(moveLeft()) {
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
			_model = glm::translate(_model, bills);
			xPos = _model[3][0];
		}

		if (x != 3)
			y = 3;
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
		glm::vec3 bills(0.0,0.0,0.03);
		
		if(moveUp()){
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
			_model = glm::translate(_model, bills);
			yPos = _model[3][1];
		}
		if (x != 4)
			y = 4;
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && _bomb->get_bombStatus() == 0)
    {
        _bomb->set_x(get_xPos());
        _bomb->set_y(get_yPos());
        _des.set_xy(get_xPos(), get_yPos());
        _des01.set_xy(get_xPos(),get_yPos());
        _bomb->updateLocation();
        _bomb->drop();
        _bomb->setBombPlanted(true);
        std::cout << "Space pressed\n";
    }
    
}

void Player::setDestructible(Destructible destructible)
{
    _des = destructible;
}

Destructible Player::getDestructible(void)
{
    return _des;
}

void Player::setDestructible01(Destructible destructible01)
{
    _des01 = destructible01;
}

Destructible Player::getDestructible01(void)
{
    return _des01;
}

GLuint Player::getProgramId() const
{
    return texture_programID;
}

void Player::draw()
{
	glUseProgram(texture_programID);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() );
}

GLfloat Player::get_xPos(void) const
{
    return this->xPos;
}

GLfloat Player::get_yPos(void) const
{
    return this->yPos;
}

GLuint Player::getPVAO() const
{
    return pVAO;
}

GLuint Player::getPUVO() const
{
    return pUVO;
}

GLuint Player::getPEBO() const
{
    return pEBO;
}

GLuint Player::getPTextureId() const
{
    return pTextureId;
}

GLuint Player::getPProgramId() const
{
	return (programID);
}

GLuint Player::getPVBO() const{
	return this->pVBO;
}

glm::mat4 Player::getView() const{
	return this->_view;
}

glm::mat4 Player::getModel() const{
	return this->_model;
}

glm::mat4 Player::getProjection() const{
	return this->_projection;
}

unsigned int Player::getModelLoc() const{
	return this->_modelLoc;
}

unsigned int Player::getVmodelLoc() const{
	return this->_vmodelLoc;
}

std::vector<glm::vec3> Player::getVertices() const{
	return this->_vertices;
}

std::vector<glm::vec2> Player::getUvbuffer() const{
	return this->_uvbuffer;
}

std::vector<glm::vec3> Player::getNormals() const{
	return this->normals;
}

int Player::getX() const{
	return this->x;
}

int Player::getY() const{
	return this->y;
}

std::vector<Wall> Player::getWalls() const{
	return this->walls;
}

std::vector<float> Player::getModelV() const{
	return (_modelV);
}

void Player::operator=(const Player &p)
{
    this->xPos = p.get_xPos();
	this->yPos = p.get_yPos();
}

void Player::restorePosition(float x, float y)
{
	_model[3][0] = x;
	_model[3][1] = y;
	xPos = x;
	yPos = y;
}
void Player::mat4ToVector()
{
    int len = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int  j = 0; j < 4; j++)
        {
            len++;
            _modelV.push_back(_model[i][j]);
        }
    }
    _modelV.push_back(len);
}

void Player::vectorToMat4()
{
    int iv = 0;
    int len = _modelV.back();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0 && iv < len; j < 4; j++)
        {
            _model[i][j] = _modelV[iv++];
        }
    }
}

void Player::printMatrix(std::string s)
{
	std::ofstream ofs("logfile.txt", std::ios::app);
    for (int i = 0; i < 4; i ++)
    {
        if (i == 1)
            ofs << s.c_str() << "._model = {";
        if (i != 1)
            ofs << "         		{";
        for (int j = 0; j < 4; j++)
        {
            ofs << _model[i][j];
            if (j != 3)
                ofs << ", ";
        }
		ofs << "}" << std::endl;
    }
	ofs << "" << std::endl;		
}

int Player::printVector()
{
    int i = 0;
	int len = _modelV.back();
	std::ofstream ofs("logfile.txt", std::ios::app);
    if (!_modelV.size())
    {
        ofs << "vector is empty" << std::endl;
        return (1);
    }
    ofs << "_modelV = {";
    while (i < len)
    {
        ofs << _modelV[i];
        if (i < (len - 1))
            ofs << ", ";
        i++;
    }
	ofs << "}" << std::endl;
	ofs << "" << std::endl;
    return (0);
}