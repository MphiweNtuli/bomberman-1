#include "timer.hpp"

Timer::Timer()
{
    time = 90;
}

Timer::~Timer(){}

void Timer::displayTime(){
    //std::cout << time - glfwGetTime() << std::endl;
}

void Timer::increaseTime(){
    time += 30;
}

float Timer::returnTime(){
    if ((time - glfwGetTime()) < 0)
        return (0);
	std::cout << "time to display " << (time - glfwGetTime()) << std::endl;
    return (time - glfwGetTime());
}

void Timer::setTime(float time)
{
    this->time = time;
}

float Timer::getTime()
{
	return this->time;
}

void Timer::init()
{
	Texture texture("BombermanModels/powerUps/cl.jpg", &timerTexture);

    GLfloat vertexData[] =
    {
        0.6f, 0.7f, -0.05f,      0.0f, 0.0f, //0
        0.7f, 0.7f, -0.05f,      1.0f, 0.0f, //1
        0.7f, 0.8f, -0.05f,      1.0f, 1.0f, //2
        0.7f, 0.8f, -0.05f,      1.0f, 1.0f, //2
        0.6f, 0.8f, -0.05f,      0.0f, 1.0f, //3
        0.6f, 0.7f, -0.05f,      0.0f, 0.0f, //0
    };
 
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}



void Timer::draw()
{
    glBindTexture(GL_TEXTURE_2D, timerTexture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
