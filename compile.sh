export SRC="main.cpp Graphics.cpp Window.cpp MainMenu.cpp stb_image.c Texture.cpp common/shader.cpp"

g++ $SRC -o bomberman -I glfw/include/ -I glew/include -L glfw/lib -L glew/lib -lglfw -lGLEW \
	-framework OpenGL