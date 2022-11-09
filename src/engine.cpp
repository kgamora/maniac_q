#include "engine.hpp"

#include <vector>
#include <queue>
#include <cstdint>

// EXTEND ALL THIS FUNCTIONS FOR MORE THAN 2 PLAYERS

uint8_t distanceToBase(uint8_t playerPosition, uint8_t player) {
    if (player == 1) {
        return playerPosition / BOARD_SIDE_LENGTH;
    } else {
        return ((BOARD_SIZE - 1) - playerPosition) / BOARD_SIDE_LENGTH;
    }
}

// I have douts about validity of this function
int8_t positionDifference(uint8_t minPlayerPosition, uint8_t maxPlayerPosition, uint8_t maxPlayer) {
    uint8_t minPlayer = 1 + (maxPlayer) % 2;

    int8_t positionMax = distanceToBase(maxPlayerPosition, maxPlayer);
    int8_t positionMin = distanceToBase(minPlayerPosition, minPlayer);

    return positionMax - positionMin;
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

double evalPosition(const Board& board, uint8_t minPlayerPosition, uint8_t maxPlayerPosition, uint8_t maxPlayer) {
    uint8_t minPlayer = 1 + (maxPlayer) % 2;

    uint8_t f1 = distanceToBase(maxPlayerPosition, maxPlayer);
    // int8_t !!!!!!!
    int8_t f2 = positionDifference(minPlayerPosition, maxPlayerPosition, maxPlayer);
    uint8_t f3 = movesToNextColumn(board, maxPlayerPosition, maxPlayer);
    uint8_t f4 = movesToNextColumn(board, minPlayerPosition, minPlayer);
    return 0.6 * f1 + 0.6001 * f2 + 14.45 * f3 + 6.52 * f4;
}