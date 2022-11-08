#include <vector>
#include <queue>
#include <cstdint>

// EXTEND ALL THIS FUNCTIONS FOR MORE THAN 2 PLAYERS

uint8_t distanceToBase(const uint8_t position, const uint8_t active_player) {
    if (active_player == 1) {
        return position / 9;
    } else {
        return (80 - position) / 9;
    }
}

// I have douts about validity of this function
uint8_t positionDifference(const uint8_t min_player_position, const uint8_t max_player_position, const uint8_t active_player) {
    uint8_t position_max = distanceToBase(max_player_position, active_player);
    uint8_t position_min = distanceToBase(min_player_position, active_player % 2 + 1);

    return position_max - position_min;
}

uint8_t movesToNextColumn(const std::vector<std::vector<uint8_t>>& board, const uint8_t player_position, const uint8_t active_player) {
    uint8_t depth = 0;
    std::queue<uint8_t> q;

    q.push(player_position);
    size_t nodes_on_level = q.size();

    std::vector<bool> visited(81, false);

    while (!q.empty()) {

        while (nodes_on_level != 0) {
            uint8_t current_position = q.front();

            if (active_player == 1) {
                if (current_position / 9 == player_position / 9 + 1) {
                    return depth;
                }
            } else {
                if (current_position / 9 + 1 == player_position / 9) {
                    return depth;
                }
            }

            for (int8_t position : board[current_position]) {
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