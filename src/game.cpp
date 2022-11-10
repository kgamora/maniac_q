//
// Created by ksgamora on 10.11.22.
//
#include "game.hpp"
#include "validation.hpp"
#include "make_move.hpp"
#include "make_fence.hpp"

Game::Game(Mode mode, BoardInit boardInit, const std::string& path, int player) : mode_(mode) {
    if (boardInit == fromFile) {
        std::fstream fileNotation(path, std::fstream::in);
        currentState_ = Board(fileNotation);
    }
    if (mode == interactive) {
        currentState_.setMaxPlayerIndex(player);
    } else if (mode == play) {
        currentState_.setMaxPlayerIndex((player + 1) % 2);
    }
}

void Game::run() {
    if (mode_ == Mode::engine) {
        runEngine();
    } else if (mode_ == Mode::interactive) {
        runEngineInteractive();
    } else if (mode_ == Mode::play) {
        runPlay();
    }
}

void Game::runEngine() {
    auto [result_str, result_double] = eng_.min_max(currentState_, 1, true);
    std::cout << result_str;
}

void Game::runEngineInteractive() {
    while (!Validation::isGameFinished(currentState_)) {
        bool playerTurn = currentState_.getActivePlayerIndex() == currentState_.getMaxPlayerIndex();
        std::string turn;
        std::string prompt = playerTurn ? PLAYER_MOVE_PROMPT : PLAYER2_MOVE_PROMPT;
        if (playerTurn) {
            auto [turn_str, turn_double] = eng_.min_max(currentState_, 1, true);
            std::cout << BEST_MOVE << turn_str << std::endl;
        }
        std::cout << prompt << std::endl;
        std::cin >> turn;
        if (!Validation::checkTurn(currentState_, turn)) {
            std::cout << BAD_TURN << std::endl;
            continue;
        }
        currentState_ = makeTurn(currentState_, turn);
        printBoard(currentState_);
    }
}

void Game::runPlay() {
    while (!Validation::isGameFinished(currentState_)) {
        bool playerTurn = currentState_.getActivePlayerIndex() != currentState_.getMaxPlayerIndex();
        std::string turn;
        std::string prompt = PLAYER_MOVE_PROMPT;
        if (playerTurn) {
            std::cout << prompt << std::endl;
            std::cin >> turn;
            if (!Validation::checkTurn(currentState_, turn)) {
                std::cout << BAD_TURN << std::endl;
                continue;
            }
        } else {
            auto [turn_str, turn_double] = eng_.min_max(currentState_, 1, true);
            std::cout << BOT_MOVES << turn_str << std::endl;
        }
        currentState_ = makeTurn(currentState_, turn);
        printBoard(currentState_);
    }
}

Board Game::makeTurn(const Board& state, const std::string& turn) {
    int row = turn[1] - '1';
    int col = turn[0] - 'a';
    if (turn.size() == 2) {
        return makeMove(state, {row, col});
    } else {
        return makeFence(state, {row, col}, turn[2] == 'h');
    }
}

