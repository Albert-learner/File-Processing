#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
	int data;
	Node *left;
	Node *right;

	Node(int value)
	{
		data = value;
		left = NULL;
		right = NULL;
	}
	friend class BinarySearchTree;
};

class BinarySearchTree
{
private:
	Node * root;
public:
	BinarySearchTree()
	{
		root = NULL;
	}
	void setNode(Node *p)
	{
		this->root = p;
		return ;
	}
	Node *getNode()
	{
		return root;
	}
	
	Node *searchBST(Node *p, int key);
	Node *searchParentBST(Node *p, int key);
	void insertBST(BinarySearchTree b, int key);
	Node *minNode(Node *p);
	Node *maxNode(Node *p);
	int height(Node *p);
	int numNode(Node *p);
	void deleteBST(BinarySearchTree b, int key);
	void inorderBST(Node *p);
};
