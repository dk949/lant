#include "grid.hpp"

// Ant

Vector2 fromAny(auto a, auto b) {
    return Vector2 {static_cast<float>(a), static_cast<float>(b)};
}

void Ant::onDraw() const {
    auto const realX = (x * Conf::cellSize) + Conf::cellSize / 2;
    auto const realY = (y * Conf::cellSize) + Conf::cellSize / 2;
    DrawCircle(realX, realY, static_cast<float>(Conf::antRad), Conf::antColor);

    auto const cor = Conf::antLine / 3;  // Correction factor. So lines look like an arrow
    auto const floatLine = static_cast<float>(Conf::antLine);
    switch (facing) {
        case Cardinal::North:
            DrawLineEx(fromAny(realX + cor, realY - Conf::antRad),
                fromAny(realX - Conf::antRad + cor, realY),
                floatLine,
                Conf::antLineCol);
            DrawLineEx(fromAny(realX - cor, realY - Conf::antRad),
                fromAny(realX + Conf::antRad - cor, realY),
                floatLine,
                Conf::antLineCol);
            break;
        case Cardinal::East:
            DrawLineEx(fromAny(realX + Conf::antRad, realY + cor),
                fromAny(realX, realY - Conf::antRad + cor),
                floatLine,
                Conf::antLineCol);
            DrawLineEx(fromAny(realX + Conf::antRad, realY - cor),
                fromAny(realX, realY + Conf::antRad - cor),
                floatLine,
                Conf::antLineCol);
            break;
        case Cardinal::South:
            DrawLineEx(fromAny(realX + cor, realY + Conf::antRad),
                fromAny(realX - Conf::antRad + cor, realY),
                floatLine,
                Conf::antLineCol);
            DrawLineEx(fromAny(realX - cor, realY + Conf::antRad),
                fromAny(realX + Conf::antRad - cor, realY),
                floatLine,
                Conf::antLineCol);
            break;
        case Cardinal::West:
            DrawLineEx(fromAny(realX - Conf::antRad, realY + cor),
                fromAny(realX, realY - Conf::antRad + cor),
                floatLine,
                Conf::antLineCol);
            DrawLineEx(fromAny(realX - Conf::antRad, realY - cor),
                fromAny(realX, realY + Conf::antRad - cor),
                floatLine,
                Conf::antLineCol);
            break;
    }
}

void Ant::turn(Dir dir) {
    switch (dir) {
        case Dir::Left:
            switch (facing) {
                case Cardinal::North: facing = Cardinal::East; break;
                case Cardinal::East: facing = Cardinal::South; break;
                case Cardinal::South: facing = Cardinal::West; break;
                case Cardinal::West: facing = Cardinal::North; break;
            }
            break;
        case Dir::Right:
            switch (facing) {
                case Cardinal::North: facing = Cardinal::West; break;
                case Cardinal::East: facing = Cardinal::North; break;
                case Cardinal::South: facing = Cardinal::East; break;
                case Cardinal::West: facing = Cardinal::South; break;
            }
            break;
    }
}

// Square

void Square::onDraw() const {
    auto const realX = x * Conf::cellSize;
    auto const realY = y * Conf::cellSize;
    DrawRectangle(realX, realY, Conf::cellSize, Conf::cellSize, Conf::borderColor);
    DrawRectangle(realX + Conf::border,
        realY + Conf::border,
        Conf::cellSize - Conf::border * 2,
        Conf::cellSize - Conf::border * 2,
        (color == Col::White) ? WHITE : BLACK);
}

void Square::flip() {
    color = (color == Col::White) ? Col::Black : Col::White;
}

// Grid


void Grid::step() {
    using enum Cardinal;
    /* From https://en.wikipedia.org/wiki/Langton%27s_ant

    Rules:
    Squares on a plane are colored variously either black or white. We arbitrarily identify one square as the "ant".
    The ant can travel in any of the four cardinal directions at each step it takes. The "ant" moves according to
    the rules below:

        At a white square, turn 90° clockwise, flip the color of the square, move forward one unit
        At a black square, turn 90° counter-clockwise, flip the color of the square, move forward one unit
    */
    auto it = squares.find(Square {.x = ant.x, .y = ant.y});
    if (it == squares.end()) {
        TraceLog(LOG_ERROR, "Tired to load a non existent grid cell (%d;%d)", ant.x, ant.y);
        return;
    }
    auto node = squares.extract(it);
    switch (node.value().color) {
        case Col::White:
            node.value().color = Col::Black;
            ant.turn(Dir::Right);
            break;
        case Col::Black:
            node.value().color = Col::White;
            ant.turn(Dir::Left);
            break;
    }
    squares.insert(std::move(node));
    switch (ant.facing) {
        case North: ant.y--; break;
        case East: ant.x++; break;
        case South: ant.y++; break;
        case West: ant.x--; break;
    }
    squares.insert(Square {ant.x, ant.y});
    m_steps++;
}

void Grid::onDraw() const {
    for (auto const &s : squares) {
        s.onDraw();
    }
    ant.onDraw();
}

void Grid::reset() {
    squares = {
        {0, 0}
    };
    ant = Ant {.x = 0, .y = 0};
    m_steps = 0;
}
