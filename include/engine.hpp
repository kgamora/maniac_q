#pragma once

#include "board.hpp"

#include <cstdint>
#include <vector>
#include <string>

int distanceToBase(int maxPlayerPosition, int maxPlayer);
int positionDifference(int minPlayerPosition, int maxPlayerPosition, int maxPlayer);
int movesToNextColumn(const Board& board, int player_position, int active_player);
double evalPosition(const Board& board);
std::string getBestMoveOnDepth(const Board& startBoard, int32_t depth);