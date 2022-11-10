#include "board.hpp"

Board::Board() :
//                 p1Fences(FENCE_COUNT),
//                 p2Fences(FENCE_COUNT),
//                 p1(0, BOARD_SIDE_LENGTH / 2),
//                 p2(BOARD_SIDE_LENGTH - 1, BOARD_SIDE_LENGTH / 2),
                 players(2),
                 graph(board_size),
                 activePlayerIndex(0)
{
    // 0 - human
    // 1 - agent
    players[0].pos = {0, BOARD_SIDE_LENGTH / 2};
    players[0].fenceCount = FENCE_COUNT;
    players[0].isMaxPlayer = false;
    players[1].pos = {BOARD_SIDE_LENGTH - 1, BOARD_SIDE_LENGTH / 2};
    players[1].fenceCount = FENCE_COUNT;
    players[1].isMaxPlayer = true;
    maxPlayerIndex = 1;

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

Board::Board(std::istream& is) : Board() {
    std::string gamePosition;

    //horizontal wall positions
    is >> gamePosition;

    if (gamePosition[0] != '/') {
        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
            uint8_t col = *i - 'a';
            i++;
            uint8_t row = *i - '1';
            addFence(Position(row, col), true);
        }
        is >> gamePosition;
    }

    //vertical wall positions
    is >> gamePosition;

    if (gamePosition[0] != '/') {
        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
            uint8_t col = *i - 'a';
            i++;
            uint8_t row = *i - '1';
            addFence(Position(row, col), false);
        }
        is >> gamePosition;
    }

    //p1 position
    is >> gamePosition;
    uint8_t row = gamePosition[1] - '1';
    uint8_t col = gamePosition[0] - 'a';
//    setP1({row, col});
    players[0].pos = {row, col};

    //p2 position
    //p2 position
    is >> gamePosition;
    row = gamePosition[1] - '1';
    col = gamePosition[0] - 'a';
//    setP2({row, col});
    players[1].pos = {row, col};

    is >> gamePosition;

    //walls
    is >> gamePosition;
//    setP1Fences(gamePosition[0] - '0');
    players[0].fenceCount = gamePosition[0] - '0';
    is >> gamePosition;
//    setP2Fences(gamePosition[0] - '0');
    players[1].fenceCount = gamePosition[0] - '0';

    is >> gamePosition;

    //who's turn
    is >> gamePosition;
//    setActivePlayer(gamePosition[0]);
    activePlayerIndex = gamePosition[0] - '1';
    maxPlayerIndex = activePlayerIndex;

    players[0].isMaxPlayer = activePlayerIndex == 0;
    players[1].isMaxPlayer = activePlayerIndex == 1;
    players[0].startRow = 0;
    players[1].startRow = BOARD_SIDE_LENGTH - 1;
    players[0].targetRow = players[1].startRow;
    players[1].targetRow = players[0].startRow;
}

void Board::addFence(Position fence, bool horizontal) {
//    assert(fence.row >= 0 && fence.row <= 7 && fence.col >= 0 && fence.col <= 7);

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
}
