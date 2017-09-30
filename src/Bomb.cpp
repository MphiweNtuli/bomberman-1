#include "Bomb.hpp"

Bomb::Bomb(int radius)
{
	 std::cout << "top of constructer \n";
	this->countdown = 2;
	this->radius = radius;
    this->_bombPlanted = false;

	this->time_dropped = 0;
	bomb_programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	Texture text("BombermanModels/bombs/bombText.png", &pBombId);

   load_result = loadOBJ("BombermanModels/bombs/bomb.obj", _vertices, _uvbuffer, normals);
    if (load_result != true)
		std::cout << "failed to load object model" << std::endl;

}

Bomb::Bomb(void)
{
	this->countdown = 0;
	this->radius = 0;
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
	_model = glm::mat4(1.0);

	_projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);

	_model = glm::translate(_model, glm::vec3(this->x, this ->y , -3.82f));
	
	_model = glm::scale(_model, glm::vec3(1.0));
 
	_view       = glm::lookAt(
		glm::vec3(-1.0f, 2.0f,  3.0f), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, -1.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f,  1.0f)  // Head is up (set to 0,-1,0 to look upside-down)
   );
   display();
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
	if (glfwGetTime() - this->time_dropped >= (this->countdown * 1.0f))
	{
		GLuint tmp = pBombId;
		Texture text("BombermanModels/exp/flames.jpeg", &pBombId);
		std::vector<glm::vec3> _vert;
		_vert.swap(_vertices);
		std::vector<glm::vec2> _uv;
		_uv.swap(_uvbuffer);	

		load_result = loadOBJ("BombermanModels/exp/explo.obj", _vertices, _uvbuffer, normals);
		_model = glm::rotate(_model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		_model = glm::scale(_model, glm::vec3(0.12));

		display();

		_vertices.swap(_vert);
		_uvbuffer.swap(_uv);
		pBombId = tmp;
		
		this->time_dropped = 0;
	}
	
}

void Bomb::drop(void)
{
	if (this->time_dropped == 0)
	{
		this->display();
		this->time_dropped = glfwGetTime();
	}
}

bool Bomb::getBombPlanted(void)
{
    return _bombPlanted;
}

void Bomb::setBombPlanted(bool bombPlanted)
{
    _bombPlanted = bombPlanted;
}


void Bomb::display(void)
{
	// display bomb
		glUseProgram(bomb_programID);
		_view = getViewMatrix();

		glm::mat4 ProjectionMatrix = _projection;
		glm::mat4 ViewMatrix = _view;
		glm::mat4 ModelMatrix = _model;

		glUniformMatrix4fv(glGetUniformLocation(bomb_programID, "transform"), 1, GL_FALSE, &_projection[0][0]);

		_modelLoc = glGetUniformLocation(bomb_programID, "model");
		glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
		glUniformMatrix4fv(glGetUniformLocation(bomb_programID, "view"), 1, GL_FALSE, &_view[0][0]);

		glGenBuffers(1, &pVAO);
		glBindBuffer(GL_ARRAY_BUFFER, pVAO);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

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
