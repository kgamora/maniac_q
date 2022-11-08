#include "state.h"
#include <cstdlib>
#include <vector>
#include <iostream>

State::State() : board_size(81), p1Fences(10), p2Fences(10) {
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

// void State::setP1Fences(uint8_t n) {}

std::pair<uint8_t, uint8_t> State::getP1() const {
    return p1;
}

std::pair<uint8_t, uint8_t> State::getP2() const {
    return p2;
}

void State::setP1(uint8_t row, uint8_t col) {
    p1 = std::pair<uint8_t, uint8_t>(row, col);
}

void State::setP2(uint8_t row, uint8_t col) {
    p2 = std::pair<uint8_t, uint8_t>(row, col);
}

void State::addFence(bool horizontal, uint8_t row, uint8_t col) {
    assert(row >= 1 && row <= 9 && col >= 1 && col <= 9);

    row--;
    col--;
    uint8_t topLeft = row * 9 + col;
    uint8_t topRight = topLeft + 1;
    uint8_t bottomLeft = topLeft + 9;
    uint8_t bottomRight = bottomLeft + 1;

    if (horizontal) {
        auto bottomLeftNeighbor = std::find(graph[topLeft].begin(), graph[topLeft].end(),bottomLeft);
        graph[topLeft].erase(bottomLeftNeighbor);

        auto bottomRightNeighbor = std::find(graph[topRight].begin(), graph[topRight].end(),bottomRight);
        graph[topRight].erase(bottomRightNeighbor);

        auto topLeftNeighbor = std::find(graph[bottomLeft].begin(), graph[bottomLeft].end(),topLeft);
        graph[bottomLeft].erase(topLeftNeighbor);

        auto topRightNeighbor = std::find(graph[bottomRight].begin(), graph[bottomRight].end(),topRight);
        graph[bottomRight].erase(topRightNeighbor);

        return;
    }

    auto topRightNeighbor = std::find(graph[topLeft].begin(), graph[topLeft].end(), topRight);
    graph[topLeft].erase(topRightNeighbor);

    auto topLeftNeighbor = std::find(graph[topRight].begin(), graph[topRight].end(), topLeft);
    graph[topRight].erase(topLeftNeighbor);

    auto bottomRightNeighbor = std::find(graph[bottomLeft].begin(), graph[bottomLeft].end(), bottomRight);
    graph[bottomLeft].erase(bottomRightNeighbor);

    auto bottomLeftNeighbor = std::find(graph[bottomRight].begin(), graph[bottomRight].end(), bottomLeft);
    graph[bottomRight].erase(bottomLeftNeighbor);

    return;
}


void State::dirtyPrint() const {
    for (size_t i = 0; i < graph.size(); ++i) {
        std::cout << "Vertex = " << i << ": [";
        for (size_t j = 0; j < graph[i].size(); ++j) {
            std::cout << unsigned (graph[i][j]) << ' ';
        }
       std::cout << "]" << std::endl;
    }
}

const std::vector<std::vector<uint8_t>>& State::getGraph() {
    return graph;
}