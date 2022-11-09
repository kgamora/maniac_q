#include "board.hpp"

Board::Board() : p1Fences(10),
                 p2Fences(10),
                 p1(0, 4),
                 p2(8, 4),
                 graph(board_size)
{
    for(size_t i = 0; i < board_size; ++i) {
        uint8_t row = i / 9;
        uint8_t col = i % 9;
        if (col > 0) {
            graph[i].push_back(i - 1);
        }
        if (col < 8) {
            graph[i].push_back(i + 1);
        }
        if (row > 0) {
            graph[i].push_back(i - 9);
        }
        if (row < 8) {
            graph[i].push_back(i + 9);
        }
    }
}

void Board::addFence(Position fence, bool horizontal) {
//    assert(row >= 0 && row <= 8 && col >= 0 && col <= 0);

    uint8_t topLeft = fence.row * 9 + fence.col;
    uint8_t topRight = topLeft + 1;
    uint8_t bottomLeft = topLeft + 9;
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
