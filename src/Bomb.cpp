#include "Bomb.hpp"

Bomb::Bomb(int radius, GLfloat x, GLfloat y)
{
	std::cout << "top of constructer \n";
	this->countdown = 3;
	this->radius = radius;
	this->x = x;
	this->y = y;
	this->time_dropped = 0;
    this->timer = 0;
	//this->display();
//    this->displayExplosion();
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
    
    glGenVertexArrays(1, &pVAO);
    
    glGenBuffers(1, &pVBO);
    glBindVertexArray(pVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    Texture pTexture("grenade.jpg", &bombTex);
    
    
    GLfloat v_explosion[] = {
        //bottom
        -0.89f, 0.75f, -0.05f,  0.0f, 0.0f, //0
        -0.75f, 0.75f, -0.05f,  1.0f, 0.0f, //1
        -0.89, 0.81f, -0.05f,  0.0f, 1.0f,  //2
        -0.89, 0.81f, -0.05f,  0.0f, 1.0f,  //2
        -0.75, 0.81f, -0.05f,  1.0f, 1.0f,  //3
        -0.75f, 0.75f, -0.05f, 1.0f, 0.0f, //1
        
        //top
        -0.89f, 0.75f, 0.05f,  0.0f, 0.0f, //4
        -0.75f, 0.75f, 0.05f,  1.0f, 0.0f, //5
        -0.89, 0.81f, 0.05f,  0.0f, 1.0f,  //6
        -0.89, 0.81f, 0.05f,  0.0f, 1.0f,  //6
        -0.75, 0.81f, 0.05f,  1.0f, 1.0f,  //7
        -0.75f, 0.75f, 0.05f,  1.0f, 0.0f, //5
        
        //front
        /*-0.89f, 0.85f, -0.05f,  0.0f, 0.0f, //0
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
        -0.89, 0.81f, -0.05f,  1.0f, 0.0f,  //2*/
        
    };
    
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_explosion), v_explosion, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    Texture tex("explosion.jpg", &explosionTex);
    
    
}

void Bomb::transformBomb()
{
    // create transformations
    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(x, y, -1.0f));
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

void Bomb::transformExplosion()
{
    // create transformations
    glm::mat4 transform;
    transform = glm::translate(transform, glm::vec3(this->get_x(), this->get_y(), -1.0f));
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


Bomb::Bomb(void)
{
    this->countdown = 0;
    this->radius = 0;
	this->x = 0;
	this->y = 0;
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

int Bomb::get_timer()
{
    return this->timer;
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
int Bomb::get_bombStatus(void)
{
	return this->time_dropped;
}

void Bomb::explode(void)
{
    showExplosion();
	// print particles and collision here
	if (this->time_dropped == 0)
		return;
	if (glfwGetTime() - this->time_dropped >= (this->countdown * 2.0f))
	{
        this->time_dropped = 0;
        std::cout << "explosion"<< std::endl;
        this->timer = glfwGetTime();
        displayExplosion();
//        showExplosion();
	}
}

void Bomb::showExplosion(void)
{
    if (this->timer == 0)
    {
        return;
    }
    //this->displayExplosion();
    if (glfwGetTime() - this->timer >= (this->countdown * 2.0f))
    {
        this->timer = 0;
        //std::cout << "explosion"<< std::endl;
//        this->displayExplosion();
    }
    
}

void Bomb::drop(void)
{
	if (this->time_dropped == 0)
	{
		this->display();
		this->time_dropped = glfwGetTime();
		std::cout << "Bomb planted"  << glfwGetTime() << std::endl;
	}
}


void Bomb::display(void)
{
    glUseProgram(programID);
    glBindTexture(GL_TEXTURE_2D, bombTex);
    glBindVertexArray(pVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Bomb::displayExplosion(void)
{
    glUseProgram(programID);
    glBindTexture(GL_TEXTURE_2D, explosionTex);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

GLuint Bomb::getProgramId() const
{
    return programID;
}
