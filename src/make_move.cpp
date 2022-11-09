#include "make_move.hpp"

#include <vector>

bool checkMove(Board boardCopy, Position target) {

    //если позиция-цель лежит вне поля
    if (target.col > 8 || target.col < 0 || target.row < 0 || target.row > 8) {
        return false;
    }

    uint8_t dstPosInGraph = (target.row) * BOARD_SIDE_LENGTH + target.col;
    int posInGraph = boardCopy.getPlayerPos(boardCopy.getActivePlayerIndex()).toSingleInt();
    int oppPosInGraph = boardCopy.getPlayerPos((boardCopy.getActivePlayerIndex() + 1) % 2).toSingleInt();

//    if (boardCopy.getActivePlayer() == 1) {
//        posInGraph = boardCopy.getP1().row * BOARD_SIDE_LENGTH + boardCopy.getP1().col;
//        oppPosInGraph = boardCopy.getP2().row * BOARD_SIDE_LENGTH + boardCopy.getP2().col;
//    } else if (boardCopy.getActivePlayer() == 2){
//        posInGraph = boardCopy.getP2().row * BOARD_SIDE_LENGTH + boardCopy.getP2().col;
//        oppPosInGraph = boardCopy.getP1().row * BOARD_SIDE_LENGTH + boardCopy.getP1().col;
//    }

    Position activePos = Position(posInGraph / 9, posInGraph % 9);
    Position oppPos = Position(oppPosInGraph / 9, oppPosInGraph % 9);

    // если пытаемся встать на прежнее место
    if (activePos == target) {
        return false;
    }

    std::vector<int> goodFields = boardCopy.getGraph()[posInGraph];
    std::vector<int> goodOppFields = boardCopy.getGraph()[oppPosInGraph];

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
        return true;
    }

    //если хотим куда-то хитро перейти
    //точно знаем, что target лежит в поле

    //если хотим перейти через клетку в направлении строки 0
    if (activePos.col == target.col && activePos.row == target.row + 2) {
        //если при этом мы не перепрыгиваем через противника, то false
        if (oppPos.col != activePos.col || oppPos.row != activePos.row - 1) {
            return false;
        }
        //если перепрыгиваем соперника
        //если поле-цель достижима из противника, то true. Иначе false
        return (std::find(goodOppFields.begin(), goodOppFields.end(), dstPosInGraph) != goodOppFields.end());
    }

    //если хотим перейти через клетку в направлении строки 8
    if (activePos.col == target.col && activePos.row == target.row + 2) {
        if (oppPos.col != activePos.col || oppPos.row != activePos.row + 1) {
            return false;
        }
        return (std::find(goodOppFields.begin(), goodOppFields.end(), dstPosInGraph) != goodOppFields.end());
    }

    //если хотим перейти через клетку в направлении столбца 0
    if (activePos.row == target.row && activePos.col == target.col + 2) {
        if (oppPos.row != activePos.row || oppPos.col != activePos.col - 1) {
            return false;
        }
        return (std::find(goodOppFields.begin(), goodOppFields.end(), dstPosInGraph) != goodOppFields.end());
    }

    //если хотим перейти через клетку в направлении столбца 8
    if (activePos.row == target.row && activePos.col == target.col - 2) {
        if (oppPos.row != activePos.row || oppPos.col != activePos.col + 1) {
            return false;
        }
        return (std::find(goodOppFields.begin(), goodOppFields.end(), dstPosInGraph) != goodOppFields.end());
    }

    //если хотим перейти по диагонали вверх
    if (activePos.row == target.row - 1 && (activePos.col == target.col - 1 || activePos.col == target.col + 1)) {
        //если оппонент перед нами
        if (oppPos.row == target.row && oppPos.col == activePos.col) {
            //смотрим на клетку за соперником
            uint8_t nextToOppPosInGraph = oppPosInGraph - 9;
            //если в нее можно попасть, то нельзя ходить по диагонали
            if (std::find(goodOppFields.begin(), goodOppFields.end(), nextToOppPosInGraph) != goodOppFields.end()) {
                return false;
            }
            //если в нее нельзя попасть, то проверяем, можно ли из позиции соперника попасть в клетку-цель
            //если можно, то true
            return (std::find(goodOppFields.begin(), goodOppFields.end(), dstPosInGraph) != goodOppFields.end());
        } else {
            // если оппонент не перед нами
            return false;
        }
    }

    //если хотим перейти по диагонали вниз
    if (activePos.row == target.row + 1 && (activePos.col == target.col - 1 || activePos.col == target.col + 1)) {
        //если оппонент перед нами
        if (oppPos.row == target.row && oppPos.col == activePos.col) {
            //смотрим на клетку за соперником
            uint8_t nextToOppPosInGraph = oppPosInGraph + 9;
            //если в нее можно попасть, то нельзя ходить по диагонали
            if (std::find(goodOppFields.begin(), goodOppFields.end(), nextToOppPosInGraph) != goodOppFields.end()) {
                return false;
            }
            //если в нее нельзя попасть, то проверяем, можно ли из позиции соперника попасть в клетку-цель
            //если можно, то true
            return (std::find(goodOppFields.begin(), goodOppFields.end(), dstPosInGraph) != goodOppFields.end());
        } else {
            // если оппонент не перед нами
            return false;
        }
    }
    return false;
}

Board makeMove(Board boardCopy, Position target) {
    boardCopy.setPlayerPos(boardCopy.getActivePlayerIndex(), target);
    boardCopy.setActivePlayerIndex((boardCopy.getActivePlayerIndex() + 1) % 2);
    return boardCopy;
}