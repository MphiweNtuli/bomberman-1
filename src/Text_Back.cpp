#include "Text_Back.hpp"

Text_Back::Text_Back()
{
    glDeleteBuffers(1, &VBO);
}

Text_Back::~Text_Back()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Text_Back::init()
{
    Texture texture("mud.jpg", &Text_BackTexture);
    
    
    //set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // texture coords
        0.6f, 1.0f, -0.04f,   0.0f, 0.0f,  //0
        0.6f, 0.6f, -0.04f,   20.0f, 0.0f,  //1
        -0.6f,  1.0f, -0.04f,   0.0f, 20.0f,  //3
        -0.6f,  1.0f,-0.04f,   0.0f, 20.0f,  //3
        -0.6f, 0.6f, -0.04f,   20.0f, 20.0f, //2
        0.6f, 0.6f, -0.04f,   20.0f, 0.0f,  //1
    };
    
    
   /* unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };*/
    
    
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
}

void Text_Back::draw()
{
    //render Text_Back
    glBindVertexArray(VAO);
    //bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Text_BackTexture);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
