#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <map>

#define BOARD_SIZE 81
#define BOARD_SIDE_LENGTH 9
#define FENCE_COUNT 10

static const std::map<char, uint8_t> cols = {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9},};

struct Position {
    uint8_t row;
    uint8_t col;

    Position() = default;
    Position(uint8_t r, uint8_t c) : row(r), col(c) {}

    friend bool operator==(const Position lhs, const Position rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; }
    friend bool operator!=(const Position lhs, const Position rhs) { return !(lhs==rhs); }

    std::string getNotation() const;
};

class Board {
public:
    static const uint8_t board_size = BOARD_SIZE;

    Board();
    explicit Board(std::istream& is);

    void addFence(Position fence, bool horizontal);

    const std::vector<std::vector<uint8_t>>& getGraph() const { return graph; }

    void setP1(Position pos) { p1 = pos; }
    void setP2(Position pos) { p2 = pos; }
    Position getP1() const { return p1; }
    Position getP2() const { return p2; }

    const std::vector<Position>& getHorizontalFences() const { return horizontalFences; }
    const std::vector<Position>& getVerticalFences() const { return verticalFences; }

    void reduceP1Fences() { if (p1Fences) --p1Fences; }
    void reduceP2Fences() { if (p2Fences) --p2Fences; }
    uint8_t getP1Fences() const { return p1Fences; }
    uint8_t getP2Fences() const { return p2Fences; }

    void setActivePlayer(uint8_t player) { activePlayer = player; }
    uint8_t getActivePlayer() const { return activePlayer; }

private:
    std::vector<std::vector<uint8_t>> graph;
    std::vector<Position> horizontalFences;
    std::vector<Position> verticalFences;
    Position p1; // [0, 0] - [8, 8]
    Position p2; // [0, 0] - [8, 8]
    uint8_t p1Fences;
    uint8_t p2Fences;
    uint8_t activePlayer;

    void setP1Fences(uint8_t n) { p1Fences = n; }
    void setP2Fences(uint8_t n) { p2Fences = n; }

    void deleteVerticalEdge(uint8_t top, uint8_t bottom);
    void deleteHorizontalEdge(uint8_t left, uint8_t right);
};
