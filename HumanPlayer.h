#pragma once
#include "player.h"
#include "Board.h"
class HumanPlayer :
	public Player
{
public:
	HumanPlayer(int _token, Board* b);
	~HumanPlayer(void);

	int parseColumn(char);

	virtual bool move();
	int getRow();
	int getCol();
	int getToken();

private:
	int row;
	int col;
	Board* board;
};

