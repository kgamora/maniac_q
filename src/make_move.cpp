#include "make_move.hpp"

#include <vector>

bool checkMove(Board boardCopy, Position target) {
    int dstPosInGraph = (target.row) * BOARD_SIDE_LENGTH + target.col;
    int posInGraph = boardCopy.getPlayerPos(boardCopy.getActivePlayerIndex()).toSingleInt();
    int oppPosInGraph = boardCopy.getPlayerPos((boardCopy.getActivePlayerIndex() + 1) % 2).toSingleInt();;

//    if (boardCopy.getActivePlayer() == 1) {
//        posInGraph = boardCopy.getP1().row * BOARD_SIDE_LENGTH + boardCopy.getP1().col;
//        oppPosInGraph = boardCopy.getP2().row * BOARD_SIDE_LENGTH + boardCopy.getP2().col;
//
//    } else if (boardCopy.getActivePlayer() == 2){
//        posInGraph = boardCopy.getP2().row * BOARD_SIDE_LENGTH + boardCopy.getP2().col;
//        oppPosInGraph = boardCopy.getP1().row * BOARD_SIDE_LENGTH + boardCopy.getP1().col;
//    }

    std::vector<int> goodFields = boardCopy.getGraph()[posInGraph];

    // если противник не рядом с нами
    if(std::find(goodFields.begin(), goodFields.end(), oppPosInGraph) == goodFields.end()) {
        // если желаемое поле рядом с нами
        if(std::find(goodFields.begin(), goodFields.end(), dstPosInGraph) != goodFields.end()) {
            return true;
        } else {
            // если противника рядом нет и мы хотим пойти на дальние клетки, то нельзя
            return false;
        }
    }

    // если противник рядом с нами
    if (oppPosInGraph == dstPosInGraph) {
        //если пытаемся встать на место соперника
        return false;
    }

    // если ходим на свободные клетки рядом
    if(std::find(goodFields.begin(), goodFields.end(), dstPosInGraph) != goodFields.end()) {
//        if (boardCopy.getActivePlayer() == 1) {
//            return true;
//            //s.setP1(dst);
//            //return s;
//        } else if (boardCopy.getActivePlayer() == 2)
//        {
//            return true;
//        }
        //s.setP2(dst);
        //return s;
        return true;
    }

    //если хотим куда-то хитро перейти
    //встаем на место соперника и пробуем оттуда перейти на нужную клетку
//    if (boardCopy.getActivePlayer() == 1) {
//        boardCopy.setP1(boardCopy.getP2());
//    }
//    else if (boardCopy.getActivePlayer() == 2)
//    {
//        boardCopy.setP2(boardCopy.getP1());
//    }
    boardCopy.setPlayerPos(boardCopy.getActivePlayerIndex(), boardCopy.getPlayerPos((boardCopy.getActivePlayerIndex() + 1) % 2));

    return checkMove(boardCopy, target);
}

Board makeMove(Board boardCopy, Position target) {
    if (checkMove(boardCopy, target)) {
//        if (boardCopy.getActivePlayer() == 1) {
//            boardCopy.setP1(target);
//            boardCopy.setActivePlayer(2);
//        } else {
//            boardCopy.setP2(target);
//            boardCopy.setActivePlayer(1);
//        }
        boardCopy.setPlayerPos(boardCopy.getActivePlayerIndex(), target);
        boardCopy.setActivePlayerIndex((boardCopy.getActivePlayerIndex() + 1) % 2);

        return boardCopy;
    }
    std::cout << "CheckMove error" << std::endl;
    assert(false);
    // ЕСЛИ ОКАЗАЛИСЬ ЗДЕСЬ, ТО ОШИБКА – НЕПРАВИЛЬНЫЙ ХОД
    return boardCopy;
}