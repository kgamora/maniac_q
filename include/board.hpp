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

static const std::map<char, int> cols = {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9},};

struct Position {
    int row;
    int col;

    Position() = default;
    Position(int r, int c) : row(r), col(c) {}

    friend bool operator==(const Position lhs, const Position rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; }
    friend bool operator!=(const Position lhs, const Position rhs) { return !(lhs==rhs); }

    int toSingleInt() const { return row * BOARD_SIDE_LENGTH + col; }
};

struct Player {
    Position pos;
    int fenceCount;
    int startRow;
    int targetRow;
    bool isMaxPlayer;
};

class Board {
public:
    static const int board_size = BOARD_SIZE;

    Board();
    explicit Board(std::istream& is);

    void addFence(Position fence, bool horizontal);

    const std::vector<std::vector<int>>& getGraph() const { return graph; }

    void setPlayerPos(int index, Position pos) { players[index].pos = pos; }
//    void setP1(Position pos) { p1 = pos; }
//    void setP2(Position pos) { p2 = pos; }
    Position getPlayerPos(int index) const { return players[index].pos; }
//    Position getP1() const { return p1; }
//    Position getP2() const { return p2; }

    const std::vector<Position>& getHorizontalFences() const { return horizontalFences; }
    const std::vector<Position>& getVerticalFences() const { return verticalFences; }

//    void reduceP1Fences() { if (p1Fences) --p1Fences; }
//    void reduceP2Fences() { if (p2Fences) --p2Fences; }
    void reducePlayerFences(int index) { if (players[index].fenceCount > 0) --players[index].fenceCount; }

//    int getP1Fences() const { return p1Fences; }
//    int getP2Fences() const { return p2Fences; }
    int getPlayerFences(int index) const { return players[index].fenceCount; }

    void setActivePlayerIndex(int index) { activePlayerIndex = index; }
    int getActivePlayerIndex() const { return activePlayerIndex; }

    int getMaxPlayerIndex() const { return maxPlayerIndex; }

    const std::vector<Player>& getPlayers() const { return players; }
    void setMaxPlayerIndex(int index);
private:
    std::vector<std::vector<int>> graph;
    std::vector<Player> players;
    std::vector<Position> horizontalFences;
    std::vector<Position> verticalFences;
//    Position p1; // [0, 0] - [8, 8]
//    Position p2; // [0, 0] - [8, 8]
//    int p1Fences;
//    int p2Fences;
    int activePlayerIndex;
    int maxPlayerIndex;

//    void setP1Fences(int n) { p1Fences = n; }
//    void setP2Fences(int n) { p2Fences = n; }
    void setPlayerFences(int index, int n) { players[index].fenceCount = n; }

    void deleteVerticalEdge(int top, int bottom);
    void deleteHorizontalEdge(int left, int right);
};
