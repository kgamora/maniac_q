#pragma once

#include "board.hpp"
#include "fstream"
#include "engine.hpp"
#include "read_write.hpp"

#define PLAYER_MOVE_PROMPT "Введите ваш ход: "
#define PLAYER2_MOVE_PROMPT "Введите ход противника: "
#define BEST_MOVE "Движок рекомендует ход: "
#define BAD_TURN "Незаконный или невалидный ход: "
#define BOT_MOVES "Бот сделал ход: "
#define SEARCH_DEPTH 2

enum Mode {
    play,
    interactive,
    engine
};

enum BoardInit {
    fromFile,
    fromStdIn
};

class Game {
public:

    Game(Mode, BoardInit, const std::string&, int);
    void run();

private:
    void runEngine();
    void runEngineInteractive();
    void runPlay();
    Board makeTurn(const Board& state, const std::string& turn);

    Mode mode_;
    Board currentState_;
    Engine eng_;
};