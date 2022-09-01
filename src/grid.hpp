#ifndef GRID_HPP
#define GRID_HPP

#include "config.hpp"

#include <fmt/format.h>
#include <raylib.h>
#include <unordered_set>

#include <algorithm>
#include <vector>

enum struct Dir { Left, Right };
enum struct Cardinal { North, East, South, West };
enum struct Col { Black, White };

struct Ant {
public:
    int x;
    int y;
    Cardinal facing = Cardinal::North;

public:
    void onDraw() const;
    void turn(Dir dir);
};

struct Square {
public:
    int x = 0;
    int y = 0;
    Col color = Col::White;

public:
    void onDraw() const;
    void flip();
};

template<>
struct std::hash<Square> {
    std::size_t operator()(Square s) const noexcept {
        return std::hash<decltype(Square::x)> {}(s.x) ^ (std::hash<decltype(Square::y)> {}(s.y) << 1);
    }
};

template<>
struct std::equal_to<Square> {
    bool operator()(Square lhs, Square rhs) const noexcept {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

struct Grid {
public:
    std::unordered_set<Square> squares;
    Ant ant;

private:
    size_t m_steps;

public:
    void step();
    void onDraw() const;
    void reset();

    [[nodiscard]] inline size_t steps() const {
        return m_steps;
    }
};

#endif  // GRID_HPP
