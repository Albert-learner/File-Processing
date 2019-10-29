#ifndef __MYBTREE_H__
#define __MYBTREE_H__
#include <iostream>
#include <cstdlib>
#include <cmath>
#define STACKSIZE 30
#define MAX 6

using namespace std;

class Node {
private:
	int n;
	int len;
	int key[MAX - 1];
	Node *pT[MAX];
	Node(int d) {
		n = 0;
		len = d;
		//포인터 및 키값 NULL로 초기화
		/*key = new int[len - 1];
		for (int i = 0; i < len - 1; i++){
		key[i] = NULL;
		}
		pT = new Node*[len];
		for (int i = 0; i < len; i++){
		pT[i] = NULL;
		}*/
		for (int i = 0; i < MAX - 1; i++) {
			key[i] = NULL;
		}
		for (int i = 0; i < MAX; i++) {
			pT[i] = NULL;
		}
	}
	friend class Tree;
};

class Tree {
private:
	Node * T;
	Node *S[STACKSIZE];
	int IndS[STACKSIZE];
	int top;
	int topInd;
public:
	Tree() {
		T = NULL;
		top = -1;
		topInd = -1;
	}
	Node *getNode(int d);
	void insertTree(int d, int newKey) { T = insertBtree(T, d, newKey); }
	Node *insertBtree(Node *T, int m, int newKey);
	void show() { inorder(T); }
	void inorder(Node *T);
	bool isFull();
	bool isEmpty();
	void push(Node *p);
	void pushInd(int index);
	Node *pop();
	int popInd();
	void deleteTree(int d, int oldKey) { T = delBtree(T, d, oldKey); }
	Node *delBtree(Node *T, int m, int oldKey);
};

#endif