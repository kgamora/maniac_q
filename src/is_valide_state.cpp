#include "board.hpp"
#include "is_valide_state.hpp"

#include <stack>
#include <vector>
#include <cstdint>

bool dfs(const std::vector<std::vector<uint8_t>>& graph, uint8_t start, uint8_t finish) {
    std::vector<uint8_t> visited(BOARD_SIZE, false);
    std::stack<uint8_t> stack;
    stack.push(start);
    while (!stack.empty()) {
        uint8_t s = stack.top();
        stack.pop();
        if (!visited[s]) {
            if (s / BOARD_SIDE_LENGTH == finish) {
                return true;
            }
            visited[s] = true;
        }

        for (uint8_t i : graph[s]) {
            if (!visited[i]) {
                stack.push(i);
            }
        }
    }
    return false;
}

bool isValidState(const Board& board) {
    uint8_t p1_position = board.getP1().row * BOARD_SIDE_LENGTH + board.getP1().col;
    uint8_t p2_position = board.getP2().row * BOARD_SIDE_LENGTH + board.getP2().col;
    return (dfs(board.getGraph(), p1_position, BOARD_SIDE_LENGTH - 1) && dfs(board.getGraph(), p2_position, 0));
}