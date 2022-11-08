#pragma once
#include <cstdlib>
#include <vector>

class State {
public:
    State();
    void addFence(bool horizontal, uint8_t row, uint8_t col);
    const std::vector<std::vector<uint8_t>>& getGraph();
    void setP1(uint8_t row, uint8_t col);
    void setP2(uint8_t row, uint8_t col);
    std::pair<uint8_t, uint8_t> getP1() const;
    std::pair<uint8_t, uint8_t> getP2() const;
    void dirtyPrint() const;
    void setP1Fences(uint8_t n);
    void setP2Fences(uint8_t n);

private:
    uint8_t board_size;
    std::vector<std::vector<uint8_t>> graph;
    std::pair<uint8_t, uint8_t> p1;
    std::pair<uint8_t, uint8_t> p2;
    uint8_t p1Fences;
    uint8_t p2Fences;
};
