#include "Tree.h"

#include <iostream>

using namespace std;

Tree::Tree()
{
	
}

//The tree for minimax is built here
Node* Tree::buildTree(Board* b, int depth, int player)
{
	//Build a tree starting at rootNode whose board will be parameter b
	//parameter depth defines how far we are down the tree
	//player denotes the token (1 or 2) that will be performing the next move in the children nodes

	Node* rootNode = new Node();

	//initialize the rootNode's parameters
	rootNode->board = b;
	rootNode->numChildren = b->getNumOpenMoves();
	rootNode->value = 0;
	rootNode->children = new Node*[rootNode->numChildren]; //The children will be an array of all the possible moves at this point

	int nextChildIndex = 0;

	//record the token of the other player in order to send that token to the next level of the tree build
	int altPlayer;
	if (player == 1)
		altPlayer = 2;
	else
		altPlayer = 1;

	//As long as we are not at the lowest possible depth or if the current node does not have a winning board, then create the children
	if (depth > 1 && !rootNode->board->checkWin())
	{
			for (int r = 0; r < MAX_BOARD_HEIGHT; r++)
			{
				for (int c = 0; c < MAX_BOARD_WIDTH; c++)
				{
					//Loop through all spots in the board and check if the spot is empty, if so, make a child with a move in that spot
					if (b->getMarker(r, c) == 0) //make potential move in open slot
					{
						//Create the lower tree, rooted at the newly found child move
						rootNode->children[nextChildIndex] = buildTree(b->treeMove(r, c, player), depth - 1, altPlayer);
						nextChildIndex++;
					}
				}
			}		
	}
	else
	{
		//If we are at the lowest depth or if this node has a winning board, then force this node to be a leaf node.
		rootNode->children = NULL;
	}

	return rootNode;

}

Tree::~Tree()
{
}
