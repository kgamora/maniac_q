//
// Created by ksgamora on 08.11.22.
//

#include "make_fence.hpp"

Board makeFence(Board boardCopy, Position pos, bool horizontal) {
    //checkFence(boardCopy, pos, horizontal);
    boardCopy.addFence(pos, horizontal);
    int activePlayerIndex = boardCopy.getActivePlayerIndex();
    if (boardCopy.getPlayerFences(activePlayerIndex) != 0)
    {
        boardCopy.reducePlayerFences(activePlayerIndex);
    }
    boardCopy.setActivePlayerIndex((activePlayerIndex + 1) % 2);
    return boardCopy;
}
