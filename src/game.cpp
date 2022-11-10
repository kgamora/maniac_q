//
// Created by ksgamora on 10.11.22.
//
#include "game.hpp"

Game::Game(Mode mode, BoardInit boardInit, std::string path, int player) {
    this->mode = mode;
    if (boardInit == fromFile) {
        std::fstream fileNotation(path, fileNotation.in);
        currentState = Board(fileNotation);
    }
    if (mode == engineInteractive) {
        currentState.setMaxPlayerIndex(player);
    } else if (mode == play) {
        currentState.setMaxPlayerIndex((player + 1) % 2);
    }
}

void Game::run() {
    if (mode == Mode::engine) {
        runEngine();
    } else if (mode == Mode::engineInteractive) {
        runEngineInteractive();
    } else if (mode == Mode::play) {
        runPlay();
    }
}

void Game::runEngine() {
    std::string result = getBestMoveOnDepth(currentState, 1);
    std::cout << result;
}

void Game::runEngineInteractive() {
    while (!Validation::isFinished(currentState)) {
        bool playerTurn = currentState.getActivePlayerIndex() == currentState.getMaxPlayerIndex();
        std::string turn;
        std::string prompt = playerTurn ? PLAYER_MOVE_PROMPT : PLAYER2_MOVE_PROMPT;
        if (playerTurn) {
            turn = getBestMoveOnDepth(currentState, 1);
            std::cout << BEST_MOVE << turn << std::endl;
        }
        std::cout << prompt << std::endl;
        std::cin >> turn;
        if (!Validation::checkTurn(turn)) {
            std::cout << BAD_TURN << std::endl;
            continue;
        }
        currentState = makeTurn(currentState, turn);
        printBoard(currentState);
    }
}

void Game::runPlay() {
    while (!Validation::isFinished(currentState)) {
        bool playerTurn = currentState.getActivePlayerIndex() != currentState.getMaxPlayerIndex();
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
            turn = getBestMoveOnDepth(currentState, 1);
            std::cout << BOT_MOVES << turn << std::endl;
        }
        currentState = makeTurn(currentState, turn);
        printBoard(currentState);
    }
}

