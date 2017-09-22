#include "Player.hpp"
#include "Bomberman.hpp"


Player::Player()
{
	bomb = new Bomb(3, 0, 0);
	x = 0;
	y = 0;
	texture_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	Texture* text = new Texture("BombermanModels/Bomberman/bombermanText.png", &pTextureId);
	this->xPos = 0.0f;
	this->yPos = 0.0f;
	_model = glm::mat4(1.0);
	//_model = glm::translate(_model, glm::vec3(0.4f,  -0.4f, -0.4f));

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
	_model = glm::translate(_model, glm::vec3(0.0f,  -0.4f, -3.5f));
	_model = glm::rotate(_model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	_model = glm::scale(_model, glm::vec3(0.1));

	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );

   bool res = loadOBJ("BombermanModels/Bomberman/bomberman.obj", _vertices, _uvbuffer, normals); 
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
		//std::cout << "Player draw" << std::endl;

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

void Player::moveUp()
{
	yPos += 0.025f;
}

void Player::moveDown()
{
	yPos -= 0.025f;
}

void Player::moveLeft()
{
	xPos -= 0.025f;
}
void Player::moveRight()
{
	xPos += 0.025f;
}

void Player::player_callback(GLFWwindow* window)
{
	
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
    	glm::vec3 bills(0.0,0.0,0.03);
		_model = glm::translate(_model, bills);
		if (x != 1)
			y = 1;
      //  std::cout << "a\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
    	glm::vec3 bills(0.0,0.0,0.03);
		_model = glm::translate(_model, bills);
		if (x != 3)
		y = 3;
    //    std::cout << "dt\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
    	glm::vec3 bills(0.0,0.0,0.03);
		_model = glm::translate(_model, bills);
		if (x != 2)
		y = 2;
        //std::cout << "a\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
    	glm::vec3 bills(0.0,0.0,0.03);
		_model = glm::translate(_model, bills);
		if (x != 4)
		y = 4;
      //  std::cout << "dt\n";
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
    	bomb->set_x(this->xPos);
    	bomb->set_y(this->yPos);
    	bomb->drop();
    }
 //   switch 
    
}

void Player::draw()
{
	glUseProgram(texture_programID);
	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() );
}
