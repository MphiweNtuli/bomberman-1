#include "Player.hpp"

Player::Player()
{
	xPos = -1.15f;
	yPos = 2.075f;
}

Player::~Player()
{
	glDeleteBuffers(1, &pVAO);
	glDeleteBuffers(1, &pVBO);
	glDeleteBuffers(1, &pEBO);
	glDeleteProgram(programID);
}

void Player::init()
{
	programID = LoadShaders("TransformationFragmentShader.hlsl", "TextureFragmentShader.hlsl");

	GLfloat vertices[] = {
        //bottom
        -0.89f, 0.85f, -0.05f,  0.0f, 0.0f, //0
        -0.85f, 0.85f, -0.05f,  1.0f, 0.0f, //1
        -0.89, 0.81f, -0.05f,  0.0f, 1.0f,  //2
        -0.89, 0.81f, -0.05f,  0.0f, 1.0f,  //2
        -0.85, 0.81f, -0.05f,  1.0f, 1.0f,  //3
        -0.85f, 0.85f, -0.05f, 1.0f, 0.0f, //1
        
        //top
        -0.89f, 0.85f, 0.05f,  0.0f, 0.0f, //4
        -0.85f, 0.85f, 0.05f,  1.0f, 0.0f, //5
        -0.89, 0.81f, 0.05f,  0.0f, 1.0f,  //6
        -0.89, 0.81f, 0.05f,  0.0f, 1.0f,  //6
        -0.85, 0.81f, 0.05f,  1.0f, 1.0f,  //7
        -0.85f, 0.85f, 0.05f,  1.0f, 0.0f, //5
        
        //front
        -0.89f, 0.85f, -0.05f,  0.0f, 0.0f, //0
        -0.85f, 0.85f, -0.05f,  1.0f, 0.0f, //1
        -0.89f, 0.85f, 0.05f,  0.0f, 1.0f, //4
        -0.89f, 0.85f, 0.05f,  0.0f, 1.0f, //4
        -0.85f, 0.85f, 0.05f,  1.0f, 1.0f, //5
        -0.85f, 0.85f, -0.05f,  1.0f, 0.0f, //1
        
        //back
        -0.89, 0.81f, -0.05f,  0.0f, 0.0f,  //2
        -0.85, 0.81f, -0.05f,  1.0f, 0.0f,  //3
        -0.89, 0.81f, 0.05f,  0.0f, 1.0f,  //6
        -0.89, 0.81f, 0.05f,  0.0f, 1.0f,  //6
        -0.85, 0.81f, 0.05f,  1.0f, 1.0f,  //7
        -0.85, 0.81f, -0.05f,  1.0f, 0.0f,  //3
        
        //side right
        -0.85f, 0.85f, -0.05f,  0.0f, 0.0f, //1
        -0.85, 0.81f, -0.05f,  1.0f, 0.0f,  //3
        -0.85f, 0.85f, 0.05f,  0.0f, 1.0f, //5
        -0.85f, 0.85f, 0.05f,  0.0f, 1.0f, //5
        -0.85, 0.81f, 0.05f,  1.0f, 1.0f,  //7
        -0.85, 0.81f, -0.05f,  1.0f, 0.0f,  //3
        
        //side left
        -0.89f, 0.85f, -0.05f,  0.0f, 0.0f, //0
        -0.89, 0.81f, -0.05f,  1.0f, 0.0f,  //2
        -0.89f, 0.85f, 0.05f,  0.0f, 1.0f, //4
        -0.89f, 0.85f, 0.05f,  0.0f, 1.0f, //4
        -0.89, 0.81f, 0.05f,  1.0f, 1.0f,  //6
        -0.89, 0.81f, -0.05f,  1.0f, 0.0f,  //2
        
	};

	/*unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};*/

	glGenVertexArrays(1, &pVAO);
	//glGenBuffers(1, &pEBO);
	glGenBuffers(1, &pVBO);
	glBindVertexArray(pVAO);
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pEBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Texture pTexture("bombermanImage.png", &pTextureId);

	/*glm::mat4 projection;
	projection = glm::perspective(glm::radians(30.0f), (float)1027 / (float)768, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);*/
}

void Player::moveUp()
{
	if (yPos < 2.075f)
		yPos += 0.025f;
}

void Player::moveDown()
{	
	if (yPos > 0.175f)
		yPos -= 0.025f;
}

void Player::moveLeft()
{
	if (xPos >= -1.15f)
		xPos -= 0.025f;
}
void Player::moveRight()
{
	if (xPos < 0.77f)
    {
		xPos += 0.025f;
        //std::cout << "pos x "<<xPos << std::endl;
    }
}

void Player::transform()
{
	// create transformations
	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(xPos, yPos, -1.0f));
	float angle = 20.0f * 0;
	transform = glm::rotate(transform, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(35.0f), (float)1024 / (float)768, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);

	// get matrix's uniform location and set matrix
	glUseProgram(programID);
	unsigned int transformLoc = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Player::draw()
{
	glUseProgram(programID);
	//camera.cameraFunction(programID);
	//draw player
	glBindTexture(GL_TEXTURE_2D, pTextureId);
	glBindVertexArray(pVAO);
	//glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_POINTS, 0, 14);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/* emsimang: experimental code*/

GLuint Player::getPVAO()
{
	return pVAO;
}

GLuint Player::getPVBO()
{
	return pVBO;
}

GLuint Player::getPEBO()
{
	return pEBO;
}

GLuint Player::getPTextureId()
{
	return pTextureId;
}

/* emsimang: experimental code*/

GLfloat Player::getYPos()
{
	return yPos;
}

GLfloat Player::getXPos()
{
	return xPos;
}

GLuint Player::getProgramId()
{
	return programID;
}
