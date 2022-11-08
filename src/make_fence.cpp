//
// Created by ksgamora on 08.11.22.
//
#include "make_fence.hpp"

bool checkFence (State currentState, bool horizontal, std::pair<uint8_t, uint8_t> position) {
    assert(std::find(currentState.getHorizontalFences().begin(), currentState.getHorizontalFences().end(), position) == currentState.getHorizontalFences().end());
    assert(std::find(currentState.getVerticalFences().begin(), currentState.getVerticalFences().end(), position) == currentState.getVerticalFences().end());
    if (horizontal) {
        std::pair<uint8_t, uint8_t> item1 = std::make_pair(position.first, position.second - 1);
        std::pair<uint8_t, uint8_t> item2 = std::make_pair(position.first, position.second + 1);
        assert(std::find(currentState.getHorizontalFences().begin(), currentState.getHorizontalFences().end(), item1) == currentState.getHorizontalFences().end());
        assert(std::find(currentState.getHorizontalFences().begin(), currentState.getHorizontalFences().end(), item2) == currentState.getHorizontalFences().end());
    } else {
        std::pair<uint8_t, uint8_t> item1 = std::make_pair(position.first - 1, position.second);
        std::pair<uint8_t, uint8_t> item2 = std::make_pair(position.first + 1, position.second);
        assert(std::find(currentState.getHorizontalFences().begin(), currentState.getHorizontalFences().end(), item1) == currentState.getHorizontalFences().end());
        assert(std::find(currentState.getHorizontalFences().begin(), currentState.getHorizontalFences().end(), item2) == currentState.getHorizontalFences().end());
    }
    return true;
}

State makeFence(State currentState, bool horizontal, std::pair<uint8_t, uint8_t> position) {
    checkFence(currentState, horizontal, position);
    uint8_t activePlayerFences = currentState.getActivePlayer() ? currentState.getP1Fences() : currentState.getP2Fences();
    assert(activePlayerFences > 0);
    currentState.addFence(horizontal, position);
    if (currentState.getActivePlayer()) {currentState.setP1Fences(activePlayerFences - 1);}
    else {currentState.setP2Fences(activePlayerFences - 1);}
    return currentState;
}

