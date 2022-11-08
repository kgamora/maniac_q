#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <algorithm>

class State {
public:
    State();
    void addFence(bool horizontal, std::pair<uint8_t, uint8_t> fence);
    const std::vector<std::vector<uint8_t>>& getGraph();
    void setP1(std::pair<uint8_t, uint8_t> field);
    void setP2(std::pair<uint8_t, uint8_t> field);
    std::pair<uint8_t, uint8_t> getP1() const;
    std::pair<uint8_t, uint8_t> getP2() const;
    std::vector<std::pair<uint8_t, uint8_t>> getHorizontalFences() const;
    std::vector<std::pair<uint8_t, uint8_t>> getVerticalFences() const;
    void dirtyPrint() const;
    void setP1Fences(uint8_t n);
    void setP2Fences(uint8_t n);
    uint8_t getP1Fences();
    uint8_t getP2Fences();
    void setActivePlayer(bool);
    bool getActivePlayer();

private:
    uint8_t board_size;
    std::vector<std::vector<uint8_t>> graph;
    std::vector<std::pair<uint8_t, uint8_t>> horizontalFences;
    std::vector<std::pair<uint8_t, uint8_t>> verticalFences;
    std::pair<uint8_t, uint8_t> p1; // [0, 0] - [8, 8]
    std::pair<uint8_t, uint8_t> p2; // [0, 0] - [8, 8]
    uint8_t p1Fences;
    uint8_t p2Fences;
    bool activePlayer;
    void deleteVerticalEdge(uint8_t top, uint8_t bottom);
    void deleteHorizontalEdge(uint8_t left, uint8_t right);
};
