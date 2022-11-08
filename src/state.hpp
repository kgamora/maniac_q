#pragma once
#include <stdint.h>
#include <vector>

class State {
public:
    void addFence (bool, std::pair<uint8_t, uint8_t>);
    void setP1(uint8_t, uint8_t);
    void setP2(uint8_t, uint8_t);
    void setP1Walls(uint8_t);
    void setP2Walls(uint8_t);
    uint8_t getP1Walls() const;
    uint8_t getP2Walls() const;
    void setActivePlayer(bool);
    bool getActivePlayer() const;
    std::pair<uint8_t, uint8_t> getP1() const;
    std::pair<uint8_t, uint8_t> getP2() const;
};