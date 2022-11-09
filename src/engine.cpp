#include "engine.hpp"

#include <vector>
#include <queue>
#include <cstdint>

// EXTEND ALL THIS FUNCTIONS FOR MORE THAN 2 PLAYERS

uint8_t distanceToBase(uint8_t position, uint8_t active_player) {
    if (active_player == 1) {
        return position / BOARD_SIDE_LENGTH;
    } else {
        return ((BOARD_SIZE - 1) - position) / BOARD_SIDE_LENGTH;
    }
}

// I have douts about validity of this function
uint8_t positionDifference(uint8_t min_player_position, uint8_t max_player_position, uint8_t active_player) {
    uint8_t position_max = distanceToBase(max_player_position, active_player);
    uint8_t position_min = distanceToBase(min_player_position, active_player % 2 + 1);

    return position_max - position_min;
}

uint8_t movesToNextColumn(const Board& board, uint8_t player_position, uint8_t active_player) {
    uint8_t depth = 0;
    std::queue<uint8_t> q;

    q.push(player_position);
    size_t nodes_on_level = q.size();

    std::vector<uint8_t> visited(BOARD_SIZE, false);

    while (!q.empty()) {
        while (nodes_on_level != 0) {
            uint8_t current_position = q.front();

            if (active_player == 1) {
                if (current_position / BOARD_SIDE_LENGTH == player_position / BOARD_SIDE_LENGTH + 1) {
                    return depth;
                }
            } else {
                if (current_position / BOARD_SIDE_LENGTH + 1 == player_position / BOARD_SIDE_LENGTH) {
                    return depth;
                }
            }

            for (uint8_t position : board.getGraph()[current_position]) {
                if (!visited[position]) {
                    q.push(position);
                }
            }

            visited[current_position] = true;
            q.pop();
            --nodes_on_level;
        }

        ++depth;
        nodes_on_level = q.size();
    }

    return depth;
}