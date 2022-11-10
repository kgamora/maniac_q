//
// Created by Иван Назаров on 08.11.2022.
//

#include "board.hpp"
#include "read_write.hpp"
#include "is_valide_state.hpp"
#include "engine.hpp"

#include <sstream>

int main() {
    std::stringstream ss;
    ss << " / / e1 e9 / 4 4 / 2";
    Board board(ss);
    printBoard(board);
    assert(isValidState(board));
    std::string bestMove = getBestMoveOnDepth(board, 1);
    std::cout << "лучший ход: " << bestMove;
}