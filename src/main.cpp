//
// Created by Иван Назаров on 08.11.2022.
//

#include "board.hpp"
#include "read_write.hpp"
#include "is_valide_state.hpp"
#include "make_move.hpp"
#include "engine.hpp"

#include <sstream>

int main() {
    std::stringstream ss;
    ss << "d4f4e7 / a2a8 / e4 e6 / 7 8 / 2";
    Board board(ss);
    printBoard(board);
    assert(isValidState(board));
    std::string bestMove = getBestMoveOnDepth(board, 1);
    std::cout << "лучший ход: " << bestMove;
}