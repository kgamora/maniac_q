#include "engine.hpp"
#include "validation.hpp"

#include <vector>
#include <queue>

int Engine::distanceToBase(int playerPosition, int player) {
    if (player == 0) {
        return playerPosition / BOARD_SIDE_LENGTH;
    } else {
        return ((BOARD_SIZE - 1) - playerPosition) / BOARD_SIDE_LENGTH;
    }
}

int Engine::positionDifference(int minPlayerPosition, int maxPlayerPosition, int maxPlayer) {
    int minPlayer = (1 + maxPlayer) % 2;

    int positionMax = distanceToBase(maxPlayerPosition, maxPlayer);
    int positionMin = distanceToBase(minPlayerPosition, minPlayer);

    return positionMax - positionMin;
}

int Engine::movesToNextRow(const Board& board, int playerPosition, int activePlayer) {
    if ((activePlayer == 0 && playerPosition / BOARD_SIDE_LENGTH == BOARD_SIDE_LENGTH - 1)
    || (activePlayer == 1 && playerPosition / BOARD_SIDE_LENGTH == 0)) {
        return -1000;
    }

    int depth = 0;
    std::queue<int > q;
    q.push(playerPosition);
    size_t nodesOnLevel = q.size();

    std::vector<int> visited(BOARD_SIZE, false);

    while (!q.empty()) {
        while (nodesOnLevel != 0) {
            int currentPosition = q.front();
            // если ходит первый игрок
            if (activePlayer == 0) {
                // то мы дошли до нужной строки в этом условии
                if (currentPosition / BOARD_SIDE_LENGTH == playerPosition / BOARD_SIDE_LENGTH + 1) {
                    return depth;
                }
            } else {
                if (currentPosition / BOARD_SIDE_LENGTH + 1 == playerPosition / BOARD_SIDE_LENGTH) {
                    return depth;
                }
            }

            for (int position : board.getGraph()[currentPosition]) {
                if (!visited[position]) {
                    q.push(position);
                }
            }

            visited[currentPosition] = true;
            q.pop();
            --nodesOnLevel;
        }

        ++depth;
        nodesOnLevel = q.size();
    }
    return depth;
}


int Engine::movesToOppBase(const Board& board, int playerPosition, int activePlayer) {

    if ((activePlayer == 0 && playerPosition / BOARD_SIDE_LENGTH == BOARD_SIDE_LENGTH - 1)
    || (activePlayer == 1 && playerPosition / BOARD_SIDE_LENGTH == 0)) {
        return -1000;
    }

    int depth = 0;
    std::queue<int> q;
    q.push(playerPosition);
    size_t nodesOnLevel = q.size();

    std::vector<int> visited(BOARD_SIZE, false);

    while (!q.empty()) {
        while (nodesOnLevel != 0) {
            int currentPosition = q.front();
            // если ходит первый игрок
            if (activePlayer == 0) {
                // то мы дошли до нужной строки в этом условии
                if (currentPosition / BOARD_SIDE_LENGTH == BOARD_SIDE_LENGTH - 1) {
                    return depth;
                }
            } else {
                if (currentPosition / BOARD_SIDE_LENGTH == 0) {
                    return depth;
                }
            }

            for (int position : board.getGraph()[currentPosition]) {
                if (!visited[position]) {
                    q.push(position);
                }
            }

            visited[currentPosition] = true;
            q.pop();
            --nodesOnLevel;
        }

        ++depth;
        nodesOnLevel = q.size();
    }
    return depth;
}

double Engine::evalPosition(const Board& board) {
    int minPlayer = (board.getMaxPlayerIndex() + 1) % 2;
    int maxPlayer = board.getMaxPlayerIndex();

//    int f1 = distanceToBase(board.getPlayerPos(maxPlayer).toSingleInt(), board.getMaxPlayerIndex());
//    int f2 = positionDifference(board.getPlayerPos(minPlayer).toSingleInt(), board.getPlayerPos(maxPlayer).toSingleInt(), maxPlayer);
//    int f3 = movesToNextRow(board, board.getPlayerPos(maxPlayer).toSingleInt(), maxPlayer);
//    int f4 = movesToNextRow(board, board.getPlayerPos(minPlayer).toSingleInt(), minPlayer);
    /*
    std::cout << "distanceToBase: " << f1 << std::endl;
    std::cout << "positionDifference: " << f2 << std::endl;
    std::cout << "movesToNextRow(max(" << maxPlayer << ")): " << f3 << std::endl;
    std::cout << "movesToNextRow(min(" << minPlayer << ")): " << f4 << std::endl;
     */

    //int f0 = distanceToBase(board.getPlayerPos(minPlayer).toSingleInt(), minPlayer);
    int f1 = movesToOppBase(board, board.getPlayerPos(maxPlayer).toSingleInt(), maxPlayer);
    int f2 = movesToOppBase(board, board.getPlayerPos(minPlayer).toSingleInt(), minPlayer);

    return f2 - f1;
}

std::vector<std::pair<std::string, Board>> Engine::boardChildrenFast(const Board& board) {
    std::vector<std::pair<std::string, Board>> children;

    for (int i = 0; i < BOARD_SIDE_LENGTH; ++i) {
        for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
            Position pos(i, j);
            if (Validation::checkFence(board, pos, true)) {
                children.emplace_back(pos.toStrAsFence(true), makeFence(board, pos, true));
            }
            if (Validation::checkFence(board, pos, false)) {
                children.emplace_back(pos.toStrAsFence(false), makeFence(board, pos, false));
            }
            if (Validation::checkMove(board, pos)) {
                children.emplace_back(pos.toStr(), makeMove(board, pos));
            }
        }
    }

    //перебираем ходы активного игрока
    //позиция игрока, который сейчас ходит
    auto activePos = board.getPlayerPos(board.getActivePlayerIndex());
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            Position newPos(activePos.row + i, activePos.col + j);
            if (Validation::checkMove(board, newPos)) {
                children.emplace_back(newPos.toStr(), makeMove(board, newPos));
            }
        }
    }
    return children;
}

// Алгоритм минимакса без отсечения
std::pair<std::string, double> Engine::minMax(const Board& startBoard, int depth, bool isMax) {
    // если depth == 0, то считаем текущую позицию
    if (depth == 0) {
        double evalCurPos = evalPosition(startBoard);
        return std::make_pair("",evalCurPos);
    }

    // если хотим проанализировать хотя бы один ход вперед
    // получаем детей
    auto children = boardChildrenFast(startBoard);

    //массив оценок для детей
    std::vector<double> childrenVal;

    //оценка текущей позиции
    double evalCurPosition = evalPosition(startBoard);

    // проходим по массиву детей, записывая их оценки
    for (const auto& [str, board] : children) {
        //добавляем оценку текущего ребенка в массив
        double evalChildPosition = minMax(board, depth - 1, !isMax).second;
        childrenVal.push_back(evalChildPosition);
    }

    //номер лучшего ребенка в списке детей
    int bestChild = -1;
    if (isMax) {
        bestChild =  std::max_element(childrenVal.begin(), childrenVal.end()) - childrenVal.begin();
    } else {
        bestChild =  std::min_element(childrenVal.begin(), childrenVal.end()) - childrenVal.begin();
    }

    return std::make_pair(children[bestChild].first, childrenVal[bestChild]);
}

Board Engine::makeTurn(const Board& state, const std::string& turn) {
    int row = turn[1] - '1';
    int col = turn[0] - 'a';
    if (turn.size() == 2) {
        return makeMove(state, {row, col});
    } else {
        return makeFence(state, {row, col}, turn[2] == 'h');
    }
}

Board Engine::makeFence(Board boardCopy, Position pos, bool horizontal) {
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

Board Engine::makeMove(Board boardCopy, Position target) {
    boardCopy.setPlayerPos(boardCopy.getActivePlayerIndex(), target);
    boardCopy.setActivePlayerIndex((boardCopy.getActivePlayerIndex() + 1) % 2);
    return boardCopy;
}
