#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
	Side player;
	Side opponent;
	Board* board1;
	int Minimax (Board * boardCopy, Move* playerMove, int depth, Side maximizingPlayer);
    Move *doMove(Move *opponentsMove, int msLeft);
	int heuristic(Board * boardCopy, Move* playerMove, Side side);
	int alphabeta (Board * boardCopy, Move* playerMove, int depth, int alpha, int beta, Side maximizingPlayer);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
