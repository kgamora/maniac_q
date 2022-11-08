#include "is_valide_state.h"

#include <stack>

bool dfs(std::vector<std::vector<uint8_t>>& graph, uint8_t start, uint8_t finish) {
    std::vector<bool> visited(81, false);
    std::stack<uint8_t> stack;
    stack.push(start);
    while (!stack.empty()) {
        uint8_t s = stack.top();
        stack.pop();
        if (!visited[s]) {
            if (s / 9 == finish) {
                return true;
            }
            visited[s] = true;
        }

        for (auto i = graph[s].begin(); i != graph[s].end(); ++i) {
            if (!visited[*i]) {
                stack.push(*i);
            }
        }
    }
    return false;
}

bool isValidState(State& state) {
    std::vector<std::vector<uint8_t>> graph = state.getGraph();
    auto p1_position_pair = state.getP1();
    uint8_t p1_position = p1_position_pair.first * 9 + p1_position_pair.second;

    auto p2_position_pair = state.getP2();
    uint8_t p2_position = p2_position_pair.first * 9 + p2_position_pair.second;

    return (dfs(graph, p1_position, 8) && dfs(graph, p2_position, 0));
}