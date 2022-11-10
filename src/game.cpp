//
// Created by ksgamora on 10.11.22.
//
#include "game.hpp"
#include "validation.hpp"

Game::Game(Mode mode, InitType init, int player, const std::string& path) : mode_(mode), currentState_(player) {
    if (init == fromFile) {
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
    auto [result_str, result_double] = eng_.minMax(currentState_, SEARCH_DEPTH, true);
    std::cout << result_str;
}

void Game::runEngineInteractive() {
    while (!Validation::isGameFinished(currentState_)) {
        bool playerTurn = currentState_.getActivePlayerIndex() == currentState_.getMaxPlayerIndex();
        std::string turn;
        std::string prompt = playerTurn ? "Введите ваш ход: " : "Введите ход противника: ";
        if (playerTurn) {
            auto [turn_str, turn_double] = eng_.minMax(currentState_, SEARCH_DEPTH, true);
            std::cout << "Движок рекомендует ход: " << turn_str << std::endl;
        }
        std::cout << prompt << std::endl;
        std::cin >> turn;
        if (!Validation::checkTurn(currentState_, turn)) {
            std::cout << "Незаконный или невалидный ход: " << std::endl;
            continue;
        }
        currentState_ = Engine::makeTurn(currentState_, turn);
        currentState_.print();
    }
}

void Game::runPlay() {
    while (!Validation::isGameFinished(currentState_)) {
        bool playerTurn = currentState_.getActivePlayerIndex() != currentState_.getMaxPlayerIndex();
        std::string turn;
//        std::string prompt = "Введите ваш ход: ";
        if (playerTurn) {
            std::cout << "Введите ваш ход: " << std::endl;
            std::cin >> turn;
            if (!Validation::checkTurn(currentState_, turn)) {
                std::cout << "Незаконный или невалидный ход: " << std::endl;
                continue;
            }
        } else {
            auto [turn_str, turn_double] = eng_.minMax(currentState_, SEARCH_DEPTH, true);
            turn = turn_str;
            std::cout << "Бот сделал ход: " << turn_str << std::endl;
        }
        currentState_ = Engine::makeTurn(currentState_, turn);
        currentState_.print();
    }
}
