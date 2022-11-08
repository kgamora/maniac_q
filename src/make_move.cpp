#include "make_move.hpp"

#include <vector>

State makeMove(State s, std::pair<uint8_t, uint8_t> dst) {

    uint8_t dstPosInGraph = (dst.first) * 9 + dst.second;

    uint8_t posInGraph = -1;
    uint8_t oppPosInGraph = -1;

    if (!s.getActivePlayer()) {
        posInGraph = s.getP1().first * 9 + s.getP1().second;
        oppPosInGraph = s.getP2().first * 9 + s.getP2().second;

    } else {
        posInGraph = s.getP2().first * 9 + s.getP2().second;
        oppPosInGraph = s.getP1().first * 9 + s.getP1().second;
    }

    auto graph = s.getGraph();
    std::vector<uint8_t> goodFields = graph[posInGraph];

    // если противник не рядом с нами
    if(std::find(goodFields.begin(), goodFields.end(), oppPosInGraph) == goodFields.end()) {
        // если желаемое поле рядом с нами
        if(std::find(goodFields.begin(), goodFields.end(), dstPosInGraph) != goodFields.end()) {
            s.setP1(dst);
            return s;
        } else {
            // если противника рядом нет и мы хотим пойти на дальние клетки, то нельзя
            assert(false);
        }
    }

    // если противник рядом с нами

    if (oppPosInGraph == dstPosInGraph) {
        //если пытаемся встать на место соперника
        assert(false);
    }

    // если ходим на свободные клетки рядом
    if(std::find(goodFields.begin(), goodFields.end(), dstPosInGraph) != goodFields.end()) {
        if (!s.getActivePlayer()) {
            s.setP1(dst);
            return s;
        }
        s.setP2(dst);
        return s;
    }

    //если хотим куда-то хитро перейти
    //встаем на место соперника и пробуем оттуда перейти на нужную клетку

    if (!s.getActivePlayer()) {
        s.setP1(s.getP2());
        return makeMove(s, dst);
    }
    s.setP2(s.getP1());
    return makeMove(s, dst);
}