#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#define STACKSIZE 40
using namespace std;

class Node
{
	int n, len;
	int *key;
	Node **child;

	Node(int d)
	{
		n = 0;
		len = d;
	
		
		key = new int[len - 1];
		for (int i = 0; i < len - 1; i++)
		{
			key[i] = NULL;
		}
		child = new Node *[len];
		for (int i = 0; i < len; i++)
		{
			child[i] = NULL;
		}
		
	}
	friend class B_TREE;
};

class B_TREE
{
	Node *root;
	Node *stack[STACKSIZE];
	int top;
	int indexStack[STACKSIZE];
	int topIndex;
public:
	B_TREE()
	{
		root = NULL;
		top = -1;
		topIndex = -1;
	}

	bool isEmpty();
	bool isFull();
	Node *getNode(int size);
	void push(Node *p);
	Node *pop();
	void pushIndex(int index);
	int popIndex();
	Node *insertB_TREE(Node *p, int size, int key);
	void insert(int size, int key)
	{
		root = insertB_TREE(root, size, key);
	}
	void inorderB_TREE(Node *p);
	void display()
	{
		inorderB_TREE(root);
	}
	Node *deleteB_TREE(Node *p, int size, int key);
	void delB_TREE(int size, int key)
	{
		root = deleteB_TREE(root, size, key);
	}
	bool existAvailableSibling(Node *p, int cost, int size);
};