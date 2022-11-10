#include "engine.hpp"
#include "make_fence.hpp"
#include "make_move.hpp"
#include "validation.hpp"

#include <vector>
#include <queue>
#include <cstdint>
#include <limits>

// EXTEND ALL THIS FUNCTIONS FOR MORE THAN 2 PLAYERS

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

int Engine::movesToNextRow(const Board& board, int player_position, int active_player) {
    if ((active_player == 0 && player_position / 9 == 8) ||(active_player == 1 && player_position / 9 == 0)) {
        return -1000;
    }
    int depth = 0;
    std::queue<int > q;
    q.push(player_position);
    size_t nodes_on_level = q.size();

    std::vector<int> visited(BOARD_SIZE, false);

    while (!q.empty()) {
        while (nodes_on_level != 0) {
            int current_position = q.front();
            // если ходит первый игрок
            if (active_player == 0) {
                // то мы дошли до нужной строки в этом условии
                if (current_position / BOARD_SIDE_LENGTH == player_position / BOARD_SIDE_LENGTH + 1) {
                    return depth;
                }
            } else {
                if (current_position / BOARD_SIDE_LENGTH + 1 == player_position / BOARD_SIDE_LENGTH) {
                    return depth;
                }
            }

            for (int position : board.getGraph()[current_position]) {
                if (!visited[position]) {
                    q.push(position);
                }
            }

            visited[current_position] = true;
            q.pop();
            --nodes_on_level;
        }

        ++depth;
        nodes_on_level = q.size();
    }
    return depth;
}


int Engine::movesToOppBase(const Board& board, int player_position, int active_player) {

    if ((active_player == 0 && player_position / 9 == 8) || (active_player == 1 && player_position / 9 == 0)) {
        return -1000;
    }

    int depth = 0;
    std::queue<int > q;
    q.push(player_position);
    size_t nodes_on_level = q.size();

    std::vector<int> visited(BOARD_SIZE, false);

    while (!q.empty()) {
        while (nodes_on_level != 0) {
            int current_position = q.front();
            // если ходит первый игрок
            if (active_player == 0) {
                // то мы дошли до нужной строки в этом условии
                if (current_position / BOARD_SIDE_LENGTH == 8) {
                    return depth;
                }
            } else {
                if (current_position / BOARD_SIDE_LENGTH == 0) {
                    return depth;
                }
            }

            for (int position : board.getGraph()[current_position]) {
                if (!visited[position]) {
                    q.push(position);
                }
            }

            visited[current_position] = true;
            q.pop();
            --nodes_on_level;
        }

        ++depth;
        nodes_on_level = q.size();
    }
    return depth;
}




double Engine::evalPosition(const Board& board) {
    int minPlayer = ((board.getMaxPlayerIndex()) + 1) % 2;
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

    std::vector<std::pair<std::string,  Board>> children;

    for (int i = 0; i < BOARD_SIDE_LENGTH; ++i) {
        for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
            Position pos(i, j);
            if (Validation::checkFence(board, pos, true)) {
                children.emplace_back(translateFence(pos, true), makeFence(board, pos, true));
            }
            if (Validation::checkFence(board, pos, false)) {
                children.emplace_back(translateFence(pos, false), makeFence(board, pos, false));
            }
            if (Validation::checkMove(board, pos)) {
                children.emplace_back(translatePosition(pos), makeMove(board, pos));
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
                children.emplace_back(translatePosition(newPos), makeMove(board, newPos));
            }
        }
    }
    return children;
}

// Алгоритм минимакса без отсечения
std::pair<std::string, double> Engine::min_max(const Board& startBoard, int depth, bool isMax) {
    // если depth == 0, то считаем текущую позицию
    if (depth == 0) {
        double evalCurPos = evalPosition(startBoard);
        return std::make_pair("", evalCurPos);
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
        double evalChildPosition = min_max(board, depth - 1, !isMax).second;
        childrenVal.push_back(evalChildPosition);
    }

    /*
    for (int i = 0; i < childrenVal.size(); ++i) {
        std::cout << childrenVal[i] << ' ';
    }
    std::cout << std::endl;
     */

    //номер лучшего ребенка в списке детей
    int bestChild = -1;
    if (isMax) {
        bestChild =  max_element(childrenVal.begin(), childrenVal.end()) - childrenVal.begin();
    } else {
        bestChild =  min_element(childrenVal.begin(), childrenVal.end()) - childrenVal.begin();
    }

    //std::cout << "Лучший ход в данной ситуации: " << std::endl;
    //printBoard(children[bestChild].second);

    return std::make_pair(children[bestChild].first, childrenVal[bestChild]);
}