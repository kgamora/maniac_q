//
// Created by ksgamora on 08.11.22.
//

#include "make_fence.hpp"

bool checkFence(const Board& currentState, Position pos, bool horizontal) {
//    assert(currentState.getPlayerFences(currentState.getActivePlayerIndex()) > 0);

    auto horizontalFences = currentState.getHorizontalFences();
    auto verticalFences = currentState.getVerticalFences();
    if (std::find(horizontalFences.begin(), horizontalFences.end(), pos) != horizontalFences.end()
    ||  std::find(verticalFences.begin(), verticalFences.end(), pos) != verticalFences.end()) {
        return false;
    }

    if (horizontal)
    {
        if (std::find(horizontalFences.begin(), horizontalFences.end(), Position(pos.row, pos.col - 1)) != horizontalFences.end()
        ||  std::find(horizontalFences.begin(), horizontalFences.end(), Position(pos.row, pos.col + 1)) != horizontalFences.end()) {
            return false;
        }
    } else if (std::find(verticalFences.begin(), verticalFences.end(), Position(pos.row - 1, pos.col)) != verticalFences.end()
           ||  std::find(verticalFences.begin(), verticalFences.end(), Position(pos.row + 1, pos.col)) != verticalFences.end()) {
        return false;
    }
    return true;
}

Board makeFence(Board boardCopy, Position pos, bool horizontal) {
    checkFence(boardCopy, pos, horizontal);
    boardCopy.addFence(pos, horizontal);
    if (boardCopy.getPlayerFences(boardCopy.getActivePlayerIndex()) == 0)
    {
        boardCopy.reducePlayerFences(boardCopy.getActivePlayerIndex());
    }
    return boardCopy;
}

