#include "Board.h"
#include <iostream>

using namespace std;



//Initialize the board
Board::Board()
{
	boardFull = false;
	movesPlayed = 0;
	//Create an empty board
	int tempBoard[MAX_BOARD_HEIGHT][MAX_BOARD_WIDTH] = 
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1,
		-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1,
		-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1,
		-1, -1, -1, -1, 0, 0, 0, 0, 0, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, 0, 0, 0, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1
	};

	//Set that empty board as the Board's internal array
	for (int i = 0; i < MAX_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_BOARD_WIDTH; j++)
		{
			board[i][j] = tempBoard[i][j];
		}
	}

	initBox(); //used for checking for a win, initialized the box to all 0s
	currPlayer = 1; 
}

//Copy constructor
Board::Board(Board* b)
{
	//Set the internal board to match the values of the board to be copied
	for (int i = 0; i < MAX_BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_BOARD_WIDTH; j++)
		{
			board[i][j] = b->getMarker(i, j);
		}
	}

	//Set internal attributes to the same as the passed in board
	size = b->size;
	freeSpace = b->freeSpace;
	lastCol = b->lastCol;
	lastPlayer = b->lastPlayer;
	lastRow = b->lastRow;
	movesPlayed = b->movesPlayed;
	boardFull = b->boardFull;
	currPlayer = b->currPlayer;
	
	initBox();


}

void Board::drawBoard()
{
	int start;
	int end;
	bool found = false ;

	for (int i = MAX_BOARD_HEIGHT -1; i >= 0; i--)
	{
		cout << i + 1 << "  ";

		for (int j = 0; j < MAX_BOARD_WIDTH; j++)
		{
			if (board[i][j] == -1)
			{
				cout << "  ";
			}
			else
			{
				if (!found)
				{
					found = true;
					start = j;
					end = j;
				}
				else
				{
					cout << "-";
					end++;
				}

				cout << board[i][j];
			}
		}

		found = false;
		cout << endl << "   ";

		if (i > 0)
		{
			for (int k = 0; k < start - 1; k++)
			{
				cout << "  ";
			}
	
			cout << "/";

			for (int l = 0; l <= end - start; l++)
			{
				cout << " |";
			}

			cout << " \\" << endl;
		}
		else
		{
			cout << endl << "   A B C D E F G H I J K L M" << endl;
		}
	}
}

void Board::setP1(Player* p)
{
	p1 = p;
}

void Board::setP2(Player* p)
{
	p2 = p;
}

Player* Board::getActivePlayer()
{
	return activePlayer;
}
void Board::setActivePlayer(Player* p)
{
	activePlayer = p;
}

bool Board::move(int row, int col, int player)
{
	//Make sure the attempted move is within a valid range and the board is not full
	if (row >= 0 && row < MAX_BOARD_HEIGHT && col >= 0 && col < MAX_BOARD_WIDTH && boardFull != true) 
	{
		//Make sure the indicated space is not already occupied
		if (board[row][col] == 0)
		{
			//Perform the move, record this as the last move that was played for win-check purposes
			lastRow = row;
			lastCol = col;
			lastPlayer = player;
			board[row][col] = player;
			drawBoard();

			movesPlayed++;

			if (movesPlayed == MAX_MOVES)
			{
				boardFull = true;
			}
			return true;
		}
	}

	return false;
}

//Method used for minimax to create children boards without editing the initial board or displaying the move on the screen
bool Board::dummyMove(int row, int col, int player)
{
	if (row >= 0 && row < MAX_BOARD_HEIGHT && col >= 0 && col < MAX_BOARD_WIDTH && boardFull != true) 
	{
		if (board[row][col] == 0)
		{
			lastRow = row;
			lastCol = col;
			lastPlayer = player;
			board[row][col] = player;
			//drawBoard();

			movesPlayed++;

			if (movesPlayed == MAX_MOVES)
			{
				boardFull = true;
			}
			return true;
		}
	}

	return false;
}

bool Board::checkWin()
{
	//The check win function uses a 3x3 box that is anchored with the last move played on the board
	//The last move is placed in all possible spots on the box and the surrounding values of the spaces 
	//are mapped into the box to check for a win pattern and for if a ladder is neutralized
	bool found = false;
	int floorPolarized = 0;
	int sidePolarized = 0;
	bool polarized = false;

	if (movesPlayed == 0)
		return false;

	for (int a1 = 0; a1 < MAX_BOX_WIDTH; a1++)
	{
		for (int a2 = 0; a2 < MAX_BOX_WIDTH; a2++)
		{
			box[a1][a2] = board[lastRow][lastCol];

			//If the moves are on the bottom or on the sides of the triangles, polarize
			if (lastRow == 0)
			{
				floorPolarized++;
			}
			else if ((board[lastRow][lastCol + 1] == -1 || board[lastRow][lastCol - 1] == -1) && board[lastRow][lastCol] != -1)
			{
				sidePolarized++;
			}

			for (int k = 0; k < MAX_BOX_WIDTH; k++)
			{
				for (int l = 0; l < MAX_BOX_WIDTH; l++)
				{
					if (box[k][l] != lastPlayer)
					{
						//map the position of the box to the true position of the values on the board
						int row = (a1 - k) + lastRow;
						int col = (l - a2) + lastCol;

						if (row < 0 || col < 0 || row >= MAX_BOARD_HEIGHT || col >= MAX_BOARD_WIDTH)
						{
							box[k][l] = -1;
						}
						else
						{
							box[k][l] = board[row][col];

							if (row == 0 && box[k][l] == lastPlayer)
							{
								floorPolarized++;
							}
							else if (((board[row][col + 1] == -1 || board[row][col - 1] == -1) && board[row][col] != -1) && box[k][l] == lastPlayer)
							{
								sidePolarized++;
							}
						}
					}
				}
			}

			if (floorPolarized == 2 || sidePolarized == 3)
			{
				polarized = true;
			}

			found = checkPattern(polarized);
			if (found)
				return found;

			initBox();
			floorPolarized = 0;
			sidePolarized = 0;
			polarized = false;
		}
	}

	return found;
}

void Board::initBox()
{
	int tempBox[MAX_BOX_WIDTH][MAX_BOX_WIDTH] = 
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};

	for (int k = 0; k < MAX_BOX_WIDTH; k++)
	{
		for (int l = 0; l < MAX_BOX_WIDTH; l++)
		{
			box[k][l] = tempBox[k][l];
		}
	}
}

bool Board::checkPattern(bool polarized)
{
	//Check for ladder pattern and if the ladder is polarized or not, if not, check if the ladder is neutralized
	int otherPlayer = 3 - lastPlayer;

	if (box[0][0] == lastPlayer &&
		box[1][0] == lastPlayer &&
		box[1][1] == lastPlayer &&
		box[2][1] == lastPlayer &&
		box[2][2] == lastPlayer)
	{
		if (polarized)
			return true;
		else if (box[0][2] != otherPlayer || box[2][0] != otherPlayer)
			return true;
	}
	
	if (box[0][2] == lastPlayer &&
		box[1][2] == lastPlayer &&
		box[1][1] == lastPlayer &&
		box[2][1] == lastPlayer &&
		box[2][0] == lastPlayer)
	{
		if (polarized)
			return true;
		else if (box[0][0] != otherPlayer || box[2][2] != otherPlayer)
			return true;
	}

	return false;
}

int Board::getPlayer()
{
	return currPlayer;
}

void Board::polarize(int boxRow, int boxCol, int boardRow, int boardCol)
{
	if (boardRow == 0)
	{
		box[boxRow][boxCol] = box[boxRow][boxCol] * POLARIZE;
	}
	else if ((board[boardRow][boardCol + 1] == -1 || board[boardRow][boardCol - 1] == -1) && board[boardRow][boardCol] != -1)
	{
		box[boxRow][boxCol] = box[boxRow][boxCol] * POLARIZE;
	}
}

bool Board::isFull()
{
	return boardFull;
}

int Board::getNumOpenMoves()
{
	//Return the number of available spots on the board, used for minimax
	return MAX_MOVES - movesPlayed;
}

int Board::getMarker(int row, int col)
{
	return board[row][col];
}


Board* Board::treeMove(int r, int c, int player)
{
	//Dummy move used for minimax to create the children
	Board* b = new Board(this);

	b->dummyMove(r, c, player);

	return b;
}

int Board::togglePlayer()
{
	if (currPlayer == 1)
		currPlayer = 2;
	else
		currPlayer = 1;

	return currPlayer;
}

void Board::toggleActive()
{
	if (activePlayer == p1)
		activePlayer = p2;
	else
		activePlayer = p1;
}


int Board::getLastPlayer()
{
	return lastPlayer;
}

int Board::getLastRow()
{
	return lastRow;
}

int Board::getLastCol()
{
	return lastCol;
}

Board::~Board()
{
}