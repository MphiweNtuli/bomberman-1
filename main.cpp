// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
//#include <GL/glew.h>

// Include GLFW
//#include <GLFW/glfw3.h>

#include "Texture.hpp"
#include "common/shader.hpp"
#include "Graphics.hpp"
#include "Window.hpp"

GLFWwindow* window;

int main(void)
{
	Window myWindow;

	myWindow.runGame();
	window = myWindow.getWindow();
	// Initialise GLFW
	/*if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(800, 600, "Bomberman", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);*/

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	//glClearColor(0.0f, 0.3f, 0.0f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	Texture texture("crate3.jpeg");

	static const GLfloat g_vertex_buffer_data[] = {
		//vertex data			//texture coordinates 
		-1.0f, 0.9f, 0.0f,		0.0f, 0.0f,
		1.0f, 0.9f, 0.0f,		20.0f, 0.0f,
		1.0f,  1.0f, 0.0f,		20.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,		0.0f, 1.0f,

		0.9f, -1.0f, 0.0f,		0.0f, 1.0f,
		1.0f,  -1.0f, 0.0f,		0.0f, 0.0f,
		0.9f, 0.9f, 0.0f,		20.0f, 1.0f,

		-1.0f, -1.0f, 0.0f,		20.0f, 1.0f,
		0.9f, -0.9f, 0.0f,		0.0f, 0.0f,
		-1.0f, -0.9f, 0.0f,		20.0f, 0.0f,

		-0.9f, -0.9f, 0.0f,		20.0f, 1.0f,
		-0.9f, 0.9f, 0.0f,		0.0f, 1.0f
	};

	GLuint elements[] = {
		0, 1, 2,
		0, 3, 2,
		4, 5, 6,
		5, 1, 6,
		7, 4, 8,
		7, 9, 8,
		9, 10, 11,
		9, 0, 11

	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//trin declare and init
	GLuint VAOs[96], VBOs[96];//, EBOs[97];
	unsigned int EBOs[96];
	Graphics g(vertexbuffer, VAOs);

	g.initGlArrays(VBOs, VAOs, EBOs);
	myWindow.setGraphics(g);

	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		//bind texture
		texture.Bind(0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			5 * sizeof(GL_FLOAT),                  // stride
			(void*)0            // array buffer offset
		);



		// Draw the triangle !
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0); // 3 indices starting at 0 -> 1 triangle

															  //trin logic
		for (int i = 0; i < 96; i++) {
			glBindVertexArray(VAOs[i]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 3 indices starting at 0 -> 1 triangle
		}
		//g.drawElements();

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
