#pragma once

#include <vector>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <algorithm>

#define BOARD_SIZE 81
#define BOARD_SIDE_LENGTH 9
#define FENCE_COUNT 10

struct Position {
    int row;
    int col;

    Position() = default;
    Position(int r, int c) : row(r), col(c) {}

    friend bool operator==(const Position lhs, const Position rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; }
    friend bool operator!=(const Position lhs, const Position rhs) { return !(lhs==rhs); }

    int toSingleInt() const { return row * BOARD_SIDE_LENGTH + col; }

    std::string toStr() const {
        char first = 'a' + static_cast<char>(col);
        char second = '1' + static_cast<char>(row);
        std::string result = std::string (1, first);
        result.append(std::string(1, second));
        return result;
    }

    std::string toStrAsFence(bool isHorizontal) const {
        std::string result = toStr();
        if (isHorizontal) {
            result.append("h");
        } else {
            result.append("v");
        }
        return result;
    }
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

    explicit Board(int playerId);
    explicit Board(std::istream& is);

    void print() const;


    void addFence(Position fence, bool horizontal);

    const std::vector<std::vector<int>>& getGraph() const { return graph; }

    void setPlayerPos(int index, Position pos) { players[index].pos = pos; }
    Position getPlayerPos(int index) const { return players[index].pos; }

    const std::vector<Position>& getHorizontalFences() const { return horizontalFences; }
    const std::vector<Position>& getVerticalFences() const { return verticalFences; }

    void reducePlayerFences(int index) { if (players[index].fenceCount > 0) --players[index].fenceCount; }
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
    int activePlayerIndex;
    int maxPlayerIndex;
    void setPlayerFences(int index, int n) { players[index].fenceCount = n; }

    void deleteVerticalEdge(int top, int bottom);
    void deleteHorizontalEdge(int left, int right);
};
