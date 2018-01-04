// CSCI 3300
// Assignment: 8
// Author:     Joshua Bowen
// File:       tree.h
// Tab stops:  8

#ifndef TREE_H_
#define TREE_H_

enum NodeKind {leaf, nonleaf};

// structure to represent a Node in a tree.

struct Node
{
	NodeKind kind;
	char ch;
	Node* left;
	Node* right;
	Node(char c)
	{
		kind = leaf;
		ch = c;
	}
	Node(Node* L, Node* R)
	{
		kind = nonleaf;
		left = L;
		right = R;
	}
};


#endif /* TREE_H_ */
