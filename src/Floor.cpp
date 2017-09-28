/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Floor.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:28:53 by tditshwe          #+#    #+#             */
/*   Updated: 2017/08/14 15:29:07 by tditshwe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Floor.hpp"

Floor::Floor()
{
    glDeleteBuffers(1, &VBO);
}

Floor::~Floor()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Floor::init()
{
    Texture texture("mud.jpg", &floorTexture);
    
    
    //set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // texture coords
        -1.0f, -1.0f, -0.06f,   0.0f, 0.0f,  //0
        0.9f, -1.0f, -0.06f,   20.0f, 0.0f,  //1
        -1.0f,  0.9f, -0.06f,   0.0f, 20.0f,  //3
        -1.0f,  0.9f,-0.06f,   0.0f, 20.0f,  //3
        0.9f,  0.9f, -0.06f,   20.0f, 20.0f, //2
        0.9f, -1.0f, -0.06f,   20.0f, 0.0f,  //1
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

void Floor::draw()
{
    //render floor
    glBindVertexArray(VAO);
    //bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
