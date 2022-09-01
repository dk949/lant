#include "config.hpp"
#include "engine.hpp"
#include "grid.hpp"
#include "ui.hpp"

#include <raylib.h>

enum struct Mode { Auto, Manual };

int main() {
    SetTraceLogLevel(TraceLogLevel::LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    Engine e {
        {
         .width = Conf::screenWidth,
         .height = Conf::screenHeight,
         .title = Conf::title,
         .fullScreen = Conf::initFullScreen,
         }
    };
    Ui ui;

    Grid g;
    Mode m;
    int stepsPerFrame;
    auto const reset = [&] {
        g.reset();
        m = Mode::Manual;
        stepsPerFrame = 1;
    };
    reset();
    while (!WindowShouldClose()) {
        if (IsWindowResized()) recalculateScreen();
        e.frameStart();
        ClearBackground(BEIGE);

        if (IsKeyPressed(Conf::resetKey)) reset();
        if (IsKeyPressed(Conf::playPauseKey)) m = (m == Mode::Manual) ? Mode::Auto : Mode::Manual;


        if (IsKeyPressed(KEY_ONE)) stepsPerFrame = 1;
        if (IsKeyPressed(KEY_TWO)) stepsPerFrame = 2;
        if (IsKeyPressed(KEY_THREE)) stepsPerFrame = 3;
        if (IsKeyPressed(KEY_THREE)) stepsPerFrame = 3;
        if (IsKeyPressed(KEY_FOUR)) stepsPerFrame = 4;
        if (IsKeyPressed(KEY_FIVE)) stepsPerFrame = 5;
        if (IsKeyPressed(KEY_SIX)) stepsPerFrame = 6;
        if (IsKeyPressed(KEY_SEVEN)) stepsPerFrame = 7;
        if (IsKeyPressed(KEY_EIGHT)) stepsPerFrame = 8;
        if (IsKeyPressed(KEY_NINE)) stepsPerFrame = 9;

        switch (m) {
            case Mode::Auto:
                for (int i = 0; i <= stepsPerFrame; i++)
                    g.step();
                if (!stepsPerFrame) stepsPerFrame = 1;
                break;
            case Mode::Manual:
                stepsPerFrame = 0;
                if (IsKeyPressed(Conf::stepKey)) g.step();
                break;
        }

        g.onDraw();

        e.uiStart();

        ui.stepsPerFrame = stepsPerFrame;
        ui.totalSteps = g.steps();
        ui.onDraw();

        e.frameEnd();
    }
    return 0;
}
