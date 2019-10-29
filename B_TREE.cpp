#include "B_TREE.h"

Node *B_TREE::getNode(int size)
{
	Node *newNode = new Node(size);
	return newNode;
}

bool B_TREE::isEmpty()
{
	if (top == -1)
		return true;
	else
		return false;
}

bool B_TREE::isFull()
{
	if (top == STACKSIZE - 1)
		return true;
	else
		return false;
}

void B_TREE::push(Node *p)
{
	if (isFull())
		return;
	top++;
	stack[top] = p;
}

Node *B_TREE::pop()
{
	if (isEmpty())
		return NULL;
	else
		return stack[top--];
}

void B_TREE::pushIndex(int cost)
{
	if (topIndex == STACKSIZE - 1)
		return ;
	else
	{
		topIndex++;
		indexStack[topIndex] = cost;
	}
}

int B_TREE::popIndex()
{
	if (topIndex == -1)
		return 0;
	else
		return indexStack[topIndex--];
}

void B_TREE::inorderB_TREE(Node *p)
{
	if (p == NULL)
		return;
	else
	{
		Node *x = p;
		int pos = 0;
		inorderB_TREE(x->child[pos]);
		while (pos <= (x->n) - 1)
		{
			cout << x->key[pos] << " ";
			inorderB_TREE(x->child[pos + 1]);
			pos++;
		}
	}
}

Node *B_TREE::insertB_TREE(Node *p, int size, int key)
{
	if (p == NULL)
	{
		p = getNode(size);
		p->key[0] = key;
		(p->n)++;
		return p;
	}

	Node *x = p;

	while (x != NULL)
	{
		int i = 0;
		while (i < (x->n) && key > x->key[i])
		{
			i++;
		}
		if (i < x->n && key == x->key[i])
		{
			top = -1;
			return p;
		}
		push(x);
		x = x->child[i];
	}

	Node *temp = getNode(size + 1);
	Node *y = NULL;
	bool confirm = false;
	x = pop();

	while (!confirm)
	{
		if (x->n < x->len - 1)
		{
			int temp_cost;
			for (int i = 0; i < x->n; i++)
			{
				if (key < x->key[i])
				{
					Node *z = x->child[i + 1];
					x->child[i + 1] = y;
					y = z;
					temp_cost = x->key[i];
					x->key[i] = key;
					key = temp_cost;
				}
			}
			x->key[x->n] = key;
			x->child[(x->n) + 1] = y;
			(x->n)++;
			confirm = true;
		}
		else
		{
			temp->child[0] = x->child[0];
			for (int i = 0; i < x->n; i++)
			{
				temp->key[i] = x->key[i];
				temp->child[i + 1] = x->child[i + 1];
			}
			temp->n = x->n;

			int temp_cost;
			for (int i = 0; i < temp->n; i++)
			{
				if (key < temp->key[i])
				{
					temp_cost = x->key[i];
					temp->key[i] = key;
					key = temp_cost;
					Node *z = temp->child[i + 1];
					temp->child[i + 1] = y;
					y = z;
				}
			}
			temp->key[temp->n] = key;
			temp->n++;
			temp->child[temp->n] = y;

			//split
			key = temp->key[(temp->n) / 2];
			x->n = (temp->n) / 2;
			x->child[0] = temp->child[0];
			for (int i = 0; i < (temp->n) / 2; i++)
			{
				x->key[i] = temp->key[i];
				x->child[i + 1] = temp->child[i + 1];
			}
			y = getNode(size);
			y->n = (temp->n) - ((temp->n) / 2) - 1;

			if (size % 2 != 0)
			{
				y->child[0] = temp->child[(temp->n) - (temp->n) / 2];
				for (int i = 0; i < (temp->n) - ((temp->n) / 2) - 1; i++)
				{
					y->key[i] = temp->key[i + (temp->n) / 2 + 1];
					y->child[i + 1] = temp->child[i + 1 + (temp->n) - ((temp->n) / 2)];
				}
			}
			else
			{
				y->child[0] = temp->child[(temp->n) - ((temp->n) / 2) + 1];
				for (int i = 0; i < (temp->n) - ((temp->n) / 2) - 1; i++)
				{
					y->key[i] = temp->key[i + (temp->n) / 2 + 1];
					y->child[i + 1] = temp->child[i + 2 + (temp->n) - ((temp->n) / 2)];
				}
			}
			if (!isEmpty())
				x = pop();
			else
			{
				p = getNode(size);
				p->key[0] = key;
				p->n++;
				p->child[0] = x;
				p->child[1] = y;
				confirm = true;
			}
		}
	}
	top = -1;
	return p;
}

bool B_TREE::existAvailableSibling(Node *p, int cost, int size)
{
	Node *sibling;
	int position=0; 

	if (p != NULL)
	{
		if (cost == 0)
		{
			sibling = p->child[1];
			position = 1;
		}
		else if (cost == size - 1)
		{
			sibling = p->child[cost - 1];
			position = 0;
		}
		else
		{
			if (p->child[cost + 1] == NULL)
			{
				sibling = p->child[cost - 1];
				position = 0;
			}
			else if (p->n >= cost + 1 && p->child[cost - 1]->n < p->child[cost + 1]->n)
			{
				sibling = p->child[cost + 1];
				position = 1;
			}
			else
			{
				sibling = p->child[cost - 1];
				position = 0;
			}
		}
	}
	if ((p->n > ceil(size / 2.0) - 1 && p->n >= ceil(size / 2.0) - 1) || (p->n == ceil(size / 2.0) - 1 && p->n > ceil(size / 2.0) - 1))
		return true;
	else
		return false;
}


Node *B_TREE::deleteB_TREE(Node *p, int size, int del_key)
{
	if (p == NULL)
	{
		top = -1;
		topIndex = -1;
		return p;
	}
	else
	{
		Node *x = p;
		Node *y = p;
		int index = 0;
		Node *inNode;
		
		do
		{
			int i = 0;
			//
			while (i < x->n && del_key > x->key[i])
				i++;
			if (i <= x->n && del_key == x->key[i])
			{
				index = i;
				break;
			}
			push(x);
			pushIndex(i);
			x = x->child[i];
		} while (x != NULL);

		inNode = x;
		if (x->child[0] != NULL)
		{
			push(x);
			pushIndex(index + 1);
			x = x->child[index+1];
			do
			{
				push(x);
				pushIndex(0);
				x = x->child[0];
			} while (x != NULL);
			popIndex();
		}

		int temp;
		if (x == NULL)
		{
			x=pop();
			temp = inNode->key[index];
			inNode->key[index] = x->key[0];
			x->key[0] = temp;
		}

		int del = del_key;
		for (int i = 1; i < x->n; i++)
		{
			if (x->key[i - 1] == del)
			{
				x->key[i - 1] = x->key[i];
				del = x->key[i];
			}
		}
		(x->n)--;
		
		bool confirm = false;
		y = NULL;
		if (!isEmpty())
		{
			y = pop();
		}

		//delete
		do
		{
			Node *sibling;
			int position = 0;
			int cost = popIndex();

			if (x == p || x->n >= ceil(size / 2.0) - 1)
				confirm = true;
			else if (existAvailableSibling(y, cost, size))
			{
				if (y != NULL)
				{
					if (cost == 0)
					{
						sibling = y->child[1];
						position = 1;
					}
					else if (cost == size - 1)
					{
						sibling = y->child[cost - 1];
						position = 0;
					}
					else
					{
						if (y->child[cost + 1] == NULL)
						{
							sibling = y->child[cost - 1];
							position = 0;
						}
						else if (y->n >= cost + 1 && y->child[cost - 1]->n < y->child[cost + 1]->n)
						{
							sibling = y->child[cost + 1];
							position = 1;
						}
						else
						{
							sibling = y->child[cost - 1];
							position = 0;
						}
					}
				}
				Node *tempN = getNode(ceil(1.5*size));
				if (position == 0)
				{
					tempN->child[0] = sibling->child[0];
					int idx = 0;
					for (idx = 0; idx < sibling->n; idx++)
					{
						tempN->key[idx] = sibling->key[idx];
						tempN->child[idx + 1] = sibling->child[idx + 1];
					}
					tempN->key[idx] = y->key[cost - 1];
					tempN->child[++idx] = x->child[0];

					for (int i = 0; idx < 1 + sibling->n + x->n; i++, idx++)
					{
						tempN->key[idx] = x->key[i];
						tempN->child[idx + 1] = x->child[i + 1];
					}
					tempN->n = 1 + sibling->n + x->n;

					if (sibling->n > ceil(size / 2.0) - 1)
					{
						sibling->child[0] = tempN->child[0];
						sibling->n = 0;

						for (idx = 0; idx < tempN->n / 2; idx++)
						{
							sibling->key[idx] = tempN->key[idx];
							sibling->n++;
						}
						y->key[cost - 1] = tempN->key[idx];
						x->child[0] = tempN->child[++idx];
						for (int i = 0; idx < tempN->n; i++, idx++)
						{
							x->key[i] = tempN->key[idx];
							x->child[i + 1] = tempN->child[idx + 1];
							x->n++;
						}
					}
					else
					{
						sibling->child[0] = tempN->child[0];
						for (int i = 0; i < tempN->n; i++)
						{
							sibling->key[i] = tempN->key[i];
							sibling->child[i + 1] = tempN->child[i + 1];
						}
						sibling->n = tempN->n;
						y->key[cost - 1] = tempN->key[tempN->n - 1];

						if (cost != 0)
						{
							for (int i = cost - 1; i < y->n; i++)
							{
								y->key[i] = y->key[i + 1];
								y->child[i + 1] = y->child[i + 2];
							}
							y->child[y->n] = y->child[y->n + 1];
							y->n--;
						}
					}
				}
				else
				{

					tempN->child[0] = x->child[0];
					int idx = 0;
					for (idx = 0; idx < x->n; idx++)
					{
						tempN->key[idx] = x->key[idx];
						tempN->child[idx + 1] = x->child[idx + 1];
					}
					tempN->key[idx] = y->key[cost];
					tempN->child[++idx] = sibling->child[0];

					for (int i = 0; i < 1 + sibling->n + x->n; i++, idx++)
					{
						tempN->key[idx] = sibling->key[i];
						tempN->child[idx + 1] = sibling->child[i + 1];
					}
					tempN->n = 1 + sibling->n + x->n;//temp 복사

					if (sibling->n > ceil(size / 2.0) - 1)//재분배
					{
						x->child[0] = tempN->child[0];
						for (idx = 0; idx < tempN->n / 2; idx++)
						{
							x->key[idx] = tempN->key[idx];
							x->child[idx + 1] = tempN->child[idx + 1];
							x->n++;
						}
						y->key[cost] = tempN->key[idx];
						sibling->child[0] = tempN->child[++idx];
						sibling->n = 0;

						for (int i = 0; idx < tempN->n; i++, idx++)
						{
							sibling->key[i] = tempN->key[idx];
							sibling->child[i + 1] = tempN->child[idx + 1];
							sibling->n++;
						}
					}
					else
					{
						x->child[0] = tempN->child[0];
						for (int i = 0; i < tempN->n; i++)
						{
							x->key[i] = tempN->key[i];
							x->child[i + 1] = tempN->child[i + 1];
						}
						x->n = tempN->n;
						y->key[cost] = tempN->key[tempN->n - 1];
						if (cost != 0)
						{
							for (int i = cost - 1; i < y->n; i++)
							{
								y->key[i] = y->key[i + 1];
								y->child[i + 1] = y->child[i + 2];
							}
							y->child[y->n] = y->child[y->n + 1];
							y->n--;
						}
						else
						{
							for (int i = cost; i < y->n; i++)
							{
								y->key[i] = y->key[i + 1];
								y->child[i + 1] = y->child[i + 2];
							}
							y->child[y->n] = y->child[y->n + 1];
							y->n--;
						}
					}					
				}
			confirm = true;
			}
			else
			{
				if (y != NULL)
				{
					if (cost == 0)
					{
						sibling = y->child[1];
						position = 1;
					}
					else if (cost == size - 1)
					{
						sibling = y->child[cost - 1];
						position = 0;
					}
					else
					{
						if (y->child[cost + 1] == NULL)
						{
							sibling = y->child[cost - 1];
							position = 0;
						}
						else if (y->n >= cost + 1 && y->child[cost - 1]->n < y->child[cost + 1]->n)
						{
							sibling = y->child[cost + 1];
							position = 1;
						}
						else
						{
							sibling = y->child[cost - 1];
							position = 0;
						}
					}
				}
				if (position == 0)
				{
					sibling->key[sibling->n] = y->key[cost - 1];
					sibling->n++;
					sibling->child[sibling->n] = x->child[0];
					y->n--;

					int tmp = sibling->n;
					for (int i = 0; tmp < sibling->n + x->n; i++, tmp++)
					{
						sibling->key[tmp] = x->key[i];
						sibling->child[tmp + 1] = x->child[i + 1];
					}
					sibling->n = sibling->n + x->n;
					delete(y->child[cost]);
				}
				else
				{
					x->key[x->n] = y->key[cost];
					x->n++;
					x->child[sibling->n] = sibling->child[0];
					y->n--;
					int cri = x->n;
					for (int i = 0; cri < x->n + sibling->n; i++, cri++)
					{
						x->key[cri] = sibling->key[i];
						x->child[cri + 1] = sibling->child[i + 1];
					}
					x->n += sibling->n;
					delete(y->child[cost + 1]);
				}
				if (!isEmpty())
				{
					x = y;
					y = pop();
				}
				else
				{
					if (position == 0)
						x = sibling;
					confirm = true;
				}
			}
		} while (!confirm);

		if (y == NULL || y->n == 0)
		{
			p = x;
			delete(y);
		}
		top = -1;
		topIndex = -1;
		return p;
	}
}