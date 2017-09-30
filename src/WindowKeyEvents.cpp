#include "Sound.hpp"
#include "WindowKeyEvents.hpp"

int current_screen = MENU_SCREEN;

WindowKeyEvents::WindowKeyEvents(){
}

WindowKeyEvents::~WindowKeyEvents(){
}

/**********************************
** loads/ plays effects onKeyEvents
***********************************/
void WindowKeyEvents::soundKeyEvents(GLFWwindow *win, Sound *s, Graphics *g)
{
    switch(g->getDrawMode())
    {
        case GAMEPLAY:
            if (glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS && current_screen != PLAY_SCREEN)
            {
                current_screen = PLAY_SCREEN;
                s->stopMusic(2000);
                s->playEffectOnce(EFFECT_ENTER, ENTER_CHANNEL);
            }
            if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS   || glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS ||
                glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS )
            {
                if (!Mix_Playing(WALK_CHANNEL))
                    ;//s->playEffectOnce(EFFECT_WALK, WALK_CHANNEL);
            }
            if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_RELEASE   && glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_RELEASE &&
                glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_RELEASE && glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_RELEASE )
                s->stopEffect(WALK_CHANNEL);
            break;
        case PAUSE:
        case SCREEN:
        case MAINMENU:
        case SETTINGS:
            if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS   || glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                if (!Mix_Playing(SCROLL_CHANNEL))
                    s->playEffectOnce(EFFECT_SCROLL, SCROLL_CHANNEL);
            }
            break;
        case GAMEPAUSE:;;
            break;
        default:
            break;
    }
}

/**************************************************
** wrappers function: handles all key events,
** by calling specific key events function handlers
***************************************************/
void WindowKeyEvents::keyEventsWrapper(GLFWwindow *win, Sound *s, Graphics *g)
{
    this->soundKeyEvents(win, s, g);
}
