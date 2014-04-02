#pragma once

#include "player.h"
#include "Tree.h"


class AIPlayer :
	public Player
{
public:
	AIPlayer(int _token, Board* b);
	~AIPlayer(void);

	virtual bool move();
	void applyHeuristic(Node*);
	Node* minimax(Node*, bool);
	Node* getNextMove();
private:
	Tree t;
	Node* root;
	Board* board;
	Node* nextMove;
};

