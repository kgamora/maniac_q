//
// Created by ksgamora on 10.11.22.
//
#include "game.hpp"
#include "validation.hpp"

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
    std::string result = getBestMoveOnDepth(currentState_, 1);
    std::cout << result;
}

void Game::runEngineInteractive() {
    while (!Validation::isGameFinished(currentState_)) {
        bool playerTurn = currentState_.getActivePlayerIndex() == currentState_.getMaxPlayerIndex();
        std::string turn;
        std::string prompt = playerTurn ? PLAYER_MOVE_PROMPT : PLAYER2_MOVE_PROMPT;
        if (playerTurn) {
            turn = getBestMoveOnDepth(currentState_, 1);
            std::cout << BEST_MOVE << turn << std::endl;
        }
        std::cout << prompt << std::endl;
        std::cin >> turn;
        if (!Validation::checkTurn(turn)) {
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
            if (!Validation::checkTurn(turn)) {
                std::cout << BAD_TURN << std::endl;
                continue;
            }
        } else {
            turn = getBestMoveOnDepth(currentState_, 1);
            std::cout << BOT_MOVES << turn << std::endl;
        }
        currentState_ = makeTurn(currentState_, turn);
        printBoard(currentState_);
    }
}

