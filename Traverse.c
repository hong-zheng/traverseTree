#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef char BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

typedef BTNode* Type;
typedef struct Node{
	Type _data;
	struct Node* _next;
}Node;
typedef BTNode* QDataType;
typedef struct QNode{
	struct QNode* _next;
	QDataType _data;
}QNode;
typedef struct Queue{
	QNode* _front;
	QNode* _rear;
}Queue;

void  queueInit(Queue* q){
	// ��ʼ������
	q->_front = q->_rear = NULL;
}
QNode* createQNode(QDataType data){
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->_data = data;
	node->_next = NULL;
	return node;
}
// ��β���
void queuePush(Queue* q, QDataType data){
	QNode* node = createQNode(data);
	if (q->_front == NULL){
		q->_front = q->_rear = node;
	}
	else
	{
		q->_rear->_next = node;
		q->_rear = node;
	}
}
// ��ͷ����
void queuePop(Queue* q){
	if (NULL == q || q->_front == NULL){
		return;
	}
	//if (q->_front->_next == NULL){
	//	q->_front = NULL;
	//	q->_rear = NULL;
	//	return;
	//}
	QNode* cur = q->_front->_next;
	free(q->_front);
	q->_front = cur;

	// ����Ұָ��
	// ͷָ�뱻ɾ����βָ��Ҳָ��NULL������ʹ������ָ��
	if (q->_front == NULL){
		q->_rear = NULL;
	}
}

// �ж��Ƿ���Ԫ�ض����ṩ�ӿ�

// ��ȡ��ͷԪ��
QDataType queueFront(Queue* q){
	return q->_front->_data;
}

// ��βԪ��
QDataType queueBack(Queue* q){
	return q->_rear->_data;
}
// һ���п��õ���ָ���Ƿ�ΪNULL���п�

size_t queueSize(Queue* q){
	int num = 0;
	QNode* cur = q->_front;
	while (cur){
		++cur;
		cur = cur->_next;
	}
	return num;
}
int queueEmpty(Queue* q){
	if (q->_front == NULL){
		return 1;
	}
	return 0;
}
void queueDestory(Queue* q){
	QNode* cur = q->_front;
	while (cur){
		// �����һ�����
		QNode* next = cur->_next;
		// �ͷŵ�ǰ���
		free(cur);
		// ���µ�ǰ���
		cur = next;
	}
	// ʹ��λ���ָ��NULL
	q->_front = q->_rear = NULL;
}

void queueDestoryqq(Queue* q){
	QNode* cur = q->_front;
	while (cur){
		QNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	q->_front = q->_rear = NULL;
}
// ջ��ʵ��

// ������: pushFront popFront
// ˳���: pushBack popBack  ����ѡ�� ջ��ʵ�ֻ����϶���˳���ʵ��
//#pragma once
// ˳���ʵ��ջ
typedef struct Stack{
	Type* _array;
	size_t _size;
	size_t _capacity;
}Stack;
void stackInit(Stack* st, size_t n){
	st->_capacity = n;
	st->_array = (Type*)malloc(sizeof(Type)*st->_capacity);
	// ջ����Ԫ�أ�Ϊ��ջ
	st->_size = 0;
}

void stackPush(Stack* st, Type data){
	// �������
	if (st->_size == st->_capacity){
		st->_capacity *= 2;
		st->_array = (Type*)realloc(st->_array, sizeof(Type)*st->_capacity);
	}
	st->_array[++st->_size] = data;
}
void stackPop(Stack* st){
	// βɾ
	if (NULL == st){
		return;
	}
	if (st->_size){
		--st->_size;
	}
}

Type stackTop(Stack* st){
	if (st && st->_size)
		return st->_array[st->_size];
	return NULL;
}
size_t stackSize(Stack* st){
	return st->_size;
}
int stackEmpty(Stack* st){
	if (st->_size == 0){
		return 1;
	}
	return 0;
}


void stackDestory(Stack* st){
	free(st->_array);
	st->_array = NULL;
	st->_size = st->_capacity = 0;
}






//// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
BTNode* BinaryTreeCreate(BTDataType* a, int* pi){
	if (a[*pi] != '#'){
		BTNode* root = (BTNode*)malloc(sizeof(BTNode));
		root->_data = a[*pi];
		++(*pi);
		root->_left = BinaryTreeCreate(a, pi);
		++(*pi);
		root->_right = BinaryTreeCreate(a, pi);
		return root;
	}
	else{
		return NULL;
	}
}

//// ����������
// һ��ָ�벻���Ըı��ڴ��е����� �� ��main�����еľֲ���������һ��ָ�룬�����Ҫ�ö���ָ��
void BinaryTreeDestory(BTNode** root){ 
	BTNode* cur = *root;
	if (cur){
		BinaryTreeDestory(&cur->_left);
		BinaryTreeDestory(&cur->_right);
		// �ͷŵ�ǰ�ڵ�
		free(cur);
		// �ı���ڵ�ָ��
		*root = NULL;// �˴����д cur=NULL,�����ȼۣ�����һ���ֲ�����������ı����ָ��
	}
}

// �������ڵ����
// �������ۼӼ�����
void BinaryTreeCount(BTNode* root, int* num){
	if (root){
		++(*num);
		BinaryTreeCount(root->_left, num);
		BinaryTreeCount(root->_right, num);
	}
}
int BinaryTreeSize(BTNode* root){
	if ( NULL == root){
		return 0;
	}
	return BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right)+1;
}

// ������Ҷ�ӽڵ����
//void BinaryTreeLeafSize(BTNode* root,int* num){
//	if (NULL == root){
//		return 0;
//	}
//	BinaryTreeLeafSize(root->_left,num);
//	BinaryTreeLeafSize(root->_right,num);
//	if (root->_left == root->_right && root->_left == NULL){
//		++(*num);
//		return;
//	}
//}
int BinaryTreeLeafCount(BTNode* root){
	// �սڵ�
	if (NULL == root){
		return 0;
	}
	// Ҷ�ӽڵ�
	if (root->_left == NULL && root->_right == NULL){
		return 1;
	}
	// ��ǰ�ڵ��Ҷ�ӽڵ�Ϊ�����Һ��ӵ�Ҷ�ӽڵ�֮��
	return BinaryTreeLeafCount(root->_left) + BinaryTreeLeafCount(root->_right);
}

// ��������k��ڵ����
// ���������ĵ� k-1 ��ڵ�ĸ�����
int BinaryTreeLevelKSize(BTNode* root, int k){
	// ��ǰλ��ΪNULL
	if (NULL == root){
		return 0;
	}
	// ���˵�ǰ���
	if (k == 1){
		return 1;
	}
	// ���㵱ǰ�ڵ�����������֮��
	return BinaryTreeLevelKSize(root->_left, k - 1)
	      +BinaryTreeLevelKSize(root->_right, k - 1);
}

// ����������ֵΪx�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x){
	if (NULL == root){
		return NULL;
	}
	// ��ǰ�ڵ�
	if (root->_data == x){
		return root;
	}
	// ��������

	// ����ҵ��ͷ���
	BTNode* ret = BinaryTreeFind(root->_left,x);
	if (ret){
		return ret;
	}
	// ���û�ҵ��������ұߣ��ҵ����ֱ�ӷ���
	return BinaryTreeFind(root->_right,x);
}

//// �������
//// Ұ·�ӣ��������������
//void BinaryTreeLevelOrder(BTNode* root){
//	if ( root == NULL){
//		return;
//	}
//
//}
//// �ж϶������Ƿ�����ȫ������
//int BinaryTreeComplete(BTNode* root){
//	Queue q;
//	queueInit(&q);
//
//	return 0;
//}

void BinaryTreePrevOrderR(BTNode* root){
	if (root == NULL){
		return;
	}
	printf("%c ",root->_data);
	BinaryTreePrevOrderR(root->_left);
	BinaryTreePrevOrderR(root->_right);
}
void BinaryTreePrevOrder(BTNode* root){
	// ����ջģ��ݹ����
	Stack st;
	stackInit(&st,10);
	BTNode* cur = root;
	BTNode* top;
	while ( cur || stackEmpty(&st) != 1){
		while (cur){
			// ǰ����������ʵ�ǰ�ڵ�
			printf("%c ",cur->_data);
			stackPush(&st,cur);
			cur = cur->_left;
		}

		// ��ȡջ��Ԫ��
		top = stackTop(&st);
		stackPop(&st);
		// ����������
		cur = top->_right;
	}

	printf("\n");
}

// ����ǵݹ����
void BinaryTreeInOrder(BTNode* root){
	Stack st;
	stackInit(&st,10);
	BTNode *cur, *top;
	cur = root;
	while (cur || stackEmpty(&st)!=1){
		while (cur){
			stackPush(&st,cur);
			cur = cur->_left;
		}

		top = stackTop(&st);
		printf("%c ",top->_data);
		stackPop(&st);
		cur = top->_right;
	}

}
void BinaryTreeInOrderR(BTNode* root){
	if (NULL == root){
		return;
	}
	BinaryTreeInOrderR(root->_left);
	printf("%c ",root->_data);
	BinaryTreeInOrderR(root->_right);
}
// �����ݹ�
void BinaryTreeLastOrderR(BTNode* root){
	if (NULL == root){
		return;
	}
	BinaryTreeLastOrderR(root->_left);
	BinaryTreeLastOrderR(root->_right);
	printf("%c ", root->_data);
}
// �����ǵݹ�
void BinaryTreeLastOrder(BTNode* root){
	Stack st;
	stackInit(&st,10);
	BTNode *cur = root, *top, *prev=NULL;// prev ������һ�η��ʵ�λ��
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			stackPush(&st,cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		// �ж��������Ƿ�������
		// û�������� ���� �������Ѿ��������
		if (top->_right == NULL || top->_right == prev){
			printf("%c ", top->_data);
			stackPop(&st);
			prev = top;
		}
		else{ // ����������
			cur = top->_right; // 
		}
	}
}
// ����������ö��������
void BinaryTreeLevelOrder1(BTNode* root){
	Queue q;
	queueInit(&q);
	if (root)
		queuePush(&q,root);
	while ( queueEmpty(&q) != 1){
		BTNode* top = queueFront(&q);
		queuePop(&q);
		printf("%c ",top->_data);
		if (top->_left){
			queuePush(&q, top->_left);
		}
		if (top->_left){
			queuePush(&q, top->_right);
		}
	}

}
//BTNode* reverse(BTNode* head){
//	BTNode *prev, *cur, *next;
//	if (NULL == head){
//		return NULL;
//	}
//	prev = NULL;
//	cur = head;
//	next = head;
//	while (cur){
//		next = cur->next;
//		cur->next = prev;
//		prev = cur;
//		cur = next;
//	}
//	return prev;
//}

void bianliqianxu(BTNode* root){
	// ����ջģ��ݹ����
	Stack st;
	stackInit(&st,10);
	BTNode* cur = root;
	BTNode* top=NULL;
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			// ǰ����������ʵ�ǰ�ڵ�
			printf("%c ", cur->_data);
			stackPush(&st, cur);
			cur = cur->_left;
		}
		// ��ȡջ��Ԫ�أ�����������
		top = stackTop(&st);
		stackPop(&st);
		cur = top->_right;
	}
	printf("\n");
}
// ����ǵݹ����
void feidgzx(BTNode* root){
	BTNode* cur = root;
	BTNode* top = NULL;
	Stack st;
	stackInit(&st,10);
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			stackPush(&st,cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		stackPop(&st);
		printf("%c ", top->_data);
		cur = top->_right;
	}
	printf("\n");
}

// �ǵݹ����
void houxu(BTNode* root){
	BTNode* cur = root;
	BTNode* top = NULL;
	BTNode* prev = NULL; // ������һ�η��ʹ���λ��
	Stack st;
	stackInit(&st, 10);
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			stackPush(&st, cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		
		// �ж��������Ƿ�������
		// û�������������������Ѿ��������
		if (top->_right == NULL || top->_right == prev){
			// ���ʵ�ǰ�ڵ�
			printf("%c ", top->_data);
			stackPop(&st);
			prev = top;
		}
		else{
			// ��������������������û�з��ʣ���Ҫ���ȷ���������
			cur = top->_right;
		}
	}
	printf("\n");
}

// �������
void LevelTraverse(BTNode* r){
	Queue q;
	queueInit(&q);
	BTNode* cur = r;
	BTNode* top = NULL;
	if (cur)
		queuePush(&q, cur);
	while (queueEmpty(&q)!=1){
			top = queueFront(&q);
			printf("%c ", top->_data);
			queuePop(&q);
			if (top->_left){
				queuePush(&q, top->_left);
			}
			if (top->_right){
				queuePush(&q, top->_right);
			}
	}
}
void BinaryTreeLevelOrder(BTNode* root){
	// ���д�����󣬴��ϵ��£�����ÿһ��ڵ�
	Queue q;
	queueInit(&q);
	// ��Ԫ�����
	if (root)
		queuePush(&q, root);
	while (queueEmpty(&q) != 1){
		// ��ȡ��ͷԪ��
		BTNode* front = queueFront(&q);
		queuePop(&q);
		// ���ʶ�ͷԪ��
		printf("%c ", front->_data);
		// ������ӣ�������ң�˳�򲻿ɸı�
		if (front->_left)
			queuePush(&q, front->_left);
		if (front->_right)
			queuePush(&q, front->_right);
	}
}

//// �ж϶������Ƿ�����ȫ������
int BinaryTreeComplete(BTNode* root){
	// ���д�����󣬴��ϵ��£�����ÿһ��ڵ�
	Queue q;
	queueInit(&q);
	// ��Ԫ�����
	if (root)
		queuePush(&q, root);
	while (queueEmpty(&q) != 1){
		// ��ȡ��ͷԪ��
		BTNode* front = queueFront(&q);
		queuePop(&q);
		// ������ӣ�������ң�˳�򲻿ɸı�
		if (front){
			queuePush(&q, front->_left);
			queuePush(&q, front->_right);
		}
		else
			break;
	}
	// ����˵���Ѿ���һ���ǿսڵ�
	// ���ж϶�����ʣ��Ԫ���Ƿ�Ϊ�սڵ�
	while (queueEmpty(&q) != 1){
		BTNode* front = queueFront(&q);
		queuePop(&q);
		if (front){
			// ʣ��Ԫ�����зǿսڵ㣬��ʾ����һ����ȫ������
			return 0;
		}
	}
	// ��ʱ��ʾʣ��ڵ�ȫ����Ϊ�սڵ㣬���Ϊһ����ȫ������
	return 1;
}

// �ж��Ƿ�Ϊ��ȫ������
int BinaryTreeCompleteNew(BTNode* root){
	// ������У����ӣ�������г���Ϊ�գ��������ж��Ƿ��зǿսڵ�
	Queue q;
	queueInit(&q);
	if (root)
		queuePush(&q, root);
	while (queueEmpty(&q) != 1){
		BTNode* front = queueFront(&q);
		queuePop(&q);
		if (front){
			queuePush(&q, front->_left);
			queuePush(&q, front->_right);
		}
		else{
			break;
		}
	}
	// �ж�ʣ�¶����е������Ƿ��зǿսڵ�
	while (queueEmpty(&q) != 1){
		BTNode* front = queueFront(&q);
		queuePop(&q);
		if (front)
			return 0;
	}
	return 1;
}
int main(){
	//BTNode* n1 = (BTNode*)malloc(sizeof(BTNode));
	char str[] = { "ABD##E##C##"};
	int indx = 0;
	BTNode* root = BinaryTreeCreate(str,&indx);
	BinaryTreeLevelOrder(root);
	printf("\n");
	if (BinaryTreeComplete(root)){
		printf("��������ȫ������\n");
	}
	else{
		printf("��������ȫ������\n");
	}
	//bianliqianxu(root);
	//BinaryTreePrevOrderR(root);

	//void postTraverse(BTNode* root);
	//printf("\n");
	//feidgzx(root);
	//BinaryTreeInOrderR(root);
	//printf("\n");
	//postTraverse(root);
	//BinaryTreeLastOrderR(root);

	/*
	printf("ǰ��ݹ�:>\n");
	BinaryTreePrevOrderR(root);
	printf("\n");
	printf("ǰ��ǵݹ�:>\n");
	BinaryTreePrevOrder(root);
	
	printf("����ݹ�:>\n");
	BinaryTreeInOrderR(root);
	printf("\n");
	printf("����ǵݹ�:>\n");
	BinaryTreeInOrder(root);

	printf("\n����ݹ�:>\n");
	BinaryTreeLastOrderR(root);
	printf("\n");
	printf("����ǵݹ�:>\n");
	BinaryTreeLastOrder(root);
	printf("\n");
	BinaryTreeLevelOrder1(root);
	printf("\n");

	printf("%d\n",BinaryTreeSize(root));
	int num = 0;
	//BinaryTreeLeafSize(root,&num);
	printf("%d\n",num);
	printf("%d\n", BinaryTreeLeafCount(root));
	printf("%d\n", BinaryTreeLevelKSize(root, 2));

	BTNode* node = BinaryTreeFind(root, 'A');
	if (node){
		printf("%c\n", node->_data);
	}
	*/
	BinaryTreeDestory(&root);
	printf("\n");
	system("pause");
	return 0;
}

void postTraverse(BTNode* root){
	BTNode* cur = root;
	BTNode* prev = NULL;
	BTNode* top = NULL;
	Stack st;
	stackInit(&st,10);
	while (cur || stackEmpty(&st)!= 1){
		while (cur){
			stackPush(&st, cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		if (top->_right == NULL || top->_right == prev){
			printf("%c ", top->_data);
			stackPop(&st);
			prev = top;
		}
		else{
			cur = top->_right;
		}
	}
	printf("\n");
}
//// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
//BTNode* BinaryTreeCreate(BTDataType* a, int* pi){
//	if ( a[*pi] != '#'){
//		BTNode* root = (BTNode*)malloc(sizeof(BTNode));
//		root->_data = a[*pi];
//		++(*pi);
//		root->_left = BinaryTreeCreate(a, pi);
//		++(*pi);
//		root->_right = BinaryTreeCreate(a, pi);
//		return root;
//	}
//	else{
//		return NULL;
//	}
//}
//// �������ڵ����
//int BinaryTreeSize(BTNode* root);
//// ������Ҷ�ӽڵ����
//int BinaryTreeLeafSize(BTNode* root);
//// ��������k��ڵ����
//int BinaryTreeLevelKSize(BTNode* root, int k);
//// ����������ֵΪx�Ľڵ�
//BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
//// ������ǰ�����
//void BinaryTreePrevOrder(BTNode* root);
//// �������������
//void BinaryTreeInOrder(BTNode* root);
//// �������������
//void BinaryTreePostOrder(BTNode* root);
//// �������
//void BinaryTreeLevelOrder(BTNode* root);
//// �ж϶������Ƿ�����ȫ������
//int BinaryTreeComplete(BTNode* root);


int mdain(){

	char str[] = { "dshfkhfjsdaklh" };
	int x = 2;
	x *= x + 1; // �ȼ��� x*=(x+1)
	//x = int(-2.3);
	printf("%d\n", x);
	switch (x){
	case 2 + 4:
		printf("6");
		break;
	}
	system("pause");
	return 0;
}

int masin(){
	char str[] = "ABD##E#H##CF##G##";
	int indx = 0;
	BTNode* root = BinaryTreeCreate(str, &indx);
	printf("\n");
	system("pause");
	return 0;
}
//
//typedef char BTDataType;
//typedef struct BinaryTreeNode
//{
//	BTDataType _data;
//	struct BinaryTreeNode* _left;
//	struct BinaryTreeNode* _right;
//}BTNode;
//// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
//BTNode* BinaryTreeCreate(BTDataType* a, int* pi){
//	if (a[*pi] != '#'){
//		BTNode* root = (BTNode*)malloc(sizeof(BTNode));
//		root->_data = a[*pi];
//		++(*pi);
//		root->_left = BinaryTreeCreate(a, pi);
//		++(*pi);
//		root->_right = BinaryTreeCreate(a, pi);
//		return root;
//	}
//	else{
//		return NULL;
//	}
//}
//// ����������
//void BinaryTreeDestory(BTNode** root){
//	BTNode* cur = *root;
//	if (cur){
//		BinaryTreeDestory(&cur->_left);
//		BinaryTreeDestory(&cur->_right);
//		free(cur);
//		*root = NULL;
//	}
//}
//// �������ڵ����: ���������ڵ� + 1
//// �������ۼӼ�����
//int treeSize(BTNode* root){
//	if (NULL == root){
//		return 0;
//	}
//	return treeSize(root->_left) + treeSize(root->_right) + 1;
//}
//void BinaryTreeSize(BTNode* root, int* num){
//	if (root){
//		++(*num);
//		BinaryTreeSize(root->_left, num);
//		BinaryTreeSize(root->_right, num);
//	}
//}
//// ������Ҷ�ӽڵ����
//int BinaryTreeLeafSize(BTNode* root){
//	if (NULL == root){
//		return 0;
//	}
//	if (root->_left == NULL && root->_right == NULL){
//		return 1;
//	}
//	return BinaryTreeLeafSize(root->_left)
//		+ BinaryTreeLeafSize(root->_right);
//
//}
//// ��������k��ڵ����
//int BinaryTreeLevelKSize(BTNode* root, int k){
//
//}
//// ����������ֵΪx�Ľڵ�
//BTNode* BinaryTreeFind(BTNode* root, BTDataType x){
//
//}
//// ������ǰ�����
//void BinaryTreePrevOrder(BTNode* root){
//
//}
//// �������������
//void BinaryTreeInOrder(BTNode* root){
//
//}
//// �������������
//void BinaryTreePostOrder(BTNode* root){
//
//}
//// �������
//void BinaryTreeLevelOrder(BTNode* root){
//
//}
//// �ж϶������Ƿ�����ȫ������
//int BinaryTreeComplete(BTNode* root){
//
//}
//
//int mainw(){
//
//	char str[] = { "ABD##E#H##CF##G##" };
//	int indx = 0;
//	int num = 0;
//	BTNode* root = BinaryTreeCreate(str, &indx);
//	BinaryTreeSize(root, &num);
//	printf(" num = %d\n", num);
//	printf("%d\n", treeSize(root));
//	printf("%d \n", BinaryTreeLeafSize(root));
//	BinaryTreeDestory(&root);
//	system("pause");
//	return 0;
//}
//
//
//
//int getH(struct TreeNode* root){
//	if (root == NULL){
//		return 0;
//	}
//	int l = getH(root->left);
//	int r = getH(root->right);
//	return l>r ? l + 1 : r + 1;
//}
//bool isBalanced(struct TreeNode* root){
//	// ����ÿһ���ڵ� �� �ж����������߶�����Ƿ񳬹�1
//	if (root == NULL){ // �����϶�Ϊƽ��������˷���true
//		return true;
//	}
//	int l = getH(root->left);
//	int r = getH(root->right);
//
//	// ��Ҫͬʱ��֤��ǰ�ڵ��Լ�������������ƽ����������һ������
//	// ��Ҫ��֤������������ʱ�������������
//	return abs(l - r)<2
//		&& isBalanced(root->left)
//		&& isBalanced(root->right);
//}
//
//
//#include<stdio.h>
//#include<stdlib.h>
//typedef struct Node{
//	char val;
//	struct Node* left;
//	struct Node* right;
//}Node;
//Node* createTree(char* str, int* idx){
//	if (str[*idx] != '#'){
//		// �������ڵ�
//		Node* root = (Node*)malloc(sizeof(Node));
//		root->val = str[*idx];
//		++(*idx);
//		root->left = createTree(str, idx);
//		++(*idx);
//		root->right = createTree(str, idx);
//		return root;
//	}
//	else{
//		return NULL;
//	}
//}
//void centerT(struct Node* root){
//	if (NULL == root){
//		return;
//	}
//	centerT(root->left);
//	printf("%c ", root->val);
//	centerT(root->right);
//}
//int main(){
//	char str[1024];
//	int indx = 0;
//	scanf("%s", str);
//	Node* root = createTree(str, &indx);
//	centerT(root);
//	return 0;
//}
//
//
//
// ����һ����
// ����ָ��+���鷽ʽ
//
//#include<stdio.h>
//#include<stdlib.h>
//typedef struct Node{
//	char val;
//	struct Node* _left;
//	struct Node* _right;
//}Node;
//// Node* createTree(char* str,int* idx){
//Node* createTree(char** str){
//	if (**str != '#'){
//		// �������ڵ�
//		Node* root = (Node*)malloc(sizeof(Node));
//		root->val = **str;
//		++(*str);
//		root->_left = createTree(str);
//		++(*str);
//		root->_right = createTree(str);
//		return root;
//	}
//	else{
//		return NULL;
//	}
//}
//void inorder(Node* root){
//	if (NULL == root){
//		return;
//	}
//	inorder(root->_left);
//	printf("%c ", root->val);
//	inorder(root->_right);
//}
//int main(){
//	//char str[101];
//	char* str = (char*)malloc(sizeof(char) * 101);
//	scanf("%s", str);
//	int indx = 0;
//	//    Node* root = createTree(str,&indx);
//	Node* root = createTree(&str);
//	inorder(root);
//	printf("\n");
//	return 0;
//}
