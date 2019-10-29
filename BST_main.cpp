#include "BST.h"

int main()
{
	vector <int>check = { 8, 18, 11, 5, 15, 4, 9, 1, 7, 17, 6, 14, 10, 3, 19, 20 };
	BinarySearchTree bst;

	for (int i = 0; i < check.size(); i++)
	{
		bst.insertBST(bst, check[i]);
		bst.inorderBST(bst.getNode());
		cout << endl;
	}

	for (int i = 0; i < check.size(); i++)
	{			
		bst.deleteBST(bst, check[i]);
		bst.inorderBST(bst.getNode());
		cout << endl;
	}
	
	for (int i = 0; i < check.size(); i++)
	{
		bst.insertBST(bst, check[i]);
		bst.inorderBST(bst.getNode());
		cout << endl;
	}

	for (int i = 0; i < check.size(); i++)
	{
		bst.deleteBST(bst, check[check.size()-1-i]);
		bst.inorderBST(bst.getNode());
		cout << endl;
	}
	return 0;
}