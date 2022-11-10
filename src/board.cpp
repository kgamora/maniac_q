#include "board.hpp"

Board::Board(int playerId)
    : players(2)
    , graph(board_size)
    , activePlayerIndex(0)
    , maxPlayerIndex((playerId + 1) % 2)
{
    players[0].pos = {0, BOARD_SIDE_LENGTH / 2};
    players[0].fenceCount = FENCE_COUNT;
    players[1].pos = {BOARD_SIDE_LENGTH - 1, BOARD_SIDE_LENGTH / 2};
    players[1].fenceCount = FENCE_COUNT;

    players[0].startRow = 0;
    players[1].startRow = BOARD_SIDE_LENGTH - 1;
    players[0].targetRow = players[1].startRow;
    players[1].targetRow = players[0].startRow;

    for(int i = 0; i < board_size; ++i) {
        int row = i / BOARD_SIDE_LENGTH;
        int col = i % BOARD_SIDE_LENGTH;
        if (col > 0) {
            graph[i].push_back(i - 1);
        }
        if (col < BOARD_SIDE_LENGTH - 1) {
            graph[i].push_back(i + 1);
        }
        if (row > 0) {
            graph[i].push_back(i - BOARD_SIDE_LENGTH);
        }
        if (row < BOARD_SIDE_LENGTH - 1) {
            graph[i].push_back(i + BOARD_SIDE_LENGTH);
        }
    }
}

Board::Board(std::istream& is) : Board(0) {
    std::string gamePosition;

    //horizontal wall positions
    is >> gamePosition;

    if (gamePosition[0] != '/') {
        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
            int col = *i - 'a';
            i++;
            int row = *i - '1';
            addFence(Position(row, col), true);
        }
        is >> gamePosition;
    }

    //vertical wall positions
    is >> gamePosition;

    if (gamePosition[0] != '/') {
        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
            int col = *i - 'a';
            i++;
            int row = *i - '1';
            addFence(Position(row, col), false);
        }
        is >> gamePosition;
    }

    //p1 position
    is >> gamePosition;
    int row = gamePosition[1] - '1';
    int col = gamePosition[0] - 'a';
    players[0].pos = {row, col};

    //p2 position
    is >> gamePosition;
    row = gamePosition[1] - '1';
    col = gamePosition[0] - 'a';
    players[1].pos = {row, col};

    // slash
    is >> gamePosition;
    //walls
    is >> gamePosition;
    players[0].fenceCount = gamePosition[0] - '0';
    is >> gamePosition;
    players[1].fenceCount = gamePosition[0] - '0';

    // slash
    is >> gamePosition;
    //who's turn
    is >> gamePosition;
    activePlayerIndex = gamePosition[0] - '1';
    maxPlayerIndex = activePlayerIndex;

    players[0].isMaxPlayer = activePlayerIndex == 0;
    players[1].isMaxPlayer = activePlayerIndex == 1;
    players[0].startRow = 0;
    players[1].startRow = BOARD_SIDE_LENGTH - 1;
    players[0].targetRow = players[1].startRow;
    players[1].targetRow = players[0].startRow;
}

void Board::print() const {
//    Position p1Pos = board.getPlayerPos(0);
//    Position p2Pos = board.getPlayerPos(1);

    std::string hat;
    hat.append(std::string(3, ' '));
    for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
        hat.append(' ' + std::string(1, 'a' + j) + std::string(2, ' '));
    }
    std::cout << hat << std::endl;

//    const std::vector<Position>& horizontalWalls = board.getHorizontalFences();
//    const std::vector<Position>& verticalWalls = board.getVerticalFences();

    for (int i = 0; i <= 2 * BOARD_SIDE_LENGTH; ++i) {
        std::string line;
        if (i == 0 or i == 2 * BOARD_SIDE_LENGTH) {
            line.append(std::string(2, ' ') + '+' + std::string(35, '-') + '+');
        } else {
            if (i % 2 == 0) {
                for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
                    if (j == 0) {
                        line.append("  |");
                    } else {
                        line.append("+");
                    }
                    //int wallRow = i / 2;
                    int wallRow = i / 2 - 1;
                    int wallCol = j;
                    if (std::find(getHorizontalFences().cbegin(), getHorizontalFences().cend(), Position(wallRow, wallCol)) != getHorizontalFences().cend()
                        || std::find(getHorizontalFences().cbegin(), getHorizontalFences().cend(), Position(wallRow, wallCol - 1)) != getHorizontalFences().cend()) {
                        line.append(std::string(3, '-'));
                    } else {
                        line.append(std::string(3, ' '));
                    }
                }
                line.append("|");
            } else {
                line.append(1, '1' + i/2);
                line.append("-|");
                for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
                    if (i == (getPlayerPos(0).row) * 2 + 1 && j == getPlayerPos(0).col) {
                        line.append(" X ");
                    } else if (i == (getPlayerPos(1).row) * 2 + 1 && j == getPlayerPos(1).col) {
                        line.append(" O ");
                    } else {
                        line.append(std::string(3 , ' '));
                    }
                    if (j == BOARD_SIDE_LENGTH - 1) {
                        line.append("|");
                    } else {
                        int wallRow = i / 2 - 1;
                        int rowCol = j;
                        if (std::find(getVerticalFences().cbegin(), getVerticalFences().cend(), Position(wallRow + 1, rowCol)) != getVerticalFences().cend()
                            || std::find(getVerticalFences().cbegin(), getVerticalFences().cend(), Position(wallRow, rowCol)) != getVerticalFences().cend()) {
                            line.append("|");
                        } else {
                            line.append(" ");
                        }
                    }
                }
            }
        }
        std::cout << line << std::endl;
    }

    std::cout << "Ход игрока: " << getActivePlayerIndex() + 1 << std::endl;
    std::cout << "Количество досок у игрока 1: " << getPlayerFences(0) << std::endl;
    std::cout << "Количество досок у игрока 2: " << getPlayerFences(1) << std::endl;
//    Engine engine;
//    double a = engine.evalPosition();
//    std::cout << "Оценка положения после этого хода: " << a;
//    std::cout << std::endl;
}

void Board::addFence(Position fence, bool horizontal) {
    int topLeft = fence.row * BOARD_SIDE_LENGTH + fence.col;
    int topRight = topLeft + 1;
    int bottomLeft = topLeft + BOARD_SIDE_LENGTH;
    int bottomRight = bottomLeft + 1;

    if (horizontal) {
        horizontalFences.push_back(fence);
        deleteVerticalEdge(topLeft, bottomLeft);
        deleteVerticalEdge(topRight, bottomRight);
    } else {
        verticalFences.push_back(fence);
        deleteHorizontalEdge(topLeft, topRight);
        deleteHorizontalEdge(bottomLeft, bottomRight);
    }
}

void Board::deleteVerticalEdge(int top, int bottom) {
    auto upstairsNeighbor = std::find(graph[bottom].begin(), graph[bottom].end(), top);
    if (upstairsNeighbor != graph[bottom].end()) {
        graph[bottom].erase(upstairsNeighbor);
    }

    auto downstairsNeighbor = std::find(graph[top].begin(), graph[top].end(), bottom);
    if (downstairsNeighbor != graph[top].end()) {
        graph[top].erase(downstairsNeighbor);
    }
}

void Board::deleteHorizontalEdge(int left, int right) {
    auto rightsideNeighbor = std::find(graph[left].begin(), graph[left].end(), right);
    if (rightsideNeighbor != graph[left].end()) {
        graph[left].erase(rightsideNeighbor);
    }

    auto leftsideNeighbor = std::find(graph[right].begin(), graph[right].end(), left);
    if (leftsideNeighbor != graph[right].end()) {
        graph[right].erase(leftsideNeighbor);
    }
}

void Board::setMaxPlayerIndex(int index) {
    maxPlayerIndex = index;
    players[0].isMaxPlayer = index == 0;
    players[1].isMaxPlayer = index == 1;
}
