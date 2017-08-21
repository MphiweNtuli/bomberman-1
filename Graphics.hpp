/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 14:44:19 by tditshwe          #+#    #+#             */
/*   Updated: 2017/08/16 14:44:21 by tditshwe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Graphics
{
public:
	Graphics(GLuint VBO, GLuint VAOs[]);

	void initGlArrays(GLuint VBOs[], GLuint VAOs[], GLuint EBOs[]);
	void initPlayerVertices(G)
	void drawElements();

	void setInt(int i);
	int getInt();

private:
	GLuint VertexArrayID;
	GLuint VAOs[96];
	int testIn;
};

#endif
