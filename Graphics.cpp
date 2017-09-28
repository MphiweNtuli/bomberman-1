/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 14:43:54 by tditshwe          #+#    #+#             */
/*   Updated: 2017/08/16 14:43:57 by tditshwe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphics.hpp"
#include <stdio.h>

Graphics::Graphics(GLuint vertexBuffer, GLuint VAOs[])
{
    this->vertexBuffer = vertexBuffer;
    
	for (int i = 0; i < 96; i++)
		this->VAOs[i] = VAOs[i];
}

void Graphics::initGlArrays(GLuint VBOs[], GLuint VAOs[], GLuint EBOs[])
{
	GLfloat vertices[96][12];
    GLfloat xLeft = -0.8f;
    GLfloat xRight = -0.7f;
    GLfloat fUnit = 0.2;
    
    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    
    int k = 0;
    for (int j = 0; j < 8; j++)
    {
        
        for (int i = 0; i < 8; i++)
        {
            //Bottom
            vertices[k][0] = xLeft + i * fUnit;
            vertices[k][1] = 0.7f - j * fUnit;
            vertices[k][2] = 0.0f;
            vertices[k][3] = xRight + i * fUnit;
            vertices[k][4] = 0.7f - j * fUnit;
            vertices[k][5] = 0.0f;
            //Top
            vertices[k][6] = xLeft + i * fUnit;
            vertices[k][7] = 0.8f - j * fUnit;
            vertices[k][8] = 0.0f;
            vertices[k][9] = xRight + i * fUnit;
            vertices[k][10] = 0.8f - j * fUnit;
            vertices[k][11] = 0.0f;
            
            glGenVertexArrays(1, &VAOs[k]);
            glGenBuffers(1, &EBOs[k]);
            glGenBuffers(1, &VBOs[k]);
            glBindVertexArray(VAOs[k]);
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[k]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[k]), vertices[k], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[k]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
			//text.Bind(0);
            glVertexAttribPointer(
                                  0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                                  3,                  // size
                                  GL_FLOAT,           // type
                                  GL_FALSE,           // normalized?
                                  0,                  // stride
                                  (void*)0            // array buffer offset
                                  );
            glEnableVertexAttribArray(0);
            k++;
        }
    }
}

void Graphics::drawElements()
{
    // Draw the triangle !
    glBindVertexArray(vertexBuffer); 
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0); // 3 indices starting at 0 -> 1 triangle
                                                         //trin logic
    for (int i = 0; i < 96; i++)
    {
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 3 indices starting at 0 -> 1 triangle
    }
}
