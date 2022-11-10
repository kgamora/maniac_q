//
// Created by ksgamora on 08.11.22.
//

#include "make_fence.hpp"
#include "is_valide_state.hpp"


// Исправить currentState -> currentBoard или типа того
bool checkFence(const Board& currentState, Position pos, bool horizontal) {
//    assert(currentState.getPlayerFences(currentState.getActivePlayerIndex()) > 0);

    // 7 потому, что нельзя поставить доску на край 8
    if (pos.row < 0 or pos.row > 7 or pos.col < 0 or pos.col > 7) {
        return false;
    }

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
    //ПРОВЕРКА ВАЛИДНОСТИ ПОЗИЦИИ

    Board newBoard = currentState;
    newBoard.addFence(pos, horizontal);

    //return true;
    return isValidState(newBoard);
}

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
