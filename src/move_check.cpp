#include "move_check.hpp"
#include "is_valide_state.hpp"

#include <stack>

bool isMoveValid(const Board& board, std::string& move) {

    // что-то делаем, куда-то ходим
    return isValidState(board);
}

