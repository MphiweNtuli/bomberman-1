#include "health.hpp"

Health::Health(){}

Health::~Health(){}

void Health::init()
{
    Texture texture("BombermanModels/powerUps/health.png", &healthTexture);

    GLfloat vertexData[] =
    {
        -0.9f, -0.6f, -0.05f,      0.0f, 0.0f, //0
        -0.8f, -0.6f, -0.05f,      1.0f, 0.0f, //1
        -0.8f, -0.7f, -0.05f,      1.0f, 1.0f, //2
        -0.8f, -0.7f, -0.05f,      1.0f, 1.0f, //2
        -0.9f, -0.7f, -0.05f,      0.0f, 1.0f, //3
        -0.9f, -0.6f, -0.05f,      0.0f, 0.0f, //0
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



void Health::draw()
{
    glBindTexture(GL_TEXTURE_2D, healthTexture);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
