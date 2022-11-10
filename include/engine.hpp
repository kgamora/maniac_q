#pragma once

#include "engine.hpp"
#include "make_fence.hpp"
#include "make_move.hpp"
#include "validation.hpp"
#include "board.hpp"

#include <vector>
#include <cstdint>
#include <string>

class Engine {
public:
    std::pair<std::string, double> min_max(const Board& startBoard, int depth, bool isMax);
    double evalPosition(const Board& board);
private:
    int movesToOppBase(const Board& board, int player_position, int active_player);
    int distanceToBase(int maxPlayerPosition, int maxPlayer);
    int positionDifference(int minPlayerPosition, int maxPlayerPosition, int maxPlayer);
    int movesToNextRow(const Board& board, int player_position, int active_player);
    std::vector<std::pair<std::string, Board>> boardChildrenFast(const Board& board);
};