#ifndef TREE_H
#define TREE_H

#include "Board.h"

struct Node
{
	Board* board;
	Node** children;
	int value;
	int numChildren;
};

class Tree
{
public: 
	Tree();
	Node* buildTree(Board* b, int depth, int player);
	Board* treeMove(int row, int col, int player);
	~Tree();
private:
	int depth;
	Node* root;
};


#endif //TREE_H