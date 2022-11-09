//
// Created by ksgamora on 08.11.22.
//

#include "board.hpp"
#include "parse_move.hpp"
#include "make_fence.hpp"
#include "make_move.hpp"

Board parseMove(const Board& currentState, const std::string& move) {
    uint8_t row = move[1] - '0';
    uint8_t col = move[0] - 'a' + 1;
    if (move.size() == 3) {
        bool isHorizontal = move[2] == 'h';
        return makeFence(currentState, {row, col}, isHorizontal);
    } else {
        return makeMove(currentState, {static_cast<uint8_t>(row - 1), static_cast<uint8_t>(col - 1)});
    }
}