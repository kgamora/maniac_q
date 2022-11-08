//
// Created by ksgamora on 08.11.22.
//
#include "parse_move.hpp"
#include "make_fence.hpp"
#include "make_move.hpp"

State parseMove(const State& currentState,const std::string& move) {
    uint8_t row = move[1] - '0';
    uint8_t col = move[0] - 'a' + 1;
    if (move.size() == 3) {
        bool isHorizontal = move[2] == 'h';
        return makeFence(currentState, isHorizontal, std::make_pair(row, col));
    } else {
        return makeMove(currentState, std::make_pair(row, col));
    }
}