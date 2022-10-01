#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <raylib.h>

#include <algorithm>
#define AS_IF(T) std::remove_cvref_t<decltype(T)>

// General


struct Conf {
public:
    static constexpr auto defaultTargetFps = 60;
    static constexpr auto zoomRatio = 0.1f;
    static constexpr auto background = BEIGE;
    static constexpr auto foreground = LIME;
    static constexpr auto uiRigthPad = 15;
    static constexpr char const *title = "Lant";

    static inline int screenWidth = 3840;
    static inline int screenHeight = 2160;
    static inline bool initFullScreen = false;
    static inline int screenSize;
    static inline int fontSize = 30;
    static inline int uiControlsPad = 200;

public:  // Controls
    static constexpr auto resetKey = KEY_R;
    static constexpr auto playPauseKey = KEY_SPACE;
    static constexpr auto fullscreenKey = KEY_F;
    static constexpr auto stepKey = KEY_ENTER;

public:  // Grid
    static constexpr auto borderColor = PURPLE;

    static inline int cellSize = 100;
    static inline int border = 8;
    static inline int gridXSize;
    static inline int gridYSize;

public:  // Ant
    static constexpr auto antColor = MAGENTA;
    static constexpr auto antLineCol = GREEN;
    static constexpr int antLine = 6;

    static constexpr int antRad = 16;
};

inline void recalculateScreen() {
    Conf::screenWidth = GetScreenWidth();
    Conf::screenHeight = GetScreenHeight();

    Conf::screenSize = Conf::screenWidth * Conf::screenHeight;
    Conf::gridXSize = Conf::screenWidth / Conf::cellSize;
    Conf::gridYSize = Conf::screenHeight / Conf::cellSize;
}

#endif  // CONFIG_HPP
