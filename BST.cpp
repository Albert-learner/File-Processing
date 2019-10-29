#include "BST.h"

// ���ϴ� ����� ��ġ ã�Ƽ� ��ȯ�ϴ� �Լ�
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

//BinarySearchTree��ü�� �θ� ����� ��ġ�� ã�Ƽ� ��ȯ�ϴ� �Լ�
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

//BinarySearchTree��ü�� Node �����ϴ� �Լ�
void BinarySearchTree::insertBST(BinarySearchTree b, int key)
{
	Node *cur = b.getNode();
	Node *prev = nullptr;

	while (cur != nullptr)
	{
		if (key == cur->data) //�ߺ��� key�� ó��
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

	// ã����
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

//��带 �������� ���� ���� ���� ��带 ��ȯ�ϴ� �Լ�
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

//��带 �������� ���� ū ���� ��带 ��ȯ�ϴ� �Լ�
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

//��带 �������� ���� ���� �������ִ� �Լ�
int BinarySearchTree::height(Node *p)
{
	if (p == NULL)
		return 0;

	int left = height(p->left);
	int right = height(p->right);
	return 1 + (left > right ? left : right);
}

//������ �Ǵ� �������� ��� ������ �������ִ� �Լ�
int BinarySearchTree::numNode(Node *p)
{
	if (p == NULL)
		return 0;
	else
		return numNode(p->left) + numNode(p->right) + 1;
}

//BinarySearchTree���� key�� �����ϴ� �Լ�
void BinarySearchTree::deleteBST(BinarySearchTree b, int key)
{
	Node *del = searchBST(b.getNode(), key);
	Node *parent = searchParentBST(b.getNode(), key);

	if (del == NULL)
		return;
	else
	{
		//�����Ϸ��� ����� left, right �� �� ���� ���(�ڽ��� ���� ���)
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
		//�����Ϸ��� ����� left �Ǵ� right�� ���� ���(�ڽ��� 1���� ���)
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
		//�����Ϸ��� ����� left, right �� �� �ִ� ���(�ڽ��� 2���� ���)
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

//inorder������ ������ִ� �Լ�
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