#include "state.h"
#include <cstdlib>
#include <vector>
#include <iostream>

State::State() : board_size(81),
                 p1Fences(10),
                 p2Fences(10),
                 p1(std::pair<uint8_t, uint8_t>(0, 4)),
                 p2(std::pair<uint8_t, uint8_t>(8, 4))
{
    graph = std::vector<std::vector<uint8_t>>(board_size);

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

std::pair<uint8_t, uint8_t> State::getP1() const {
    return p1;
}

std::pair<uint8_t, uint8_t> State::getP2() const {
    return p2;
}

void State::setP1(std::pair<uint8_t, uint8_t> field) {
    p1 = std::make_pair(field.first - 1, field.second - 1);
}

void State::setP2(std::pair<uint8_t, uint8_t> field) {
    p2 = std::make_pair(field.first - 1, field.second - 1);
}

void State::addFence(bool horizontal, std::pair<uint8_t, uint8_t> fence) {

    uint8_t row = fence.first;
    uint8_t col = fence.second;

    assert(row >= 1 && row <= 9 && col >= 1 && col <= 9);

    row--;
    col--;
    uint8_t topLeft = row * 9 + col;
    uint8_t topRight = topLeft + 1;
    uint8_t bottomLeft = topLeft + 9;
    uint8_t bottomRight = bottomLeft + 1;

    if (horizontal) {
        horizontalFences.push_back(fence);
        deleteVerticalEdge(topLeft, bottomLeft);
        deleteVerticalEdge(topRight, bottomRight);
        return;
    }

    verticalFences.push_back(fence);
    deleteHorizontalEdge(topLeft, topRight);
    deleteHorizontalEdge(bottomLeft, bottomRight);
    return;
}

void State::deleteVerticalEdge(uint8_t top, uint8_t bottom) {
    auto upstairsNeighbor = std::find(graph[bottom].begin(), graph[bottom].end(), top);
    if (upstairsNeighbor != graph[bottom].end()) {
        graph[bottom].erase(upstairsNeighbor);
    }

    auto downstairsNeighbor = std::find(graph[top].begin(), graph[top].end(), bottom);
    if (downstairsNeighbor != graph[top].end()) {
        graph[top].erase(downstairsNeighbor);
    }
}

void State::deleteHorizontalEdge(uint8_t left, uint8_t right) {
    auto rightsideNeighbor = std::find(graph[left].begin(), graph[left].end(), right);
    if (rightsideNeighbor != graph[left].end()) {
        graph[left].erase(rightsideNeighbor);
    }

    auto leftsideNeighbor = std::find(graph[right].begin(), graph[right].end(), left);
    if (leftsideNeighbor != graph[right].end()) {
        graph[right].erase(leftsideNeighbor);
    }
}

void State::dirtyPrint() const {
    for (size_t i = 0; i < graph.size(); ++i) {
        std::cout << "Vertex = " << i << ": [";
        if (graph[i].size() != 0) {
            for (size_t j = 0; j < graph[i].size(); ++j) {
                std::cout << unsigned(graph[i][j]) << ' ';
            }
        }
       std::cout << "]" << std::endl;
    }
}

const std::vector<std::vector<uint8_t>>& State::getGraph() {
    return graph;
}