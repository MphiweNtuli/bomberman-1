#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include <vector>
#include <cstring>

// #include <GL/glew.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// // using namespace glm;

// #include "shader.hpp"
// #include "texture.hpp"
#include "Bomberman.hpp"

class Text
{
	public:
		// Text(const char * texturePath);
		Text();
		~Text();

		void loadText(const char * text, int x, int y, int size);

	private:
		unsigned int Text2DTextureID;
		unsigned int Text2DVertexBufferID;
		unsigned int Text2DUVBufferID;
		unsigned int Text2DShaderID;
		unsigned int Text2DUniformID;
		GLuint	textId;
};





#endif 