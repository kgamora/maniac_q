#include "make_move.hpp"

#include <vector>

// Принимает позицию target – поле, на которое хотим сделать ход
// target принимает значения от [0,0] до [8,8]!
Board makeMove(Board boardCopy, Position target) {
    boardCopy.setPlayerPos(boardCopy.getActivePlayerIndex(), target);
    boardCopy.setActivePlayerIndex((boardCopy.getActivePlayerIndex() + 1) % 2);
    return boardCopy;
}