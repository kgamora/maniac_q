//
// Created by Иван Назаров on 08.11.2022.
//

#include "board.hpp"
#include "read_write.hpp"
#include "is_valide_state.hpp"

int main() {
    Board board(std::cin);
    printBoard(board);
    assert(isValidState(board));
}