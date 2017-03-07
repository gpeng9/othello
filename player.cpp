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
    testingMinimax = true;
     opponent = WHITE;
     player = side;
     if (side == BLACK)
     {
		 opponent = WHITE;
	 }
	 else
		opponent = WHITE;
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
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
     Move* move = new Move(-1,-1);
     Move* best_move = new Move(-1,-1);
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
      
      int min = -1000;
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
					Board* board2 = board1 -> copy();
					
					board2->doMove(move,player);
					if (board2->hasMoves(player)==false)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						continue;
					}
					int score = Minimax(board2, move,2, player);
					if (heuristic(board2, move) > min)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						min = score;
					}
					delete board2;
				}
			}
		}
		board1 -> doMove(best_move,player);
		return best_move;
	}
	
}

int Player::heuristic(Board * boardCopy, Move* playerMove)
{
	int score = boardCopy->count(player) - boardCopy->count(opponent);
	if (playerMove->x == 0 || playerMove->x == 7)
	{
		if (playerMove->y == 0 || playerMove->y == 7)
		{
			score += 5;
		}
		else
			score += 3;
	}
	
	else if (playerMove->y == 0 || playerMove->y == 7)
	{
		score += 3;
	}
	
	if (playerMove->x == 1 || playerMove->x == 6 || playerMove->y == 1 || playerMove->y == 6)
	{
		score -= 5;
	}
	
	return score;
}      

int Player:: Minimax (Board * boardCopy, Move* playerMove, int depth, Side maximizingPlayer)
{
	Move* move = new Move(-1,-1);
	Move* best_move  = new Move(-1,-1);
	int totalScore = 0;
	if (depth == 0 || boardCopy->hasMoves(maximizingPlayer) == false)
	{
		return heuristic(boardCopy, playerMove);
	}
	if (maximizingPlayer == player)
	{
		int bestValue = -10000;
		 for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				move->setX(i);
				move->setY(j);
				if (board1->checkMove(move, opponent)) 
				{
				
					Board* board2 = board1 -> copy();
					board2->doMove(playerMove, player);
					board2->doMove(move,opponent);
					if (board2->hasMoves(opponent)==false)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						continue;
					}
					int score = Minimax(board2, move, depth - 1, opponent);
					
					
					if (score > bestValue)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						bestValue = score;
					}
					delete board2;
			}
		}
	}
		Board* board2 = board1 -> copy();
		board2->doMove(playerMove, player);		
		board2->doMove(move,opponent);
		int totalScore = heuristic(board2, best_move);
		delete board2;
		return  totalScore;
	}
	else 
	{
		int scoreValue = 10000;
		for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				move->setX(i);
				move->setY(j);
				if (board1->checkMove(move, player)) 
				{
					
					Board* board2 = board1 -> copy();
					board2->doMove(playerMove, opponent);
					board2->doMove(move,player);
					if (board2->hasMoves(player)==false)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						continue;
					}
					totalScore = Minimax(board2, move, depth - 1, player);
					
					if (totalScore < scoreValue)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						scoreValue = totalScore;
					}
					delete board2;
				}
			}
		}
		Board* board2 = board1 -> copy();
		board2->doMove(playerMove, opponent);		
		board2->doMove(move,player);
		int totalScore = heuristic(board2, best_move);
		delete board2;
		return  totalScore;
	}
}
	/**
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
	return NULL;*/
