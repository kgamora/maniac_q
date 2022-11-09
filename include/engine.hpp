#pragma once

#include "board.hpp"

#include <cstdint>
#include <vector>

uint8_t distanceToBase(uint8_t position, uint8_t active_player);
uint8_t positionDifference(uint8_t min_player_position, uint8_t max_player_position, uint8_t active_player);
uint8_t movesToNextColumn(const Board& board, uint8_t player_position, uint8_t active_player);