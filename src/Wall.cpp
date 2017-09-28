/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:28:53 by tditshwe          #+#    #+#             */
/*   Updated: 2017/09/18 11:03:38 by rmoswela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wall.hpp"

Wall::Wall()
{
	glDeleteBuffers(1, &vertexbuffer);
}

Wall::Wall(GLfloat x, GLfloat y, bool isDec)
{
	xPos = x;
	yPos = y;
	isDestructable = isDec;
    destroyed = false;
}

Wall::~Wall()
{
	glDeleteVertexArrays(1, &VertexArrayID);
}

bool    Wall::isDestroyed()
{
    return destroyed;
}

void    Wall::setIsDestroyed(bool isDestroyed)
{
    this->destroyed = isDestroyed;
}

void Wall::init()
{

	Texture texture("brick2.jpg", &wallTexture);
    
    static const GLfloat vertexData[] = {
        /*wall up direction*/
        //bottom
        -1.0f, 0.8f, -0.05f,        0.0f, 0.0f,  //0
        0.9f,  0.8f,  -0.05f,       20.0f, 0.0f, //1
        0.9f,  0.9f, -0.05f,        20.0f, 1.0f, //2
        -1.0f, 0.8f, -0.05f,        0.0f, 0.0f,  //0
        -1.0f, 0.9f, -0.05f,        0.0f, 1.0f,  //3
        0.9f,  0.9f,  -0.05f,       20.0f, 0.0f, //2
        
        //top
        -1.0f, 0.8f, 0.05f,         0.0f, 0.0f,  //4
        0.9f,  0.8f,  0.05f,        20.0f, 0.0f, //5
        0.9f,  0.9f, 0.05f,         20.0f, 1.0f, //6
        -1.0f, 0.8f, 0.05f,         0.0f, 0.0f,  //4
        -1.0f, 0.9f, 0.05f,         0.0f, 1.0f,  //7
        0.9f,  0.9f, 0.05f,         20.0f, 1.0f, //6
        
        //side left
        -1.0f, 0.8f, -0.05f,        0.0f, 0.0f,  //0
        -1.0f, 0.9f, -0.05f,        1.0f, 0.0f,  //3
        -1.0f, 0.9f, 0.05f,         1.0f, 1.0f,  //7
        -1.0f, 0.8f, -0.05f,        0.0f, 0.0f,  //0
        -1.0f, 0.8f, 0.05f,         0.0f, 1.0f,  //4
        -1.0f, 0.9f, 0.05f,         1.0f, 1.0f,  //7
        
        //side right
        0.9f,  0.8f,  -0.05f,       0.0f, 0.0f, //1
        0.9f,  0.9f, -0.05f,        1.0f, 0.0f, //2
        0.9f,  0.9f, 0.05f,         1.0f, 1.0f, //6
        0.9f,  0.8f,  -0.05f,       0.0f, 0.0f, //1
        0.9f,  0.8f,  0.05f,        0.0f, 1.0f, //5
        0.9f,  0.9f, 0.05f,         1.0f, 1.0f, //6
        
        
        //front
        -1.0f, 0.8f, -0.05f,        0.0f, 0.0f,  //0
        0.9f,  0.8f,  -0.05f,       20.0f, 0.0f, //1
        0.9f,  0.8f,  0.05f,        20.0f, 1.0f, //5
        -1.0f, 0.8f, -0.05f,        0.0f, 0.0f,  //0
        -1.0f, 0.8f, 0.05f,         0.0f, 1.0f,  //4
        0.9f,  0.8f,  0.05f,        20.0f, 1.0f, //5
        
        //back
        -1.0f, 0.9f, -0.05f,        0.0f, 0.0f,  //3
        0.9f,  0.9f,  -0.05f,       20.0f, 0.0f, //2
        0.9f,  0.9f, 0.05f,         20.0f, 1.0f, //6
        -1.0f, 0.9f, -0.05f,        0.0f, 0.0f,  //3
        -1.0f, 0.9f, 0.05f,         0.0f, 1.0f,  //7
        0.9f,  0.9f, 0.05f,         20.0f, 1.0f, //6
        
        
        /*wall right direction*/
        //bottom
        0.8f,  0.9f, -0.05f,		0.0f, 0.0f, //8
        0.8f, -0.9f, -0.05f,		20.0f, 0.0f,  //9
        0.9f,  0.9f,  -0.05f,       20.0f, 1.0f, //1
        0.9f,  0.9f,  -0.05f,       20.0f, 1.0f, //1
        0.9f, -0.9f, -0.05f,		0.0f, 1.0f,  //10
        0.8f, -0.9f, -0.05f,		20.0f, 0.0f,  //9
        
        //top
        0.8f,  0.9f, 0.05f,         20.0f, 1.0f,  //11
        0.8f, -0.9f, 0.05f,         0.0f, 1.0f,   //12
        0.9f,  0.9f, 0.05f,         20.0f, 0.0f,  //13
        0.9f,  0.9f, 0.05f,         20.0f, 0.0f,  //13
        0.9f, -0.9f, 0.05f,         0.0f, 0.0f,   //14
        0.8f, -0.9f, 0.05f,         0.0f, 1.0f,   //12
        
        //front
        0.8f,  0.9f, -0.05f,		0.0f, 0.0f,  //8
        0.8f,  0.9f, 0.05f,         0.0f, 1.0f,  //11
        0.8f, -0.9f, -0.05f,		20.0f, 0.0f,   //9
        0.8f, -0.9f, -0.05f,		20.0f, 0.0f,   //9
        0.8f, -0.9f, 0.05f,         20.0f, 1.0f,   //12
        0.8f,  0.9f, 0.05f,         0.0f, 1.0f,  //11
        
        //back
        0.9f,  0.9f,  -0.05f,       0.0f, 0.0f, //1
        0.9f,  0.9f, 0.05f,         0.0f, 1.0f,  //13
        0.9f, -0.9f, -0.05f,		20.0f, 0.0f,  //10
        0.9f, -0.9f, -0.05f,		20.0f, 0.0f,  //10
        0.9f, -0.9f, 0.05f,         0.0f, 1.0f,   //14
        0.9f,  0.9f, 0.05f,         20.0f, 1.0f,  //13
        

        /*wall left direction*/
        //bottom
        -1.0f, 0.9f, -0.05f,		20.0f, 1.0f, //15
        -1.0f, -0.9f, -0.05f,		0.0f, 1.0f,  //16
        -0.9f, 0.9f, -0.05f,		20.0f, 0.0f, //17
        -0.9f, 0.9f, -0.05f,		20.0f, 0.0f, //17
        -0.9f, -0.9f, -0.05f,		0.0f, 0.0f,  //18
        -1.0f, -0.9f, -0.05f,		0.0f, 1.0f,  //16
        
        //top
        -1.0f, 0.9f, 0.05f,         20.0f, 1.0f, //19
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //20
        -0.9f, 0.9f, 0.05f,         20.0f, 0.0f, //21
        -0.9f, 0.9f, 0.05f,         20.0f, 0.0f, //21
        -0.9f, -0.9f, 0.05f,		0.0f, 0.0f,  //22
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //20
        
        //front
        -0.9f, 0.9f, -0.05f,		0.0f, 0.0f, //17
        -0.9f, 0.9f, 0.05f,         0.0f, 1.0f, //21
        -0.9f, -0.9f, -0.05f,		20.0f, 0.0f,  //18
        -0.9f, -0.9f, -0.05f,		20.0f, 0.0f,  //18
        -0.9f, -0.9f, 0.05f,		20.0f, 1.0f,  //22
        -0.9f, 0.9f, 0.05f,         0.0f, 1.0f, //21
        
        //back
        -1.0f, 0.9f, -0.05f,		0.0f, 0.0f, //15
        -1.0f, 0.9f, 0.05f,         0.0f, 1.0f, //19
        -1.0f, -0.9f, -0.05f,		20.0f, 0.0f,  //16
        -1.0f, -0.9f, -0.05f,		20.0f, 0.0f,  //16
        -1.0f, -0.9f, 0.05f,		20.0f, 1.0f,  //20
        -1.0f, 0.9f, 0.05f,         0.0f, 1.0f, //19
        
        
        /*wall down direction*/
        //bottom
        -1.0f, -1.0f, -0.05f,		0.0f, 0.0f,  //23
        0.9f, -1.0f, -0.05f,		20.0f, 0.0f, //24
        0.9f, -0.9f, -0.05f,		20.0f, 1.0f, //25
        0.9f, -0.9f, -0.05f,		20.0f, 1.0f, //25
        -1.0f, -0.9f, -0.05f,		0.0f, 1.0f,  //26
        -1.0f, -1.0f, -0.05f,		0.0f, 0.0f,  //23
        
        //top
        -1.0f, -1.0f, 0.05f,		0.0f, 0.0f,  //27
        0.9f, -1.0f, 0.05f,         20.0f, 0.0f, //28
        0.9f, -0.9f, 0.05f,         20.0f, 1.0f, //29
        0.9f, -0.9f, 0.05f,         20.0f, 1.0f, //29
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //30
        -1.0f, -1.0f, 0.05f,		0.0f, 0.0f,  //27
        
        //side left
        -1.0f, -0.9f, -0.05f,		0.0f, 0.0f,  //26
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //30
        -1.0f, -1.0f, -0.05f,		1.0f, 0.0f,  //23
        -1.0f, -1.0f, -0.05f,		1.0f, 0.0f,  //23
        -1.0f, -1.0f, 0.05f,		1.0f, 1.0f,  //27
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //30
        
        //side right
        0.9f, -1.0f, -0.05f,		0.0f, 0.0f, //24
        0.9f, -0.9f, -0.05f,		1.0f, 0.0f, //25
        0.9f, -0.9f, 0.05f,         1.0f, 1.0f, //29
        0.9f, -1.0f, -0.05f,		0.0f, 0.0f, //24
        0.9f, -1.0f, 0.05f,         0.0f, 1.0f, //28
        0.9f, -0.9f, 0.05f,         1.0f, 1.0f, //29
        
        //front
        -1.0f, -1.0f, -0.05f,		0.0f, 0.0f,  //23
        -1.0f, -1.0f, 0.05f,		0.0f, 1.0f,  //27
        0.9f, -1.0f, -0.05f,		20.0f, 0.0f, //24
        0.9f, -1.0f, -0.05f,		20.0f, 0.0f, //24
        0.9f, -1.0f, 0.05f,         20.0f, 1.0f, //28
        -1.0f, -1.0f, 0.05f,		0.0f, 1.0f,  //27
        
        //back
         -1.0f, -0.9f, -0.05f,		0.0f, 0.0f,  //26
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //30
        0.9f, -0.9f, -0.05f,		20.0f, 0.0f, //25
        0.9f, -0.9f, -0.05f,		20.0f, 0.0f, //25
        0.9f, -0.9f, 0.05f,         20.0f, 1.0f, //29
        -1.0f, -0.9f, 0.05f,		0.0f, 1.0f,  //30
    };
    
    glGenVertexArrays(1, &VertexArrayID);
    
    glGenBuffers(1, &vertexbuffer);
    
    glBindVertexArray(VertexArrayID);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
}

void Wall::draw()
{
	glBindTexture(GL_TEXTURE_2D, wallTexture);
	glBindVertexArray(VertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, 114);
}

GLfloat Wall::getXPos()
{
    return xPos;
}

GLfloat Wall::getYPos()
{
    return yPos;
}
