#ifndef UI_HPP
#define UI_HPP


#include "config.hpp"

#include <cstddef>

class Ui {
public:
    int stepsPerFrame;
    size_t totalSteps;


public:
    void onDraw() const;

private:
    void printFps() const;
    void printStepCount() const;
    void printStepsPerSecond() const;
    void printControls() const;


private:
    // Drawing helpers
    mutable int m_vertical;

    int xPos() const {
        return Conf::screenWidth - (Conf::fontSize * Conf::uiRigthPad);
    }

    int yPos() const {
        return Conf::screenHeight - Conf::fontSize * m_vertical--;
    }
};

#endif  // UI_HPP
