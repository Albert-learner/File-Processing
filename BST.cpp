#include "BST.h"

// 원하는 노드의 위치 찾아서 반환하는 함수
Node *BinarySearchTree::searchBST(Node *p, int key)
{
	if (p == NULL)
		return NULL;
	else
	{
		if (key == p->data)
			return p;
		else if (key < p->data)
			p = searchBST(p->left, key);
		else
			p = searchBST(p->right, key);
	}
	return p;
}

//BinarySearchTree객체에 부모 노드의 위치를 찾아서 반환하는 함수
Node *BinarySearchTree::searchParentBST(Node *p, int key)
{
	Node *prev = NULL;

	if (p == NULL)
		return NULL;
	else
	{
		Node *cur = p;
		prev = p;
		while (cur != nullptr)
		{
			if (key == cur->data)
				return prev;
			else if (key < cur->data)
			{
				prev = cur;
				cur = cur->left;
			}
			else
			{
				prev = cur;
				cur = cur->right;
			}
		}
	}
}

//BinarySearchTree객체에 Node 삽입하는 함수
void BinarySearchTree::insertBST(BinarySearchTree b, int key)
{
	Node *cur = b.getNode();
	Node *prev = nullptr;

	while (cur != nullptr)
	{
		if (key == cur->data) //중복된 key값 처리
			return;
		if (key < cur->data)
		{
			prev = cur;
			cur = cur->left;
		}
		else
		{
			prev = cur;
			cur = cur->right;
		}
	}

	// 찾았음
	Node *newNode = new Node(key);
	if (root == nullptr)
		root = newNode;
	else
	{
		if (key < prev->data)
			prev->left = newNode;
		else
			prev->right = newNode;
	}
	return;
}

//노드를 기준으로 가장 작은 값의 노드를 반환하는 함수
Node *BinarySearchTree::minNode(Node *p)
{
	if (p == NULL)
		return p;
	else
	{
		if (p->left == NULL)
			return p;
		else
			return minNode(p->left);
	}
}

//노드를 기준으로 가장 큰 값의 노드를 반환하는 함수
Node *BinarySearchTree::maxNode(Node *p)
{
	if (p == NULL)
		return p;
	else
	{
		if (p->right == NULL)
			return p;
		else
			return maxNode(p->right);
	}
}

//노드를 기준으로 높이 값을 리턴해주는 함수
int BinarySearchTree::height(Node *p)
{
	if (p == NULL)
		return 0;

	int left = height(p->left);
	int right = height(p->right);
	return 1 + (left > right ? left : right);
}

//기준이 되는 노드까지의 노드 개수를 리턴해주는 함수
int BinarySearchTree::numNode(Node *p)
{
	if (p == NULL)
		return 0;
	else
		return numNode(p->left) + numNode(p->right) + 1;
}

//BinarySearchTree에서 key값 삭제하는 함수
void BinarySearchTree::deleteBST(BinarySearchTree b, int key)
{
	Node *del = searchBST(b.getNode(), key);
	Node *parent = searchParentBST(b.getNode(), key);

	if (del == NULL)
		return;
	else
	{
		//삭제하려는 노드의 left, right 둘 다 없는 경우(자식이 없는 경우)
		if (del->left == NULL && del->right == NULL)
		{
			if (del == root)
			{
				root = NULL;
				return;
			}
			if (parent->left == del)
				parent->left = NULL;
			else
				parent->right = NULL;
			delete(del);
		}
		//삭제하려는 노드의 left 또는 right가 없는 경우(자식이 1개인 경우)
		else if (del->left == NULL || del->right == NULL)
		{
			if (del == root)
			{
				if (root->right != NULL)
					root = root->right;
				else
					root = root->left;
				return;
			}
			if (del->left != NULL)
			{
				if (parent->left == del)
					parent->left = del->left;
				else
					parent->right = del->left;
			}
			else
			{
				if (parent->left == del)
					parent->left = del->right;
				else
					parent->right = del->right;
			}
			delete(del);
		}
		//삭제하려는 노드의 left, right 둘 다 있는 경우(자식이 2개인 경우)
		else
		{
			if (BinarySearchTree::height(del->left) > BinarySearchTree::height(del->right))
			{
				Node *tmp = maxNode(del->left);
				int value = tmp->data;
				Node *tmp_par = searchParentBST(tmp, tmp->data);
				if (tmp->left != NULL) {
					tmp_par->right = tmp->left;
					tmp->left = NULL;
				}
				deleteBST(b, value);
				del->data = value;

			}
			else
			{
				Node *tmp = minNode(del->right);
				int value = tmp->data;
				Node *tmp_par = searchParentBST(tmp, tmp->data);
				if (tmp->right != NULL) {
					tmp_par->left = tmp->right;
					tmp->right = NULL;
				}
				deleteBST(b, value);
				del->data = value;
			}
		}
	}
}

//inorder순으로 출력해주는 함수
void BinarySearchTree::inorderBST(Node *p)
{
	if (p != NULL)
	{
		inorderBST(p->left);
		cout << p->data << " ";
		inorderBST(p->right);
	}
	return;
}