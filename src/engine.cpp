#include "engine.hpp"
#include "make_fence.hpp"
#include "make_move.hpp"

#include <vector>
#include <queue>
#include <cstdint>
#include <limits>

// EXTEND ALL THIS FUNCTIONS FOR MORE THAN 2 PLAYERS

int distanceToBase(int playerPosition, int player) {
    if (player == 1) {
        return playerPosition / BOARD_SIDE_LENGTH;
    } else {
        return ((BOARD_SIZE - 1) - playerPosition) / BOARD_SIDE_LENGTH;
    }
}

// I have douts about validity of this function
int positionDifference(int minPlayerPosition, int maxPlayerPosition, int maxPlayer) {
    int minPlayer = 1 + (maxPlayer) % 2;

    int positionMax = distanceToBase(maxPlayerPosition, maxPlayer);
    int positionMin = distanceToBase(minPlayerPosition, minPlayer);

    return positionMax - positionMin;
}

int movesToNextColumn(const Board& board, int player_position, int active_player) {
    int depth = 0;
    std::queue<int > q;

    q.push(player_position);
    size_t nodes_on_level = q.size();

    std::vector<int > visited(BOARD_SIZE, false);

    while (!q.empty()) {
        while (nodes_on_level != 0) {
            int current_position = q.front();

            if (active_player == 1) {
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

double evalPosition(const Board& board) {
    int minPlayer = ((board.getMaxPlayerIndex()) + 1) % 2;
    int maxPlayer = board.getMaxPlayerIndex();

    int f1 = distanceToBase(board.getPlayerPos(maxPlayer).toSingleInt(), board.getMaxPlayerIndex());
    // здесь знаковый int !!!!!!!
    int f2 = positionDifference(board.getPlayerPos(minPlayer).toSingleInt(), board.getPlayerPos(maxPlayer).toSingleInt(), maxPlayer);
    int f3 = movesToNextColumn(board, board.getPlayerPos(maxPlayer).toSingleInt(), maxPlayer);
    int f4 = movesToNextColumn(board, board.getPlayerPos(minPlayer).toSingleInt(), minPlayer);
    return 0.6 * f1 + 0.6001 * f2 + 14.45 * f3 + 6.52 * f4;
}

std::vector<Board> stateChildren(const Board& board) {
    std::vector<Board> children;
    for (int i = 0; i < BOARD_SIDE_LENGTH; ++i) {
        for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
            if (checkFence(board, Position(i, j), true)) {
                children.push_back(makeFence(board, Position(i, j), true));
            }
            if (checkFence(board, Position(i, j), false)) {
                children.push_back(makeFence(board, Position(i, j), false));
            }
            if (checkMove(board, Position(i, j))) {
                children.push_back(makeMove(board, Position(i, j)));
            }
        }
    }
    return children;
}

double alpha_beta(const Board& board, int depth, double alpha, double beta, int maximizingPlayer) {
    if (depth == 0) {
        return evalPosition(board);
    }
    double value;
    if (maximizingPlayer) {
        value = std::numeric_limits<double>::min();
        for (const Board& child : stateChildren(board)) {
            value = std::max(value, alpha_beta(child, depth - 1, alpha, beta, false));
            if (value >= beta) {
                break;
            }
            alpha = std::max(alpha, value);
        }
        return value;
    } else {
        value = std::numeric_limits<double>::max();
        for (const Board& child : stateChildren(board)) {
            value = std::min(value, alpha_beta(child, depth - 1, alpha, beta, true));
            if (value <= alpha) {
                break;
            }
            beta = std::min(beta, value);
        }
        return value;
    }
}

std::string getBestMoveOnDepth(const Board& startBoard, int depth) {
    std::vector<std::pair<std::string,  Board>> children;
    for (int i = 0; i < BOARD_SIDE_LENGTH; ++i) {
        for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
            Position pos(i, j);
            if (checkFence(startBoard, pos, true)) {
                children.emplace_back(translateFence(pos, true), makeFence(startBoard, pos, true));
            }
            if (checkFence(startBoard, pos, false)) {
                children.emplace_back(translateFence(pos, false), makeFence(startBoard, pos, false));
            }
            if (checkMove(startBoard, pos)) {
                children.emplace_back(translatePosition(pos), makeMove(startBoard, pos));
            }
        }
    }

    double result = std::numeric_limits<double>::min();
    std::string res_str;

    for (const auto& [str, board] : children) {
        double stateEval = alpha_beta(board, depth, std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), false);
        if (result < stateEval) {
            result = stateEval;
            res_str = str;
        }
    }

    return res_str;
}