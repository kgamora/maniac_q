#pragma once

#include "engine.hpp"
#include "validation.hpp"
#include "board.hpp"

#include <vector>
#include <cstdint>
#include <string>

class Engine {
public:
    std::pair<std::string, double> minMax(const Board& startBoard, int depth, bool isMax);
    double evalPosition(const Board& board);
    static Board makeTurn(const Board& state, const std::string& turn);
    static Board makeFence(Board board_copy, Position pos, bool horizontal);
    static Board makeMove(Board boardCopy, Position target);

private:
    int movesToOppBase(const Board& board, int playerPosition, int activePlayer);
    int distanceToBase(int maxPlayerPosition, int maxPlayer);
    int positionDifference(int minPlayerPosition, int maxPlayerPosition, int maxPlayer);
    int movesToNextRow(const Board& board, int playerPosition, int activePlayer);
    std::vector<std::pair<std::string, Board>> boardChildrenFast(const Board& board);
};