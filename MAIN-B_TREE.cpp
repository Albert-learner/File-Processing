#include "B_TREE.h"

int main()
{
	vector <int>list = { 30, 20, 62, 110, 140, 15, 65, 136, 150, 120,
					     40, 132, 19, 128, 138, 100, 16, 145, 70, 42,
					     69, 43, 26, 60, 130, 50, 18, 7, 36, 58,
					     22, 41, 59, 57, 54, 33, 75, 124, 122, 123 };

	vector <int>del_list = { 40, 132, 19, 128, 138, 100, 16, 145, 70, 42,
						  22, 41, 62, 110, 140, 15, 65, 124, 122, 123,
						  30, 20, 59, 57, 54, 33, 75, 136, 150, 120,
						  69, 43, 26,60, 130, 50, 18, 7, 36, 58 };

	B_TREE b;
	for (int i = 0; i < list.size(); i++)
	{
		b.insert(3, list[i]);
		b.display();
		cout << endl;
	}

	for (int i = 0; i < del_list.size(); i++)
	{
		b.delB_TREE(3, del_list[i]);
		b.display();
		cout << endl;
	}
	return 0;
}