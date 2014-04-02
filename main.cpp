#include <iostream>
#include "Board.h"
#include "Tree.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

using namespace std;

int parseColumn(char input);


void main()
{
	int mode;		//play mode (PvP=1, PvC=2, CvP=3)
	Player* active; //Pointer to the player whose turn it is

	cout << "Welcome to Polarized Ladder!!!" << endl;
	cout << endl << "Please select which mode you would like to play in" << endl << "(1 for PvP, 2 for PvC, 3 for CvP): ";
	cin >> mode;


	Board b = Board();
	if (mode == 1) //PvP
	{
		HumanPlayer h1(1, &b);
		HumanPlayer h2(2, &b);
		b.setP1(&h1);
		b.setP2(&h2);
		b.setActivePlayer(&h1);

	}
	else if (mode == 2) //PvC
	{
		HumanPlayer h(1, &b);
		AIPlayer ai(2, &b);
		b.setP1(&h);
		b.setP2(&ai);
		b.setActivePlayer(&h);
	}
	else				//CvP (Computer starts first)
	{
		HumanPlayer h(2, &b);
		AIPlayer ai(1, &b);
		b.setP1(&ai);
		b.setP2(&h);
		b.setActivePlayer(&ai);
	}
	b.drawBoard();

		do //perform the Active Player's move and continue until we have a winner or the board is full (draw)
		{	
			active = b.getActivePlayer();
		
			while(!active->move()) //Call the active player's move, returns false if move is not valid
			{
				cout << "Invalid move!!!!! Re-enter location!" << endl;
			}

			b.togglePlayer();	//Toggles the board player token (1 or 2) used for minimax
			b.toggleActive();	//Toggles the turn, getActivePlayer will now return the alternate player
		}
		while (!b.checkWin() && !b.isFull()); //end game loop if there is a win or a tie

		if (b.checkWin())
			cout << "Player " << b.getLastPlayer() << " wins the game!!!!!!" << endl;
		else if (b.isFull())
			cout << "Draw! No more moves to play!" << endl;

	system("pause");

}
	
	

	




