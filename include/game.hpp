#pragma once

#include "board.hpp"
#include "engine.hpp"

#include <fstream>

//#define PLAYER_MOVE_PROMPT "Введите ваш ход: "
//#define PLAYER2_MOVE_PROMPT "Введите ход противника: "
//#define BEST_MOVE "Движок рекомендует ход: "
//#define BAD_TURN "Незаконный или невалидный ход: "
//#define BOT_MOVES "Бот сделал ход: "
#define SEARCH_DEPTH 3

enum Mode {
    play,
    interactive,
    engine
};

enum InitType {
    fromFile,
    fromStdIn
};

class Game {
public:
    Game(Mode mode, InitType init, int player, const std::string& path);
    void run();

private:
    void runEngine();
    void runEngineInteractive();
    void runPlay();

    Mode mode_;
    Board currentState_;
    Engine eng_;
};