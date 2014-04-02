#include "AIPlayer.h"
#include <iostream>

using namespace std;

AIPlayer::AIPlayer(int _token, Board* b)
{
	token = _token;
	isComputer = true;
	board = b;
}


AIPlayer::~AIPlayer(void)
{
}

bool AIPlayer::move()
{
	//Here is where the minimax tree is created and the heuristic is applied.
	root = t.buildTree(board, TREE_DEPTH, token);
	
	//Once the tree is created, apply the heuristic to the leaf nodes and propogate the values up the tree
	applyHeuristic(root);

	//getNextMove will apply minimax to see which choice would be the best to take
	nextMove = getNextMove();

	//Perform the move
	board->move(nextMove->board->getLastRow(), nextMove->board->getLastCol(), token);

	return true;
}


void AIPlayer::applyHeuristic(Node* rootNode)
{
	//Check for leaf node in order to apply the heuristic to the bottom of the tree
	if(rootNode->children == NULL) //leaf node
	{
		//If this is a winning board for the AI, value is +100000
		if (rootNode->board->checkWin() == true && rootNode->board->getLastPlayer() == token)
		{
			rootNode->value = 100000;
		}	
		//If this is a winning board for the opponent, value is -100000
		else if (rootNode->board->checkWin() == true && rootNode->board->getLastPlayer() != token)
		{
			rootNode->value = -100000;
		}
		else
		{
			for (int r = 0; r < MAX_BOARD_HEIGHT; r++)
			{
				for (int c = 0; c < MAX_BOARD_WIDTH; c++)
				{
					//Loop through the entire board and find spots where the AI's token is
					if (rootNode->board->getMarker(r, c) == token)
					{
						//If you have a single connection between two AI tokens ---- then value = +1
						if (rootNode->board->getMarker(r, c+1) == token)
						{
							//If you have a partial ladder built with 3 tokens __| then value = +10
							if (rootNode->board->getMarker(r+1, c+1) == token)
							{
								//If you have a partial ladder built with 4 token __|''' then +100
								if (rootNode->board->getMarker(r+1, c+2) == token)
								{
									rootNode->value += 100;
								}
								rootNode->value += 10;
							}
							rootNode->value += 1;
						}
						//If you have a single connection between two AI tokens ---- then value = +1
						if (rootNode->board->getMarker(r, c-1) == token)
						{
							//If you have a partial ladder built with 3 tokens |__ then value = +10
							if (rootNode->board->getMarker(r+1, c-1) == token)
							{
								//If you have a partial ladder built with 4 tokens '''|__ then value = +100
								if (rootNode->board->getMarker(r+1, c-2) == token)
								{
									rootNode->value += 100;
								}
								rootNode->value += 10;
							}
							rootNode->value += 1;
						}


					}
					//If the token you encounter is the opponent's
					else if (rootNode->board->getMarker(r, c) != token && rootNode->board->getMarker(r, c) != -1 && rootNode->board->getMarker(r, c) != 0) //it is the other player
					{
						//get the opponent token
						int opponent = rootNode->board->getMarker(r, c);

						//Same heuristic as detailed above but the values are negative since these cases are more advantageous for the opponent
						if (rootNode->board->getMarker(r, c+1) == opponent)
						{
							if (rootNode->board->getMarker(r+1, c+1) == opponent)
							{
								if (rootNode->board->getMarker(r+1, c+2) == opponent)
								{
									rootNode->value -= 100;
								}
								rootNode->value -= 10;
							}
							rootNode->value -= 1;
						}
						if (rootNode->board->getMarker(r, c-1) == opponent)
						{
							if (rootNode->board->getMarker(r+1, c-1) == opponent)
							{
								if (rootNode->board->getMarker(r+1, c-2) == opponent)
								{
									rootNode->value -= 100;
								}
								rootNode->value -= 10;
							}
							rootNode->value -= 1;
						}
					}
				}
			}
		}
	}
	//If the node we are looking at is NOT a leaf node then recursively call this function on this node's children
	else
	{
		for (int i = 0; i < rootNode->numChildren; i++)
		{
			applyHeuristic(rootNode->children[i]);
		}
	}
}

//Here is where the values of the heuristic are propogated up the tree
Node* AIPlayer::minimax(Node* rootNode, bool isMax)
{
	//Node that will store the best choice depending on the level you are on (min or max)
	Node* optimalNode = new Node();

	//If you are a leaf node, return yourself up a level to be compared with the other children nodes
	if (rootNode->children == NULL)
		return rootNode;
	else
	{
		//If you are on the max level, then optimalNode will be one whose value is the highest
		if (isMax)
		{
			//set optimal value to something very low for initial comparison
			optimalNode->value = -100000;

			//loop through all children of this node
			for (int i = 0; i < rootNode->numChildren; i++)
			{
				//Apply the minimax on the children, setting them to the level min  (isMax = false)
				Node* child = minimax(rootNode->children[i], false);

				//Once the children nodes have applied minimax, get the highest value of the children nodes
				if (child->value > optimalNode->value)
					optimalNode = child;
			}
			//set this rootNode's value to the optimal value that was found in the loop
			rootNode->value = optimalNode->value;
			return rootNode;
		}
		else //if isMax == false (we are on the min level)
		{
			//Same logc as above but now we are looking for the smallest value as the optimal one
			optimalNode->value = 100000;
			for (int i = 0; i < rootNode->numChildren; i++)
			{
				Node* child = minimax(rootNode->children[i], true);
				if (child->value < optimalNode->value)
					optimalNode = child;
			}
			rootNode->value = optimalNode->value;
			return rootNode;

		}
	}
}

//This method will return the node that will be the most optimal choice
Node* AIPlayer::getNextMove()
{
	//apply minimax for the board configuration we are on now
	minimax(root, true);

	for (int i = 0; i < root->numChildren; i++)
	{
		//Find the child node that is sharing the same heuristic value as the root node after the minimax evaluation
		//i.e. the child node that was defined that the optimalNode in the minimax function
		if (root->children[i]->value == root->value)
		{
			return root->children[i];
		}
	}
}