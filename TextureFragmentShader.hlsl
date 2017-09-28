#version 330 core

// Ouput data
out vec4 color;
in vec2 tex;

// texture sampler
uniform sampler2D texture1;

void main()
{
	// Output color = yellow 
	color = texture(texture1, tex);
}
