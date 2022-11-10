#include "board.hpp"

bool dfs(const std::vector<std::vector<int>>& graph, int start, int finish);

namespace Validation {
    bool isValidState(const Board& board);
    bool checkFence(const Board& board, Position pos, bool horizontal);
    bool checkMove(const Board& board, Position target);
    bool isGameFinished(const Board& board);
    bool checkTurn(const Board& board, const std::string& turn);
}