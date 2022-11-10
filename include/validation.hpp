#include "board.hpp"

bool dfs(const std::vector<std::vector<int>>& graph, int start, int finish);

namespace Validation {
    bool isValidState(const Board& board);
    bool checkFence(const Board& currentState, Position pos, bool horizontal);
    bool checkMove(Board boardCopy, Position target);
}