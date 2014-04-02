#ifndef BOARD_H
#define BOARD_H

#include "Player.h"


const int MAX_BOARD_WIDTH = 13;
const int MAX_BOARD_HEIGHT = 7;
const int MAX_BOX_WIDTH = 3;
const int POLARIZE = 10;
const int MAX_MOVES = 49;
const int TREE_DEPTH = 3;


class Board
{
public:
	Board();
	Board(Board* b);
	virtual ~Board();
	void drawBoard();
	bool move(int row, int col, int player);
	bool dummyMove(int row, int col, int player);
	bool checkWin();
	int getPlayer();
	bool isFull();
	int getNumOpenMoves();
	Board* treeMove(int row, int col, int player);
	int getMarker(int row, int col);
	int togglePlayer();
	int getLastPlayer();
	int getLastRow();
	int getLastCol();
	void setP1(Player*);
	void setP2(Player*);
	Player* getActivePlayer();
	void setActivePlayer(Player*);
	void toggleActive();

private:
	int size;
	int freeSpace;
	int board[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH];
	int box[MAX_BOX_WIDTH][MAX_BOX_WIDTH];
	int lastRow;
	int lastCol;
	int lastPlayer;
	int movesPlayed;
	bool boardFull;
	int currPlayer;
	Player* activePlayer;
	Player* p1;
	Player* p2;

	void initBox();

	bool checkPattern(bool polarized);
	void polarize(int, int, int, int);
};

#endif //BOARD_H