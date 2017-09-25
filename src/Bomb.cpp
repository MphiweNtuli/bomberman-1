#include "Bomb.hpp"

Bomb::Bomb(int radius, GLfloat x, GLfloat y)
{
	 std::cout << "top of constructer \n";
	this->countdown = 3;
	this->radius = radius;
	//this->x = x;
	//this->y = y;
	this->time_dropped = 0;
	//this->display();
	// std::cout << "insider constructer \n";
	bomb_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	Texture * text = new Texture("BombermanModels/bombs/bombText.png", &pBombId);
	// _model = glm::translate(_model, glm::vec3(0.0f,  -0.4f, -3.5f));
	// //this->xPos = 0.0f;
	// //this->yPos = 0.0f;
	// _model = glm::mat4(1.0);
	// //_model = glm::translate(_model, glm::vec3(0.4f,  -0.4f, -0.4f));

	// _projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
	// _model = glm::translate(_model, glm::vec3(x,  y, -3.5f));
	// //_model = glm::rotate(_model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
 //    //_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	// _model = glm::scale(_model, glm::vec3(0.9));
 
	// _view       = glm::lookAt(
	// 	glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
	// 	glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
	// 	glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
 //   );

   bool res = loadOBJ("BombermanModels/bombs/bomb.obj", _vertices, _uvbuffer, normals); 
 //   //std::cout << "end of constructer \n";


}

Bomb::Bomb(void)
{
	this->countdown = 0;
	this->radius = 0;
	//this->x = 0;
	//this->y = 0;
}

Bomb::~Bomb(void)
{
	return ;
}

int Bomb::get_countdown(void)
{
	return this->countdown;
}

int Bomb::get_radius(void)
{
	return this->radius;
}

GLfloat Bomb::get_x(void)
{
	return this->x;
}

GLfloat Bomb::get_y(void)
{
	return this->y;
}

void Bomb::set_countdown(int countdown)
{
	this->countdown = countdown;
}

void Bomb::set_radius(int radius)
{
	this->radius = radius;
}

void Bomb::set_x(GLfloat x)
{ 
	this->x = x;
}

void Bomb::set_y(GLfloat y)
{
	this->y = y;
}

void Bomb::updateLocation(void)
{
	//bomb_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	//Texture* text = new Texture("BombermanModels/bombs/bombText.png", &pBombId);
	//this->xPos = 0.0f;
	//this->yPos = 0.0f;
	std::cout << "update \n";
	_model = glm::mat4(1.0);

	this ->x = get_x();
	this ->y = get_y();



	//_model = glm::translate(_model, glm::vec3(0.4f,  -0.4f, -0.4f));

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
	//std::cout << get_x() << " <-- x   " << this ->x << "and " << this ->y << " :  y -->  " << get_y() << "\n";

	// _model = glm::translate(_model, glm::vec3(0.0f,  -0.4f, -3.5f));
	_model = glm::translate(_model, glm::vec3(this->x, this ->y , -3.82f));
	// _model = glm::translate(_model, glm::vec3(0.0f,  get_y(), get_x()));
	// _model = glm::translate(_model, glm::vec3(0.0f,  -0.4f, -3.5f));
	
	_model = glm::scale(_model, glm::vec3(1.0));
 
	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );

   //bool res = loadOBJ("BombermanModels/bombs/bomb.obj", _vertices, _uvbuffer, normals); 
	this -> x = 0.0f;
	this -> y = 0.0f;
//	std::cout << get_x() << " <-- x   " << this ->x << "and " << this ->y << " :  y -->  " << get_y() << "\n";

   display();
   //std::cout << "end of constructer \n";


}

int Bomb::get_bombStatus(void)
{
	return this->time_dropped;
}

void Bomb::explode(void)
{
	// print particles and collision here
	if (this->time_dropped == 0)
		return;
	if (glfwGetTime() - this->time_dropped >= (this->countdown * 2.0f))
	{
			
			this->time_dropped = 0;
	}
}

void Bomb::drop(void)
{
	if (this->time_dropped == 0)
	{
		this->display();
		this->time_dropped = glfwGetTime();
		std::cout << "Bomb planted" << std::endl;
	}
}


void Bomb::display(void)
{
	// display bomb
		//updateLocation();
		glUseProgram(bomb_programID);
	
		_view = getViewMatrix();

		glm::mat4 ProjectionMatrix = _projection;
		glm::mat4 ViewMatrix = _view;
		glm::mat4 ModelMatrix = _model;

		glUniformMatrix4fv(glGetUniformLocation(bomb_programID, "transform"), 1, GL_FALSE, &_projection[0][0]);
		//std::cout << "bomb draw" << std::endl;

		_modelLoc = glGetUniformLocation(bomb_programID, "model");
		glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(glGetUniformLocation(bomb_programID, "view"), 1, GL_FALSE, &_view[0][0]);

		glGenBuffers(1, &pVAO);
		glBindBuffer(GL_ARRAY_BUFFER, pVAO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

		GLuint pUVO;
		glGenBuffers(1, &pUVO);
		glBindBuffer(GL_ARRAY_BUFFER, pUVO);
		glBufferData(GL_ARRAY_BUFFER, _uvbuffer.size() * sizeof(glm::vec2), &_uvbuffer[0], GL_STATIC_DRAW);
		

		glBindTexture(GL_TEXTURE_2D, pBombId);

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
	return;
}






