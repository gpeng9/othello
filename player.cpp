#include "player.hpp"
#include <iostream>
using namespace std;
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
     opponent = WHITE;
     player = BLACK;
     board1 = new Board();
     
    
     /*
     * 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
 /*
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     
     Move* move = new Move(0,0);
      if (opponentsMove == NULL)
      {
		 for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				move->setX(i);
				move->setY(j);
            if (board1->checkMove(move, player)) 
            {
				board1->doMove(move,player);
				 
				return move;
			}
			}
		}
	  }
	  else 
	  {
		  board1->doMove(opponentsMove ,opponent);
      }
      
      if(board1->hasMoves(player) == false)
      {
		  return NULL;
	  }
	  else 
	  {
		  for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				
				move->setX(i);
				move->setY(j);
				if (board1->checkMove(move, player)) 
				{
					board1->doMove(move,player);
					
					return move;
				}
			}
		}
	}
	return NULL;
}
 */     
   Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     Move* move = new Move(0,0);
      if (opponentsMove == NULL)
      {
		 for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				move->setX(i);
				move->setY(j);
            if (board1->checkMove(move, player)) 
            {
				board1->doMove(move,player);
				 
				return move;
			}
			}
		}
	  }
	  else 
	  {
		  board1->doMove(opponentsMove ,opponent);
      }
      
      if(board1->hasMoves(player) == false)
      {
		  return NULL;
	  }
	  else 
	  {
		  for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				
				move->setX(i);
				move->setY(j);
				if (board1->checkMove(move, player)) 
				{
					board1->doMove(move,player);
					
					return move;
				}
			}
		}
	}
	return NULL;
}
int Player::heuristic(Board * boardCopy, Move* playerMove)
{
	int score = boardCopy->count(opponent) - boardCopy->count(player);
	if (playerMove->x == 0 || playerMove->x == 7)
	{
		if (playerMove->y == 0 || playerMove->y == 7)
		{
			score *= 3;
		}
		else 
			score *= 2;
	}
	if (playerMove->x == 1 || playerMove->x == 6 || playerMove->y == 1 || playerMove->y == 6)
	{
		score *= -3;
	}
	return score;
}
	
 


