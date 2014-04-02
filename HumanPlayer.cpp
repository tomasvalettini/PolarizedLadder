#include "HumanPlayer.h"
#include <iostream>

using namespace std;


HumanPlayer::HumanPlayer(int _token, Board* b)
{
	isComputer = false;
	token = _token;
	board = b;
}

bool HumanPlayer::move()
{
		int tempRow;
		char colInput;


		cout << endl << "Player " << token << ":" << endl;
		cout << "Enter the row you wish to play in: ";
		cin >> tempRow;
		cout << endl << endl;

		row = tempRow - 1;

		cout << "Enter the column letter you wish to play in row " << tempRow << ": ";
		cin >> colInput;
	
		col = parseColumn(toupper(colInput));
		return (board->move(row, col, token));
}

int HumanPlayer::parseColumn(char input)
{
	int col = 0;
	switch(input)
	{
	case 'A':
		col = 0;
		break;
	case 'B':
		col = 1;
		break;
	case 'C':
		col = 2;
		break;
	case 'D':
		col = 3;
		break;
	case 'E':
		col = 4;
		break;
	case 'F':
		col = 5;
		break;
	case 'G':
		col = 6;
		break;
	case 'H':
		col = 7;
		break;
	case 'I':
		col = 8;
		break;
	case 'J':
		col = 9;
		break;
	case 'K':
		col = 10;
		break;
	case 'L':
		col = 11;
		break;
	case 'M':
		col = 12;
		break;
	}

	return col;

}


int HumanPlayer::getRow()
{
	return row;
}

int HumanPlayer::getCol()
{
	return col;
}

int HumanPlayer::getToken()
{
	return token;
}


HumanPlayer::~HumanPlayer(void)
{
}

