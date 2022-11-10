#include "board.hpp"
#include "validation.hpp"

#include <stack>
#include <vector>

bool dfs(const std::vector<std::vector<int>>& graph, int start, int finish) {
    std::vector<int> visited(BOARD_SIZE, false);
    std::stack<int> stack;
    stack.push(start);
    while (!stack.empty()) {
        int s = stack.top();
        stack.pop();
        if (!visited[s]) {
            if (s / BOARD_SIDE_LENGTH == finish) {
                return true;
            }
            visited[s] = true;
        }

        for (int i : graph[s]) {
            if (!visited[i]) {
                stack.push(i);
            }
        }
    }
    return false;
}

namespace Validation {

bool isValidState(const Board &board) {
    const std::vector<Player>& players = board.getPlayers();

    // Проверки позиции пешек
    for (int i = 0; i < players.size(); ++i) {
        for (int j = i + 1; j < players.size(); j++) {
            if (players[i].pos == players[j].pos) return false;
        }
    }

    // Добавить проверки позиции досок
    const std::vector<Position>& horizontalFences = board.getHorizontalFences();
    const std::vector<Position>& verticalFences = board.getVerticalFences();

    // Проверка строк
    for (int i = 0; i < horizontalFences.size(); ++i) {
        int iRow = horizontalFences[i].row;
        int iCol = horizontalFences[i].col;
        
        bool outOfBorder = iRow > 7 || iRow < 0 || iCol > 7 || iCol < 0;
        if (outOfBorder) return false;

        for (int j = i + 1; j < horizontalFences.size(); j++) {
            int jRow = horizontalFences[j].row;
            int jCol = horizontalFences[j].col;

            if (jRow == iRow && (iCol == jCol + 1 || iCol == jCol - 1 || iCol == jCol)) return false;
        }
    }

    // Проверка колонок
    for (int i = 0; i < verticalFences.size(); ++i) {
        int iRow = verticalFences[i].row;
        int iCol = verticalFences[i].col;
        
        bool outOfBorder = iRow > 7 || iRow < 0 || iCol > 7 || iCol < 0;
        if (outOfBorder) return false;

        for (int j = i + 1; j < verticalFences.size(); j++) {
            int jRow = verticalFences[j].row;
            int jCol = verticalFences[j].col;

            if (jCol == iCol && (iRow == jRow + 1 || iRow == jRow - 1 || iRow == jRow)){
                return false;
            }
        }
    }

    // Проверка непересечения горизонтальных и вертикальных fences
    for (const Position& hFence : horizontalFences) {
        for (const Position& vFence : verticalFences) {
            if (hFence == vFence) return false;
        }
    }

    // Добавить проверки количества досок
    for (const Player& player : players) {
        if (player.fenceCount < 0) return false;
    }

    return (dfs(board.getGraph(), board.getPlayerPos(0).toSingleInt(), BOARD_SIDE_LENGTH - 1) &&
            dfs(board.getGraph(), board.getPlayerPos(1).toSingleInt(), 0));
}

bool checkFence(const Board &board, Position pos, bool horizontal) {

    // 7 потому, что нельзя поставить доску на край 8
    if (pos.row < 0 or pos.row > 7 or pos.col < 0 or pos.col > 7) {
        std::cout << "sdlmkk1" << std::endl;
        return false;
    }

    if (board.getPlayers()[board.getActivePlayerIndex()].fenceCount == 0) {
        std::cout << "sdlmkk2" << std::endl;
        return false;
    }

    auto horizontalFences = board.getHorizontalFences();
    auto verticalFences = board.getVerticalFences();
    if (std::find(horizontalFences.begin(), horizontalFences.end(), pos) != horizontalFences.end()
        || std::find(verticalFences.begin(), verticalFences.end(), pos) != verticalFences.end()) {
        std::cout << "sdlmkk3" << std::endl;
        return false;
    }

    if (horizontal) {
        if (std::find(horizontalFences.begin(), horizontalFences.end(), Position(pos.row, pos.col - 1)) !=
            horizontalFences.end()
            || std::find(horizontalFences.begin(), horizontalFences.end(), Position(pos.row, pos.col + 1)) !=
               horizontalFences.end()) {
            std::cout << "sdlmkk4" << std::endl;
            return false;
        }
    } else if (std::find(verticalFences.begin(), verticalFences.end(), Position(pos.row - 1, pos.col)) !=
               verticalFences.end()
               || std::find(verticalFences.begin(), verticalFences.end(), Position(pos.row + 1, pos.col)) !=
                  verticalFences.end()) {
        std::cout << "sdlmkk5" << std::endl;
        return false;
    }

    //ПРОВЕРКА ВАЛИДНОСТИ ПОЗИЦИИ
    Board boardCopy = board;
    boardCopy.addFence(pos, horizontal);

    //return true;
    return isValidState(boardCopy);
}

bool checkMove(const Board& board, Position target) {

    //если позиция-цель лежит вне поля
    if (target.col > 8 || target.col < 0 || target.row < 0 || target.row > 8) {
        return false;
    }

    int dstPosInGraph = (target.row) * BOARD_SIDE_LENGTH + target.col;
    int posInGraph = board.getPlayerPos(board.getActivePlayerIndex()).toSingleInt();
    int oppPosInGraph = board.getPlayerPos((board.getActivePlayerIndex() + 1) % 2).toSingleInt();

    Position activePos = board.getPlayerPos(board.getActivePlayerIndex());
    Position oppPos = board.getPlayerPos((board.getActivePlayerIndex() + 1) % 2);

    // если пытаемся встать на прежнее место
    if (activePos == target) {
        return false;
    }

    std::vector<int> goodFields = board.getGraph()[posInGraph];
    std::vector<int> goodOppFields = board.getGraph()[oppPosInGraph];

    // если противник не рядом с нами
    if (std::find(goodFields.begin(), goodFields.end(), oppPosInGraph) == goodFields.end()) {
        // если желаемое поле рядом с нами
        if (std::find(goodFields.begin(), goodFields.end(), dstPosInGraph) != goodFields.end()) {
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
    if (std::find(goodFields.begin(), goodFields.end(), dstPosInGraph) != goodFields.end()) {
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
    if (activePos.col == target.col && activePos.row == target.row - 2) {
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
            int nextToOppPosInGraph = oppPosInGraph - BOARD_SIDE_LENGTH;
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
            int nextToOppPosInGraph = oppPosInGraph + BOARD_SIDE_LENGTH;
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

bool isGameFinished(const Board& board) {
    const std::vector<Player>& players = board.getPlayers();

    for (const Player& player : players) {
        if (player.pos.row == player.targetRow) return true;
    }
    
    return false;
}

bool checkTurn(const Board &board, const std::string &turn) {
    if (!(turn.size() == 2 or turn.size() == 3)) {
        return false;
    }
    int row = turn[1] - '1';
    int col = turn[0] - 'a';
    if (row < 0 or row > 8 or col < 0 or col > 8) {
        return false;
    }
    if (turn.size() == 3) {
        if (turn[2] != 'h' and turn[2] != 'v') {
            return false;
        }
        if (!checkFence(board, {row, col}, turn[2] == 'h')) {
            return false;
        }
    }
    if (turn.size() == 2 and not checkMove(board, {row, col})) {
        return false;
    }
    return true;
}

} // Validation