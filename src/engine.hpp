#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "config.hpp"

#include <raylib.h>
#include <raymath.h>

struct WinConf {
public:
    int width;
    int height;
    char const *title;
    bool fullScreen;
};

class Engine {
private:
    Camera2D m_cam;
    WinConf m_win;
    WinConf m_windowedState;
    int m_fps;
    bool m_useUI;

public:
    Engine(WinConf win, int fps = Conf::defaultTargetFps);
    ~Engine();

    void frameStart();
    void uiStart();
    void frameEnd();

private:
    void mousePan();
    void mouseZoom();
    void fullScreenToggle();
};

#endif  // WINDOW_HPP
