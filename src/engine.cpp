#include "engine.hpp"

Engine::Engine(WinConf win, int fps)
        : m_cam {Vector2Zero(), Vector2Zero(), 0.f, 1.f}
        , m_win {win}
        , m_windowedState {win}
        , m_fps {fps}
        , m_useUI {false} {
    InitWindow(win.width, win.height, win.title);
    SetTargetFPS(fps);
    if (Conf::initFullScreen != IsWindowFullscreen()) ToggleFullscreen();
    recalculateScreen();
}

Engine::~Engine() {
    CloseWindow();  // Close window and OpenGL context
}

void Engine::frameStart() {
    BeginDrawing();
    BeginMode2D(m_cam);


    fullScreenToggle();
    mousePan();
    mouseZoom();
}

void Engine::uiStart() {
    EndMode2D();
    m_useUI = true;
}

void Engine::frameEnd() {
    if (!m_useUI) EndMode2D();

    m_useUI = false;
    EndDrawing();
}

void Engine::mousePan() {
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return;

    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / m_cam.zoom);
    m_cam.target = Vector2Add(m_cam.target, delta);
}

void Engine::mouseZoom() {
    float wheel = GetMouseWheelMove();
    if (wheel == 0) return;

    m_cam.target = GetScreenToWorld2D(GetMousePosition(), m_cam);
    m_cam.offset = GetMousePosition();

    float const zoomIncrement = m_cam.zoom * Conf::zoomRatio;

    m_cam.zoom += wheel * zoomIncrement;
    if (m_cam.zoom < zoomIncrement) m_cam.zoom = zoomIncrement;
}

#include <fmt/printf.h>

void Engine::fullScreenToggle() {
    if (!IsKeyPressed(Conf::fullscreenKey)) return;

    fmt::printf(
        R"(%s: m_windowedState = {
     width = %d;
     height = %d;
     fullScreen = %d;
    }
     ScreenWidth = %d;
     ScreenHeight = %d;

     MonitorWidth = %d;
     MonitorHeight = %d;
    )",
        __func__,
        m_windowedState.width,
        m_windowedState.height,
        m_windowedState.fullScreen,
        GetScreenWidth(),
        GetScreenHeight(),
        GetMonitorWidth(GetCurrentMonitor()),
        GetMonitorHeight(GetCurrentMonitor()));

    if (m_windowedState.fullScreen) {
        //SetWindowSize(m_windowedState.width, m_windowedState.height);
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
        fmt::print("going out of full screen\n");
    } else {
        m_windowedState.width = GetScreenWidth();
        m_windowedState.height = GetScreenHeight();
        SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
        fmt::print("going into full screen\n");
    }


    m_windowedState.fullScreen = !m_windowedState.fullScreen;
    recalculateScreen();
    ToggleFullscreen();
}
