#pragma once

#include <cstdint>
#include <vector>

uint8_t distanceToBase(const uint8_t position, const uint8_t active_player);
uint8_t positionDifference(const uint8_t min_player_position, const uint8_t max_player_position, const uint8_t active_player);
uint8_t movesToNextColumn(const std::vector<std::vector<uint8_t>>& board, const uint8_t player_position, const uint8_t active_player);