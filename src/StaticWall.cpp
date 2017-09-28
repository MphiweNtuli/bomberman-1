/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticWall.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:28:53 by tditshwe          #+#    #+#             */
/*   Updated: 2017/09/11 16:27:00 by rmoswela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StaticWall.hpp"

StaticWall::StaticWall()
{
    //glDeleteBuffers(1, &VBO);
}

StaticWall::~StaticWall()
{
    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);*/
}

void StaticWall::init()
{
    Texture texture("brick2.jpg", &wallTexture);
    
    GLfloat vertices[STATIC_WALLS][180];
    GLfloat xLeft = -0.8f;
    GLfloat xRight = -0.7f;
    GLfloat fUnit = 0.2;
    
    int k = 0;
    for (int j = 0; j < 8; j++)
    {
        
        for (int i = 0; i < 8; i++)
        {
            /*bottom side*/
            
            //Bottom left 0
            vertices[k][0] = xLeft + i * fUnit;
            vertices[k][1] = 0.6f - j * fUnit;
            vertices[k][2] = -0.05f;
            //texture coordinates
            vertices[k][3] = 0.0f;
            vertices[k][4] = 0.0f;
            //Bottom right 1
            vertices[k][5] = xRight + i * fUnit;
            vertices[k][6] = 0.6f - j * fUnit;
            vertices[k][7] = -0.05f;
            //texture coordinates
            vertices[k][8] = 1.0f;
            vertices[k][9] = 0.0f;
            //Top right 3
            vertices[k][10] = xRight + i * fUnit;
            vertices[k][11] = 0.7f - j * fUnit;
            vertices[k][12] = -0.05f;
            //texture coordinates
            vertices[k][13] = 1.0f;
            vertices[k][14] = 1.0f;
            //Top right 3
            vertices[k][15] = xRight + i * fUnit;
            vertices[k][16] = 0.7f - j * fUnit;
            vertices[k][17] = -0.05f;
            //texture coordinates
            vertices[k][18] = 1.0f;
            vertices[k][19] = 1.0f;
            //Top left 2
            vertices[k][20] = xLeft + i * fUnit;
            vertices[k][21] = 0.7f - j * fUnit;
            vertices[k][22] = -0.05f;
            //texture coordinates
            vertices[k][23] = 0.0f;
            vertices[k][24] = 1.0f;
            //Bottom left 0
            vertices[k][25] = xLeft + i * fUnit;
            vertices[k][26] = 0.6f - j * fUnit;
            vertices[k][27] = -0.05f;
            //texture coordinates
            vertices[k][28] = 0.0f;
            vertices[k][29] = 0.0f;
            
            
            /*top side*/
            
            //Bottom left 4
            vertices[k][30] = xLeft + i * fUnit;
            vertices[k][31] = 0.6f - j * fUnit;
            vertices[k][32] = 0.05f;
            //texture coordinates
            vertices[k][33] = 0.0f;
            vertices[k][34] = 0.0f;
            //Bottom right 5
            vertices[k][35] = xRight + i * fUnit;
            vertices[k][36] = 0.6f - j * fUnit;
            vertices[k][37] = 0.05f;
            //texture coordinates
            vertices[k][38] = 1.0f;
            vertices[k][39] = 0.0f;
            //Top left 7
            vertices[k][40] = xRight + i * fUnit;
            vertices[k][41] = 0.7f - j * fUnit;
            vertices[k][42] = 0.05f;
            //texture coordinates
            vertices[k][43] = 1.0f;
            vertices[k][44] = 1.0f;
            //Top left 7
            vertices[k][45] = xRight + i * fUnit;
            vertices[k][46] = 0.7f - j * fUnit;
            vertices[k][47] = 0.05f;
            //texture coordinates
            vertices[k][48] = 1.0f;
            vertices[k][49] = 1.0f;
            //Top right 6
            vertices[k][50] = xLeft + i * fUnit;
            vertices[k][51] = 0.7f - j * fUnit;
            vertices[k][52] = 0.05f;
            //texture coordinates
            vertices[k][53] = 0.0f;
            vertices[k][54] = 1.0f;
            //Bottom left 4
            vertices[k][55] = xLeft + i * fUnit;
            vertices[k][56] = 0.6f - j * fUnit;
            vertices[k][57] = 0.05f;
            //texture coordinates
            vertices[k][58] = 0.0f;
            vertices[k][59] = 0.0f;
            
            /*front side*/
            
            //Bottom left 0
            vertices[k][60] = xLeft + i * fUnit;
            vertices[k][61] = 0.6f - j * fUnit;
            vertices[k][62] = -0.05f;
            //texture coordinates
            vertices[k][63] = 0.0f;
            vertices[k][64] = 0.0f;
            //Bottom right 1
            vertices[k][65] = xRight + i * fUnit;
            vertices[k][66] = 0.6f - j * fUnit;
            vertices[k][67] = -0.05f;
            //texture coordinates
            vertices[k][68] = 1.0f;
            vertices[k][69] = 0.0f;
            //Bottom right 5
            vertices[k][70] = xRight + i * fUnit;
            vertices[k][71] = 0.6f - j * fUnit;
            vertices[k][72] = 0.05f;
            //texture coordinates
            vertices[k][73] = 1.0f;
            vertices[k][74] = 1.0f;
            //Bottom right 5
            vertices[k][75] = xRight + i * fUnit;
            vertices[k][76] = 0.6f - j * fUnit;
            vertices[k][77] = 0.05f;
            //texture coordinates
            vertices[k][78] = 1.0f;
            vertices[k][79] = 1.0f;
            //Bottom left 4
            vertices[k][80] = xLeft + i * fUnit;
            vertices[k][81] = 0.6f - j * fUnit;
            vertices[k][82] = 0.05f;
            //texture coordinates
            vertices[k][83] = 0.0f;
            vertices[k][84] = 1.0f;
            //Bottom left 0
            vertices[k][85] = xLeft + i * fUnit;
            vertices[k][86] = 0.6f - j * fUnit;
            vertices[k][87] = -0.05f;
            //texture coordinates
            vertices[k][88] = 0.0f;
            vertices[k][89] = 0.0f;
            
            /*right side*/
            
            //Bottom right 1
            vertices[k][90] = xRight + i * fUnit;
            vertices[k][91] = 0.6f - j * fUnit;
            vertices[k][92] = -0.05f;
            //texture coordinates
            vertices[k][93] = 0.0f;
            vertices[k][94] = 0.0f;
            //Top right 3
            vertices[k][95] = xRight + i * fUnit;
            vertices[k][96] = 0.7f - j * fUnit;
            vertices[k][97] = -0.05f;
            //texture coordinates
            vertices[k][98] = 1.0f;
            vertices[k][99] = 0.0f;
            //Top left 7
            vertices[k][100] = xRight + i * fUnit;
            vertices[k][101] = 0.7f - j * fUnit;
            vertices[k][102] = 0.05f;
            //texture coordinates
            vertices[k][103] = 1.0f;
            vertices[k][104] = 1.0f;
            //Top left 7
            vertices[k][105] = xRight + i * fUnit;
            vertices[k][106] = 0.7f - j * fUnit;
            vertices[k][107] = 0.05f;
            //texture coordinates
            vertices[k][108] = 1.0f;
            vertices[k][109] = 1.0f;
            //Bottom right 5
            vertices[k][110] = xRight + i * fUnit;
            vertices[k][111] = 0.6f - j * fUnit;
            vertices[k][112] = 0.05f;
            //texture coordinates
            vertices[k][113] = 0.0f;
            vertices[k][114] = 1.0f;
            //Bottom right 1
            vertices[k][115] = xRight + i * fUnit;
            vertices[k][116] = 0.6f - j * fUnit;
            vertices[k][117] = -0.05f;
            //texture coordinates
            vertices[k][118] = 0.0f;
            vertices[k][119] = 0.0f;

            /*left side view*/
            
            //Bottom left 0
            vertices[k][120] = xLeft + i * fUnit;
            vertices[k][121] = 0.6f - j * fUnit;
            vertices[k][122] = -0.05f;
            //texture coordinates
            vertices[k][123] = 0.0f;
            vertices[k][124] = 0.0f;
            //Top left 2
            vertices[k][125] = xLeft + i * fUnit;
            vertices[k][126] = 0.7f - j * fUnit;
            vertices[k][127] = -0.05f;
            //texture coordinates
            vertices[k][128] = 1.0f;
            vertices[k][129] = 0.0f;
            //Top right 6
            vertices[k][130] = xLeft + i * fUnit;
            vertices[k][131] = 0.7f - j * fUnit;
            vertices[k][132] = 0.05f;
            //texture coordinates
            vertices[k][133] = 1.0f;
            vertices[k][134] = 1.0f;
            //Top right 6
            vertices[k][135] = xLeft + i * fUnit;
            vertices[k][136] = 0.7f - j * fUnit;
            vertices[k][137] = 0.05f;
            //texture coordinates
            vertices[k][138] = 1.0f;
            vertices[k][139] = 1.0f;
            //Bottom left 4
            vertices[k][140] = xLeft + i * fUnit;
            vertices[k][141] = 0.6f - j * fUnit;
            vertices[k][142] = 0.05f;
            //texture coordinates
            vertices[k][143] = 0.0f;
            vertices[k][144] = 1.0f;
            //Bottom left 0
            vertices[k][145] = xLeft + i * fUnit;
            vertices[k][146] = 0.6f - j * fUnit;
            vertices[k][147] = -0.05f;
            //texture coordinates
            vertices[k][148] = 0.0f;
            vertices[k][149] = 0.0f;
            
            
            /*back view*/
            
            //Top left 2
            vertices[k][150] = xLeft + i * fUnit;
            vertices[k][151] = 0.7f - j * fUnit;
            vertices[k][152] = -0.05f;
            //texture coordinates
            vertices[k][153] = 0.0f;
            vertices[k][154] = 0.0f;
            //Top right 3
            vertices[k][155] = xRight + i * fUnit;
            vertices[k][156] = 0.7f - j * fUnit;
            vertices[k][157] = -0.05f;
            //texture coordinates
            vertices[k][158] = 1.0f;
            vertices[k][159] = 0.0f;
            //Top left 7
            vertices[k][160] = xRight + i * fUnit;
            vertices[k][161] = 0.7f - j * fUnit;
            vertices[k][162] = 0.05f;
            //texture coordinates
            vertices[k][163] = 1.0f;
            vertices[k][164] = 1.0f;
            //Top left 7
            vertices[k][165] = xRight + i * fUnit;
            vertices[k][166] = 0.7f - j * fUnit;
            vertices[k][167] = 0.05f;
            //texture coordinates
            vertices[k][168] = 1.0f;
            vertices[k][169] = 1.0f;
            //Top right 6
            vertices[k][170] = xLeft + i * fUnit;
            vertices[k][171] = 0.7f - j * fUnit;
            vertices[k][172] = 0.05f;
            //texture coordinates
            vertices[k][173] = 0.0f;
            vertices[k][174] = 1.0f;
            //Top left 2
            vertices[k][175] = xLeft + i * fUnit;
            vertices[k][176] = 0.7f - j * fUnit;
            vertices[k][177] = -0.05f;
            //texture coordinates
            vertices[k][178] = 0.0f;
            vertices[k][179] = 0.0f;

            
            
            glGenVertexArrays(1, &VAOs[k]);
        
            glGenBuffers(1, &VBOs[k]);
            
            glBindVertexArray(VAOs[k]);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[k]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[k]), vertices[k], GL_STATIC_DRAW);
            
            //position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            Wall wall(xLeft + i * fUnit, 0.7f - j * fUnit, false);
            walls.push_back(wall);
            k++;
        }
    }
    
}

std::list<Wall>     StaticWall::getWalls() const
{
    return walls;
}

void StaticWall::draw()
{
    for (int i = 0; i < STATIC_WALLS; i++)
    {
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glBindVertexArray(VAOs[i]);
        glDrawArrays(GL_TRIANGLES, 0, 180);
    }
}
