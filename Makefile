# INSTUCTIONS FOR FIRST TIME USE (ON A COMPUTER YOU HAVEN'T USED BEFORE/FROM A NEW CLONED REPO)
# If you have already used this Makefile before ignore the instructions below. Just use it the normal way.
# 1) Type 'make', it will execute then run into an error. this is normal because the changes have not yet reflected on in the terminal.
# 2) Type 'source ~/.zshrc', this will refresh the terminal.
# 3) Type 'make', it will execute with the new terminal state and there should be no error.

# SOME PROBLEMS YOU MIGHT ENCOUNTER
# * Brew may take forever to install or update. Just press ctrl-c and start the procces again.

# WHERE TO PUT YOUR FILES (IT WON'T WORK IF THE FILES ARE IN THE WRONG PLACE)
# * Source files (*.cpp) must be put in the 'src' folder
# * Header files (*.hpp) must be put in the 'include' folder

NAME = bomberman

CC = clang++
CCFLAGS = #-Wall -Werror -Wextra

SRC_FOLDER = src
INCLUDE_FOLDER = include

SRCDIR = src/
SRCS = main.cpp Graphics.cpp Window.cpp MainMenu.cpp stb_image.cpp loader.cpp\
	  Texture.cpp shader.cpp WindowKeyEvents.cpp Player.cpp controls.cpp\
	  Sound.cpp Wall.cpp Floor.cpp Portal.cpp StaticWall.cpp Destructible.cpp\
	  camera.cpp health.cpp timer.cpp Bomb.cpp GameState.cpp

SRC	= $(addprefix $(SRCDIR), $(SRCS))
INCLUDE = $(wildcard $(INCLUDE_FOLDER)/*.hpp)

BREW_REPO = https://github.com/Tolsadus/42homebrewfix.git
BREW_TMP = .brew
BREW = ${HOME}/.brew

_GLEW_FOLDER = $(BREW)/Cellar/glew
GLEW_FOLDER = $(_GLEW_FOLDER)/$(shell ls -r $(_GLEW_FOLDER) | head -n 1)
GLEW = -L $(GLEW_FOLDER)/lib -lGLEW -I $(GLEW_FOLDER)/include/GL

_GLFW_FOLDER = $(BREW)/Cellar/glfw
GLFW_FOLDER = $(_GLFW_FOLDER)/$(shell ls -r $(_GLFW_FOLDER) | head -n 1)
GLFW = -L $(GLFW_FOLDER)/lib -lglfw -I $(GLFW_FOLDER)/include/GLFW

_BOOST_FOLDER = $(BREW)/Cellar/boost
BOOST_FOLDER = $(_BOOST_FOLDER)/$(shell ls -r $(_BOOST_FOLDER) | head -n 1)
BOOST = -L $(BOOST_FOLDER)/lib -lboost_serialization -I $(BOOST_FOLDER)/include/

_SDL2_FOLDER = $(BREW)/Cellar/sdl2
SDL2_FOLDER = $(_SDL2_FOLDER)/$(shell ls -r $(_SDL2_FOLDER) | head -n 1)
SDL2 = -L $(SDL2_FOLDER)/lib -lSDL2 -I $(SDL2_FOLDER)/include/SDL2

_SDL2_MIXER_FOLDER = $(BREW)/Cellar/sdl2_mixer
SDL2_MIXER_FOLDER = $(_SDL2_MIXER_FOLDER)/$(shell ls -r $(_SDL2_MIXER_FOLDER) | head -n 1)
SDL2_MIXER = -L $(SDL2_MIXER_FOLDER)/lib -lSDL2_mixer -I $(SDL2_MIXER_FOLDER)/include/SDL2

_GLM_FOLDER = $(BREW)/Cellar/glm
GLM_FOLDER = $(_GLM_FOLDER)/$(shell ls -r $(_GLM_FOLDER) | head -n 1)
GLM = -I $(GLM_FOLDER)/include/GLM

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE) $(BREW) $(_BOOST_FOLDER) $(_GLM_FOLDER) $(_GLEW_FOLDER) $(_GLFW_FOLDER) $(_SDL2_FOLDER) $(_SDL2_MIXER_FOLDER)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) -I $(INCLUDE_FOLDER) $(BOOST) $(GLM) $(GLEW) $(GLFW) $(SDL2) $(SDL2_MIXER) -framework OpenGL

$(BREW):
	git clone $(BREW_REPO) $(BREW_TMP)
	sh $(BREW_TMP)/install.sh && rm -rf $(BREW_TMP)

$(_BOOST_FOLDER):
	brew install boost

$(_GLM_FOLDER):
	brew install glm

$(_GLEW_FOLDER):
	brew install glew

$(_GLFW_FOLDER):
	brew install glfw3

$(_SDL2_FOLDER):
	brew install sdl2

$(_SDL2_MIXER_FOLDER):
	brew install sdl2_mixer

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re
