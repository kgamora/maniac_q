#include "board.hpp"

Board::Board() : p1Fences(FENCE_COUNT),
                 p2Fences(FENCE_COUNT),
                 p1(0, BOARD_SIDE_LENGTH / 2),
                 p2(BOARD_SIDE_LENGTH, BOARD_SIDE_LENGTH / 2),
                 graph(board_size),
                 activePlayer(1)
{
    for(size_t i = 0; i < board_size; ++i) {
        uint8_t row = i / BOARD_SIDE_LENGTH;
        uint8_t col = i % BOARD_SIDE_LENGTH;
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

Board::Board(std::istream& is) {
    std::string gamePosition;

    //horizontal wall positions
    is >> gamePosition;
    if (gamePosition[0] != '/') {
        for (char c : gamePosition) {
            uint8_t col = cols.at(c++);
            uint8_t row = c - '0';
            addFence(Position(row, col), true);
        }
        is >> gamePosition;
    }

    //vertical wall positions
    is >> gamePosition;
    if (gamePosition[0] != '/') {
        for (char c : gamePosition) {
            uint8_t col = cols.at(c++);
            uint8_t row = c - '0';
            addFence({row, col}, false);
        }
        is >> gamePosition;
    }

    //p1 position
    is >> gamePosition;
    uint8_t row = gamePosition[1] - '0';
    uint8_t col = cols.at(gamePosition[0]);
    setP1({row, col});

    //p2 position
    std::cin >> gamePosition;
    row = gamePosition[1] - '0';
    col = cols.at(gamePosition[0]);
    setP2({row, col});

    is >> gamePosition;

    //walls
    is >> gamePosition;
    setP1Fences(gamePosition[0] - '0');
    is >> gamePosition;
    setP2Fences(gamePosition[0] - '0');

    is >> gamePosition;

    //who's turn
    is >> gamePosition;
    setActivePlayer(gamePosition[0]);
}

void Board::addFence(Position fence, bool horizontal) {
//    assert(row >= 0 && row <= 8 && col >= 0 && col <= 0);

    uint8_t topLeft = fence.row * BOARD_SIDE_LENGTH + fence.col;
    uint8_t topRight = topLeft + 1;
    uint8_t bottomLeft = topLeft + BOARD_SIDE_LENGTH;
    uint8_t bottomRight = bottomLeft + 1;

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

void Board::deleteVerticalEdge(uint8_t top, uint8_t bottom) {
    auto upstairsNeighbor = std::find(graph[bottom].begin(), graph[bottom].end(), top);
    if (upstairsNeighbor != graph[bottom].end()) {
        graph[bottom].erase(upstairsNeighbor);
    }

    auto downstairsNeighbor = std::find(graph[top].begin(), graph[top].end(), bottom);
    if (downstairsNeighbor != graph[top].end()) {
        graph[top].erase(downstairsNeighbor);
    }
}

void Board::deleteHorizontalEdge(uint8_t left, uint8_t right) {
    auto rightsideNeighbor = std::find(graph[left].begin(), graph[left].end(), right);
    if (rightsideNeighbor != graph[left].end()) {
        graph[left].erase(rightsideNeighbor);
    }

    auto leftsideNeighbor = std::find(graph[right].begin(), graph[right].end(), left);
    if (leftsideNeighbor != graph[right].end()) {
        graph[right].erase(leftsideNeighbor);
    }
}
