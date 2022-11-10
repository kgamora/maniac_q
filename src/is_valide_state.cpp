#include "board.hpp"
#include "is_valide_state.hpp"

#include <stack>
#include <vector>
#include <cstdint>

bool dfs(const std::vector<std::vector<int>>& graph, int start, int finish) {
    std::vector<int> visited(BOARD_SIZE, false);
    std::stack<int> stack;
    stack.push(start);
    while (!stack.empty()) {
        int s = stack.top();
        stack.pop();
        if (!visited[s]) {
            if (s / BOARD_SIDE_LENGTH == finish) {
                return true;
            }
            visited[s] = true;
        }

        for (int i : graph[s]) {
            if (!visited[i]) {
                stack.push(i);
            }
        }
    }
    return false;
}

bool isValidState(const Board& board) {
//    int p1_position = board.getP1().row * BOARD_SIDE_LENGTH + board.getP1().col;
//    int p2_position = board.getP2().row * BOARD_SIDE_LENGTH + board.getP2().col;
    // Добавить проверки позиции пешек
    // Добавить проверки позиции досок
    // Добавить проверки количества досок
    return (dfs(board.getGraph(), board.getPlayerPos(0).toSingleInt(), BOARD_SIDE_LENGTH - 1) && dfs(board.getGraph(), board.getPlayerPos(1).toSingleInt(), 0));
}