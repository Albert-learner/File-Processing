#include "B_TREE.h"

//빈 노드 생성
Node* Tree::getNode(int m) {
	Node *p = new Node(m);
	return p;
}

//노드 입력 함수
Node* Tree::insertBtree(Node *T, int m, int newKey) {
	if (T == NULL) {             //트리가 비어있을 경우
		T = getNode(m);
		T->key[0] = newKey;
		(T->n)++;
		return T;
	}

	int i = 0;
	Node *x = T;

	while (x != NULL) {
		int a = 0;
		while (a < (x->n) && newKey > x->key[a]) { //newKey가 더 큰 값을 찾거나 Node에 들어있는 key값 개수 전까지 탐색
			a++;
		}
		if (a < x->n && newKey == x->key[a]) { //만약 탐색 도중 newKey값과 같은 키 값을 찾게되면
			top = -1;
			return T;
		}
		push(x);        //경로를 스택에 저장
		x = x->pT[a];   //다음 바로 밑의 포인터로
	}
	//삽입
	Node *tempNode = getNode(m + 1); //key값이 많아지게 되어서 overflow가 될 때 newKey를 집어넣은 임시노드 생성
	Node *y = NULL;
	bool finished = false;
	x = pop();                       //스택 안의 경로 가져옴
	int newK = newKey;
	while (!finished) {
		if (x->n < x->len - 1) {      //노드 안에 key개수가 m-1보다 작을 경우
			int temp;                //newK와 그 하위 포인터를 소팅하여 저장하고 while문 탈출
			for (int i = 0; i < x->n; i++) {
				if (newK < x->key[i]) {
					Node *z = x->pT[i + 1];
					x->pT[i + 1] = y;
					y = z;
					temp = x->key[i];
					x->key[i] = newK;
					newK = temp;
				}
			}
			x->key[x->n] = newK;
			x->pT[(x->n) + 1] = y;
			(x->n)++;
			finished = true;
		}
		else {                         //overflow가 되는 경우
			int a;
			tempNode->pT[0] = x->pT[0];      //임시 노드에 x노드 저장
			for (int i = 0; i < x->n; i++) {
				tempNode->key[i] = x->key[i];
				tempNode->pT[i + 1] = x->pT[i + 1];
			}
			tempNode->n = x->n;

			int temp;
			for (int i = 0; i < tempNode->n; i++) { //임시 노드에 newK와 그 하위 포인터를 정렬하여 저장
				if (newK < tempNode->key[i]) {
					temp = x->key[i];
					tempNode->key[i] = newK;
					newK = temp;
					Node *z = tempNode->pT[i + 1];
					tempNode->pT[i + 1] = y;
					y = z;
				}
			}
			tempNode->key[tempNode->n] = newK;
			tempNode->n++;
			tempNode->pT[tempNode->n] = y;
			//스플릿
			newK = tempNode->key[(tempNode->n) / 2];  //newK를 임시 노드의 절반 지점에 있는 key값으로 설정
			x->n = (tempNode->n) / 2;                 //임시노드의 키의 개수의 절반을 x의 키의 개수로 설정(int 형이므로 소수점은 버림)             
			x->pT[0] = tempNode->pT[0];
			for (int i = 0; i < (tempNode->n / 2); i++) { //새로운 x노드 저장
				x->key[i] = tempNode->key[i];
				x->pT[i + 1] = tempNode->pT[i + 1];
			}
			y = getNode(m);       //y노드 위한 새로운 공간 설정
			y->n = (tempNode->n) - ((tempNode->n) / 2) - 1;  //중간값은 위로 올라가야되기 때문에 개수 조정
															 //인덱스를 조절해 중간key값 이후의 포인터와 key값들을 y에 저장
															 //case m이 홀수
			if (m % 2 != 0) {
				y->pT[0] = tempNode->pT[(tempNode->n) - ((tempNode->n) / 2)];
				for (int i = 0; i < (tempNode->n) - ((tempNode->n) / 2) - 1; i++) {
					y->key[i] = tempNode->key[i + (tempNode->n) / 2 + 1];
					y->pT[i + 1] = tempNode->pT[i + 1 + (tempNode->n) - ((tempNode->n) / 2)];
				}
			}
			//case m이 짝수
			else {
				y->pT[0] = tempNode->pT[(tempNode->n) - ((tempNode->n) / 2) + 1];
				for (int i = 0; i < (tempNode->n) - ((tempNode->n) / 2) - 1; i++) {
					y->key[i] = tempNode->key[i + (tempNode->n) / 2 + 1];
					y->pT[i + 1] = tempNode->pT[i + 2 + (tempNode->n) - ((tempNode->n) / 2)];
				}
			}
			if (!isEmpty()) { //아직 경로가 남았으면
				x = pop();
			}
			else {    //경로 끝나서 새로운 root생성
				T = getNode(m);
				T->key[0] = newK;
				T->n++;
				T->pT[0] = x;
				T->pT[1] = y;
				finished = true;
			}
		}

	}
	top = -1;
	return T;
}

Node* Tree::delBtree(Node *T, int m, int oldKey) {
	Node *x = T;
	int k = 0;
	while (x != NULL) {
		int a = 0;
		while (a < (x->n) && oldKey > x->key[a]) { //newKey가 더 큰 값을 찾거나 Node에 들어있는 key값 개수 전까지 탐색
			a++;
		}
		if (a < x->n && oldKey == x->key[a]) { //만약 탐색 도중 newKey값과 같은 키 값을 찾게되면
			k = a;
			break;
		}
		push(x);        //경로를 스택에 저장
		pushInd(a);
		x = x->pT[a];   //다음 바로 밑의 포인터로
	}

	if (x == NULL) { //del할 것을 못찾았을 경우
		top = -1;
		topInd = -1;
		return T;
	}

	Node *inNode = x;
	if (x->pT[0] != NULL) {//내부 노드에서 발견될 경우
		push(x);
		pushInd(k + 1);
		x = x->pT[k + 1];
		while (x != NULL) {
			push(x);
			pushInd(0);
			x = x->pT[0];
		}
		popInd();
	}

	if (x == NULL) {//내부 노드일 경우 후행키 교체
		x = pop();
		inNode->key[k] = x->key[0];
		x->key[0] = oldKey;
	}
	int temp = oldKey;
	for (int i = 0; i < x->n - 1; i++) {
		if (x->key[i] == temp) {
			x->key[i] = x->key[i + 1];
			temp = x->key[i + 1];
		}
	}
	x->n--;
	//oldkey삭제
	bool finished = false;
	Node *y = NULL;
	if (!isEmpty()) {
		y = pop(); // y = x부모
	}
	while (!finished) {
		Node * sib;
		int pos;//0 = left, 1 = right;
		int a;
		if (y != NULL) {
			a = popInd();
			if (a == 0) {
				sib = y->pT[1];
				pos = 1;
			}
			else if (a == m - 1) {
				sib = y->pT[a - 1];
				pos = 0;
			}
			else {
				if (y->pT[a + 1] == NULL) {
					sib = y->pT[a - 1];
					pos = 0;
				}
				else if (y->pT[a - 1]->n < y->pT[a + 1]->n && y->n >= a + 1) {
					sib = y->pT[a + 1];
					pos = 1;
				}
				else {
					sib = y->pT[a - 1];
					pos = 0;
				}
			}
		}

		if (x == T || x->n >= ceil(m / 2.0) - 1) {//x가 root거나 x가 underflow가 아니면
			finished = true;
		}

		else if (y->n > ceil(m / 2.0) - 1 && sib->n >= ceil(m / 2.0) - 1 || y->n == ceil(m / 2.0) - 1 && sib->n > ceil(m / 2.0) - 1) { // 키 재분배 및 합병(tree안변함)
			Node *tempNode = getNode(ceil(1.5 * m));
			if (pos == 0) {//sib 왼쪽
				tempNode->pT[0] = sib->pT[0];
				int i = 0;
				for (i = 0; i < sib->n; i++) {
					tempNode->key[i] = sib->key[i];
					tempNode->pT[i + 1] = sib->pT[i + 1];
				}
				tempNode->key[i] = y->key[a - 1];
				tempNode->pT[++i] = x->pT[0];

				for (int b = 0; i < 1 + sib->n + x->n; b++, i++) {
					tempNode->key[i] = x->key[b];
					tempNode->pT[i + 1] = x->pT[b + 1];
				}
				tempNode->n = 1 + sib->n + x->n;

				if (sib->n >ceil(m / 2.0) - 1) {//sib 여유 있으면 재분배
					sib->pT[0] = tempNode->pT[0];
					sib->n = 0;
					for (i = 0; i < tempNode->n / 2; i++) {
						sib->key[i] = tempNode->key[i];
						sib->n++;
					}
					y->key[a - 1] = tempNode->key[i];
					x->pT[0] = tempNode->pT[++i];
					for (int b = 0; i < tempNode->n; b++, i++) {
						x->key[b] = tempNode->key[i];
						x->pT[b + 1] = tempNode->pT[i + 1];
						x->n++;
					}
				}
				else {//sib 여유없음 합병
					sib->pT[0] = tempNode->pT[0];
					for (int b = 0; b < tempNode->n; b++) {
						sib->key[b] = tempNode->key[b];
						sib->pT[b + 1] = tempNode->pT[b + 1];
					}
					sib->n = tempNode->n;
					y->key[a - 1] = tempNode->key[tempNode->n - 1];
					if (a != 0) {
						for (int b = a - 1; b < y->n; b++) {           //여기야!ㄴ
							y->key[b] = y->key[b + 1];
							y->pT[b + 1] = y->pT[b + 2];
						}
						y->pT[y->n] = y->pT[y->n + 1];
						y->n--;
					}
					else {
						for (int b = a; b < y->n; b++) {
							y->key[b] = y->key[b + 1];
							y->pT[b + 1] = y->pT[b + 2];
						}
						y->pT[y->n] = y->pT[y->n + 1];
						y->n--;
					}
				}

			}
			else {//sib 오른쪽
				tempNode->pT[0] = x->pT[0];
				int i = 0;
				for (i = 0; i < x->n; i++) {
					tempNode->key[i] = x->key[i];
					tempNode->pT[i + 1] = x->pT[i + 1];
				}
				tempNode->key[i] = y->key[a];
				tempNode->pT[++i] = sib->pT[0];

				for (int b = 0; i < 1 + sib->n + x->n; b++, i++) {
					tempNode->key[i] = sib->key[b];
					tempNode->pT[i + 1] = sib->pT[b + 1];
				}
				tempNode->n = 1 + sib->n + x->n;

				if (sib->n >ceil(m / 2.0) - 1) {//sib 여유 있으면 재분배
					x->pT[0] = tempNode->pT[0];
					for (i = 0; i < tempNode->n / 2; i++) {
						x->key[i] = tempNode->key[i];
						x->pT[i + 1] = tempNode->pT[i + 1];
						x->n++;
					}
					y->key[a] = tempNode->key[i];
					sib->pT[0] = tempNode->pT[++i];
					sib->n = 0;
					for (int b = 0; i < tempNode->n; b++, i++) {
						sib->key[b] = tempNode->key[i];
						sib->pT[b + 1] = tempNode->pT[i + 1];
						sib->n++;
					}
				}
				else {//sib 여유없음 합병
					x->pT[0] = tempNode->pT[0];
					for (int b = 0; b < tempNode->n; b++) {
						x->key[b] = tempNode->key[b];
						x->pT[b + 1] = tempNode->pT[b + 1];
					}
					x->n = tempNode->n;
					y->key[a] = tempNode->key[tempNode->n - 1];
					if (a != 0) {
						for (int b = a - 1; b < y->n; b++) {
							y->key[b] = y->key[b + 1];
							y->pT[b + 1] = y->pT[b + 2];
						}
						y->pT[y->n] = y->pT[y->n + 1];
						y->n--;
					}
					else {
						for (int b = a; b < y->n; b++) {
							y->key[b] = y->key[b + 1];
							y->pT[b + 1] = y->pT[b + 2];
						}
						y->pT[y->n] = y->pT[y->n + 1];
						y->n--;
					}
				}
			}
			finished = true;
		}
		else {
			if (pos == 0) {
				sib->key[sib->n] = y->key[a - 1];
				sib->n++;
				sib->pT[sib->n] = x->pT[0];
				y->n--;
				int b = sib->n;
				for (int q = 0; b < sib->n + x->n; b++, q++) {
					sib->key[b] = x->key[q];
					sib->pT[b + 1] = x->pT[q + 1];
				}
				sib->n = sib->n + x->n;
				y->pT[a] = NULL;
			}
			else {
				x->key[x->n] = y->key[a];
				x->n++;
				x->pT[sib->n] = sib->pT[0];
				y->n--;
				int b = x->n;
				for (int q = 0; b < x->n + sib->n; b++, q++) {
					x->key[b] = sib->key[q];
					x->pT[b + 1] = sib->pT[q + 1];
				}
				x->n = x->n + sib->n;
				y->pT[a + 1] = NULL;
			}
			if (!isEmpty()) {
				x = y;
				y = pop();
			}
			else {
				if (pos == 0) {
					x = sib;
				}
				finished = true;
			}
		}
	}

	if (y == NULL || y->n == 0) {
		T = x;
		y = NULL;
	}

	top = -1;
	topInd = -1;
	return T;
}

void Tree::inorder(Node *T) {
	if (T == NULL) {
		return;
	}
	Node *x = T;
	int a = 0;
	inorder(x->pT[a]);
	while (a <= (x->n) - 1) {
		cout << x->key[a] << " ";
		inorder(x->pT[a + 1]);
		a++;
	}
}

bool Tree::isFull() {
	if (top == STACKSIZE - 1) {
		return true;
	}
	else {
		return false;
	}
}
bool Tree::isEmpty() {
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}

void Tree::push(Node *p) {
	if (isFull()) {
		return;
	}
	else {
		top++;
		S[top] = p;
	}
}

void Tree::pushInd(int p) {
	if (topInd == STACKSIZE - 1) {
		return;
	}
	else {
		topInd++;
		IndS[topInd] = p;
	}
}

Node* Tree::pop() {
	if (isEmpty()) {
		return NULL;
	}
	return (S[top--]);
}

int Tree::popInd() {
	if (topInd == -1) {
		return NULL;
	}
	return (IndS[topInd--]);
}