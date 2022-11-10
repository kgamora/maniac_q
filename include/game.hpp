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

enum Mode {
    play,
    engineInteractive,
    engine
};

enum BoardInit {
    fromFile,
    fromStart
};

class Game {
public:

    Game(Mode, BoardInit, std::string, int);

    void run();

private:
    void runEngine();
    void runEngineInteractive();
    void runPlay();
    Mode mode;
    Board currentState;
};