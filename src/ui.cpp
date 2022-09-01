#include "ui.hpp"



char const *keyToStr(KeyboardKey key);

auto const drawText = [](auto text, int x, int y) {
    DrawText(text, x, y, Conf::fontSize, Conf::foreground);
};

void Ui::onDraw() const {
    m_vertical = 11;
    printFps();
    printStepCount();
    printStepsPerSecond();
    printControls();
}

void Ui::printFps() const {
    drawText(TextFormat("Fps: %d", GetFPS()), xPos(), yPos());
}

void Ui::printStepCount() const {
    drawText(TextFormat("Step: %d", totalSteps), xPos(), yPos());
}

void Ui::printStepsPerSecond() const {
    drawText(TextFormat("Steps per second: %d", GetFPS() * stepsPerFrame), xPos(), yPos());
}

void Ui::printControls() const {
    m_vertical--;
    auto const shY = [&] {
        return Conf::screenHeight - Conf::fontSize * m_vertical--;
    };

    auto const descX = Conf::screenWidth - (Conf::fontSize * Conf::uiRigthPad) + Conf::uiControlsPad;
    auto const descY = [&] {
        return Conf::screenHeight - Conf::fontSize * (m_vertical + 1);
    };

    drawText("LMB", xPos(), shY());
    drawText("Pan", descX, descY());

    drawText("Wheel", xPos(), shY());
    drawText("Zoom", descX, descY());

    drawText(keyToStr(Conf::stepKey), xPos(), shY());
    drawText("Next step", descX, descY());

    drawText(keyToStr(Conf::resetKey), xPos(), shY());
    drawText("Reset", descX, descY());

    drawText(keyToStr(Conf::playPauseKey), xPos(), shY());
    drawText("Play/Pause", descX, descY());

    drawText("1-9", xPos(), shY());
    drawText("Speed", descX, descY());
}

#define KTS(KEY) \
    case KEY_##KEY: return #KEY

char const *keyToStr(KeyboardKey key) {
    // clang-format off
    switch (key) {
        KTS(NULL); KTS(APOSTROPHE); KTS(COMMA); KTS(MINUS); KTS(PERIOD); KTS(SLASH); KTS(ZERO); KTS(ONE); KTS(TWO);
        KTS(THREE); KTS(FOUR); KTS(FIVE); KTS(SIX); KTS(SEVEN); KTS(EIGHT); KTS(NINE); KTS(SEMICOLON); KTS(EQUAL);
        KTS(A); KTS(B); KTS(C); KTS(D); KTS(E); KTS(F); KTS(G); KTS(H); KTS(I); KTS(J); KTS(K); KTS(L); KTS(M); KTS(N);
        KTS(O); KTS(P); KTS(Q); KTS(R); KTS(S); KTS(T); KTS(U); KTS(V); KTS(W); KTS(X); KTS(Y); KTS(Z);
        KTS(LEFT_BRACKET); KTS(BACKSLASH); KTS(RIGHT_BRACKET); KTS(GRAVE); KTS(SPACE); KTS(ESCAPE); KTS(ENTER);
        KTS(TAB); KTS(BACKSPACE); KTS(INSERT); KTS(DELETE); KTS(RIGHT); KTS(LEFT); KTS(DOWN); KTS(UP); KTS(PAGE_UP);
        KTS(PAGE_DOWN); KTS(HOME); KTS(END); KTS(CAPS_LOCK); KTS(SCROLL_LOCK); KTS(NUM_LOCK); KTS(PRINT_SCREEN);
        KTS(PAUSE); KTS(F1); KTS(F2); KTS(F3); KTS(F4); KTS(F5); KTS(F6); KTS(F7); KTS(F8); KTS(F9); KTS(F10); KTS(F11);
        KTS(F12); KTS(LEFT_SHIFT); KTS(LEFT_CONTROL); KTS(LEFT_ALT); KTS(LEFT_SUPER); KTS(RIGHT_SHIFT);
        KTS(RIGHT_CONTROL); KTS(RIGHT_ALT); KTS(RIGHT_SUPER); KTS(KB_MENU); KTS(KP_0); KTS(KP_1); KTS(KP_2); KTS(KP_3);
        KTS(KP_4); KTS(KP_5); KTS(KP_6); KTS(KP_7); KTS(KP_8); KTS(KP_9); KTS(KP_DECIMAL); KTS(KP_DIVIDE);
        KTS(KP_MULTIPLY); KTS(KP_SUBTRACT); KTS(KP_ADD); KTS(KP_ENTER); KTS(KP_EQUAL);

        default: return "Unknown key";
    }
    // clang-format on
}
