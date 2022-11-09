#pragma once

#include "board.hpp"

#include <cstdint>
#include <vector>

uint8_t distanceToBase(uint8_t maxPlayerPosition, uint8_t maxPlayer);
int8_t positionDifference(uint8_t minPlayerPosition, uint8_t maxPlayerPosition, uint8_t maxPlayer);
uint8_t movesToNextColumn(const Board& board, uint8_t player_position, uint8_t active_player);
double evalPosition(const Board& board, uint8_t minPlayerPosition, uint8_t maxPlayerPosition, uint8_t maxPlayer);