#ifndef WINDOW_KEY_EVENTS_HPP
#define WINDOW_KEY_EVENTS_HPP

#define MENU_SCREEN 0
#define PLAY_SCREEN 1

# include "Sound.hpp"
#include "Graphics.hpp"


class WindowKeyEvents {
    public:
        WindowKeyEvents();
        ~WindowKeyEvents();
        void windowKeyEvents(GLFWwindow *win);
        void soundKeyEvents(GLFWwindow *win, Sound *sound, Graphics *g);
        void keyEventsWrapper(GLFWwindow *win, Sound *s, Graphics *g);
};

#endif