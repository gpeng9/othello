#include "player.hpp"
#include <iostream>
#include <cmath>
using namespace std;
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;
     player = side;
     if (side == BLACK)
     {
		 opponent = WHITE;
	 }
	 else
		opponent = BLACK;
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
      
      int min = -100001;
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
					if (board2->hasMoves(opponent)==false)
					{
						
						int s = heuristic(board2, move, opponent);
						if (s > min)
						{
							best_move->setX(move->x);
							best_move->setY(move->y);
							min = s;
						}
						
						continue;
					}
					int score = alphabeta(board2, move,3, -10000,10000, player);
					if (score > min)
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

int Player::heuristic(Board * boardCopy, Move* playerMove, Side side)
{
	int score = boardCopy->count(player) - boardCopy->count(opponent);
	if (side == player)
	{
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
	}
	else
	{
		if (playerMove->x == 0 || playerMove->x == 7)
		{
			if (playerMove->y == 0 || playerMove->y == 7)
			{
				score -= 8;
			}
			else
				score -= 6;
		}
		
		else if (playerMove->y == 0 || playerMove->y == 7)
		{
			score -= 5;
		}
		
		if (playerMove->x == 1 || playerMove->x == 6 || playerMove->y == 1 || playerMove->y == 6)
		{
			score += 5;
		}
	}
	return score;
}      

int Player:: alphabeta (Board * boardCopy, Move* playerMove, int depth, int alpha, int beta, Side maximizingPlayer)
{
	Move* move = new Move(3,4);
	//Move* best_move  = new Move(3,4);
	//int totalScore = 0;
	int bestValue = -10000;
	int scoreValue = 10000;
	if (depth == 0 || boardCopy->hasMoves(maximizingPlayer) == false)
	{
		int score = heuristic(boardCopy, playerMove, maximizingPlayer);
		return score;
	}
	if (maximizingPlayer == player)
	{
		//int bestValue = -10000;
		 for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				move->setX(i);
				move->setY(j);
				if (board1->checkMove(move, opponent)) 
				{
				
					Board* board2 = boardCopy -> copy();
					board2->doMove(playerMove, player);
					board2->doMove(move,opponent);
					
					bestValue = max(bestValue,alphabeta(board2, move, depth - 1, alpha,beta, opponent));
					alpha = max(alpha, bestValue);
					
					if (beta <= alpha)
					{
						break;
					}
					delete board2;
			}
		}
	}
		
		return bestValue;
	}
	else 
	{
		//int scoreValue = 10000;
		for (int i = 0; i < 8; i++) 
		  {
			for (int j = 0; j < 8; j++) 
			{
				move->setX(i);
				move->setY(j);
				if (board1->checkMove(move, player)) 
				{
					
					Board* board2 = boardCopy -> copy();
					board2->doMove(playerMove, opponent);
					board2->doMove(move,player);
					
					scoreValue = min(scoreValue,alphabeta(board2, move, depth - 1, alpha,beta, player));
					beta = min(beta, scoreValue);
					
					if (beta <= alpha)
					{
						break;
					}
					delete board2;
				}
			}
		}
		
		return scoreValue;
	}
}


/**
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     
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
					if (score > min)
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
	Move* move = new Move(3,4);
	Move* best_move  = new Move(3,4);
	int totalScore = 0;
	if (depth == 0 || boardCopy->hasMoves(maximizingPlayer) == false)
	{
		int score = boardCopy->count(player) - boardCopy->count(opponent);
		return score;
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
				
					Board* board2 = boardCopy -> copy();
					board2->doMove(playerMove, player);
					board2->doMove(move,opponent);
					
					totalScore = Minimax(board2, move, depth - 1, opponent);
					
					
					if (totalScore > bestValue)
					{
						best_move->setX(move->x);
						best_move->setY(move->y);
						bestValue = totalScore;
					}
					delete board2;
			}
		}
	}
		
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
					
					Board* board2 = boardCopy -> copy();
					board2->doMove(playerMove, opponent);
					board2->doMove(move,player);
					
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
		
		return  totalScore;
	}
}
*/
/**
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     
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
					int score = heuristic(board2, move);
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
*/
