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
	// 初始化队列
	q->_front = q->_rear = NULL;
}
QNode* createQNode(QDataType data){
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->_data = data;
	node->_next = NULL;
	return node;
}
// 队尾入队
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
// 队头出队
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

	// 处理野指针
	// 头指针被删除，尾指针也指向NULL，不能使其随意指向
	if (q->_front == NULL){
		q->_rear = NULL;
	}
}

// 判断是否还有元素对外提供接口

// 获取队头元素
QDataType queueFront(Queue* q){
	return q->_front->_data;
}

// 队尾元素
QDataType queueBack(Queue* q){
	return q->_rear->_data;
}
// 一般判空用的是指针是否为NULL来判空

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
		// 存放下一个结点
		QNode* next = cur->_next;
		// 释放当前结点
		free(cur);
		// 更新当前结点
		cur = next;
	}
	// 使首位结点指向NULL
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
// 栈的实现

// 单链表: pushFront popFront
// 顺序表: pushBack popBack  优先选择 栈的实现基本上都是顺序表实现
//#pragma once
// 顺序表实现栈
typedef struct Stack{
	Type* _array;
	size_t _size;
	size_t _capacity;
}Stack;
void stackInit(Stack* st, size_t n){
	st->_capacity = n;
	st->_array = (Type*)malloc(sizeof(Type)*st->_capacity);
	// 栈中无元素，为空栈
	st->_size = 0;
}

void stackPush(Stack* st, Type data){
	// 检查容量
	if (st->_size == st->_capacity){
		st->_capacity *= 2;
		st->_array = (Type*)realloc(st->_array, sizeof(Type)*st->_capacity);
	}
	st->_array[++st->_size] = data;
}
void stackPop(Stack* st){
	// 尾删
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






//// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
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

//// 二叉树销毁
// 一级指针不可以改变内存中的内容 ， 在main函数中的局部变量就是一级指针，因此需要用二级指针
void BinaryTreeDestory(BTNode** root){ 
	BTNode* cur = *root;
	if (cur){
		BinaryTreeDestory(&cur->_left);
		BinaryTreeDestory(&cur->_right);
		// 释放当前节点
		free(cur);
		// 改变根节点指向
		*root = NULL;// 此处如果写 cur=NULL,并不等价，这是一个局部变量，不会改变根的指向
	}
}

// 二叉树节点个数
// 遍历，累加计数器
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

// 二叉树叶子节点个数
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
	// 空节点
	if (NULL == root){
		return 0;
	}
	// 叶子节点
	if (root->_left == NULL && root->_right == NULL){
		return 1;
	}
	// 当前节点的叶子节点为起左右孩子的叶子节点之和
	return BinaryTreeLeafCount(root->_left) + BinaryTreeLeafCount(root->_right);
}

// 二叉树第k层节点个数
// 左右子树的第 k-1 层节点的个数和
int BinaryTreeLevelKSize(BTNode* root, int k){
	// 当前位置为NULL
	if (NULL == root){
		return 0;
	}
	// 到了当前层次
	if (k == 1){
		return 1;
	}
	// 满足当前节点条件的左右之和
	return BinaryTreeLevelKSize(root->_left, k - 1)
	      +BinaryTreeLevelKSize(root->_right, k - 1);
}

// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x){
	if (NULL == root){
		return NULL;
	}
	// 当前节点
	if (root->_data == x){
		return root;
	}
	// 左右子树

	// 左边找到就返回
	BTNode* ret = BinaryTreeFind(root->_left,x);
	if (ret){
		return ret;
	}
	// 左边没找到，就找右边，找到与否直接返回
	return BinaryTreeFind(root->_right,x);
}

//// 层序遍历
//// 野路子，先先序后层序出列
//void BinaryTreeLevelOrder(BTNode* root){
//	if ( root == NULL){
//		return;
//	}
//
//}
//// 判断二叉树是否是完全二叉树
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
	// 借助栈模拟递归过程
	Stack st;
	stackInit(&st,10);
	BTNode* cur = root;
	BTNode* top;
	while ( cur || stackEmpty(&st) != 1){
		while (cur){
			// 前序遍历，访问当前节点
			printf("%c ",cur->_data);
			stackPush(&st,cur);
			cur = cur->_left;
		}

		// 获取栈顶元素
		top = stackTop(&st);
		stackPop(&st);
		// 访问右子树
		cur = top->_right;
	}

	printf("\n");
}

// 中序非递归遍历
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
// 后续递归
void BinaryTreeLastOrderR(BTNode* root){
	if (NULL == root){
		return;
	}
	BinaryTreeLastOrderR(root->_left);
	BinaryTreeLastOrderR(root->_right);
	printf("%c ", root->_data);
}
// 后续非递归
void BinaryTreeLastOrder(BTNode* root){
	Stack st;
	stackInit(&st,10);
	BTNode *cur = root, *top, *prev=NULL;// prev 标记最后一次访问的位置
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			stackPush(&st,cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		// 判断右子树是否访问完成
		// 没有右子树 或者 右子树已经访问完成
		if (top->_right == NULL || top->_right == prev){
			printf("%c ", top->_data);
			stackPop(&st);
			prev = top;
		}
		else{ // 访问右子树
			cur = top->_right; // 
		}
	}
}
// 层序遍历利用队列来完成
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
	// 借助栈模拟递归过程
	Stack st;
	stackInit(&st,10);
	BTNode* cur = root;
	BTNode* top=NULL;
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			// 前序遍历，访问当前节点
			printf("%c ", cur->_data);
			stackPush(&st, cur);
			cur = cur->_left;
		}
		// 获取栈顶元素，访问右子树
		top = stackTop(&st);
		stackPop(&st);
		cur = top->_right;
	}
	printf("\n");
}
// 中序非递归遍历
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

// 非递归后序
void houxu(BTNode* root){
	BTNode* cur = root;
	BTNode* top = NULL;
	BTNode* prev = NULL; // 标记最后一次访问过的位置
	Stack st;
	stackInit(&st, 10);
	while (cur || stackEmpty(&st) != 1){
		while (cur){
			stackPush(&st, cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		
		// 判断右子树是否访问完成
		// 没有右子树或者右子树已经访问完成
		if (top->_right == NULL || top->_right == prev){
			// 访问当前节点
			printf("%c ", top->_data);
			stackPop(&st);
			prev = top;
		}
		else{
			// 右子树存在且右子树还没有访问，需要首先访问右子树
			cur = top->_right;
		}
	}
	printf("\n");
}

// 层序遍历
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
	// 队列从左向后，从上到下，保存每一层节点
	Queue q;
	queueInit(&q);
	// 根元素入队
	if (root)
		queuePush(&q, root);
	while (queueEmpty(&q) != 1){
		// 获取队头元素
		BTNode* front = queueFront(&q);
		queuePop(&q);
		// 访问队头元素
		printf("%c ", front->_data);
		// 孩子入队，先左后右，顺序不可改变
		if (front->_left)
			queuePush(&q, front->_left);
		if (front->_right)
			queuePush(&q, front->_right);
	}
}

//// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root){
	// 队列从左向后，从上到下，保存每一层节点
	Queue q;
	queueInit(&q);
	// 根元素入队
	if (root)
		queuePush(&q, root);
	while (queueEmpty(&q) != 1){
		// 获取队头元素
		BTNode* front = queueFront(&q);
		queuePop(&q);
		// 孩子入队，先左后右，顺序不可改变
		if (front){
			queuePush(&q, front->_left);
			queuePush(&q, front->_right);
		}
		else
			break;
	}
	// 到这说明已经有一个非空节点
	// 再判断队列中剩余元素是否都为空节点
	while (queueEmpty(&q) != 1){
		BTNode* front = queueFront(&q);
		queuePop(&q);
		if (front){
			// 剩余元素中有非空节点，表示不是一颗完全二叉树
			return 0;
		}
	}
	// 此时表示剩余节点全部都为空节点，因此为一颗完全二叉树
	return 1;
}

// 判断是否为完全二叉树
int BinaryTreeCompleteNew(BTNode* root){
	// 放入队列，出队，如果队列出队为空，跳出，判断是否还有非空节点
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
	// 判断剩下队列中的数据是否还有非空节点
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
		printf("该树是完全二叉树\n");
	}
	else{
		printf("该树非完全二叉树\n");
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
	printf("前序递归:>\n");
	BinaryTreePrevOrderR(root);
	printf("\n");
	printf("前序非递归:>\n");
	BinaryTreePrevOrder(root);
	
	printf("中序递归:>\n");
	BinaryTreeInOrderR(root);
	printf("\n");
	printf("中序非递归:>\n");
	BinaryTreeInOrder(root);

	printf("\n后序递归:>\n");
	BinaryTreeLastOrderR(root);
	printf("\n");
	printf("后序非递归:>\n");
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
//// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
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
//// 二叉树节点个数
//int BinaryTreeSize(BTNode* root);
//// 二叉树叶子节点个数
//int BinaryTreeLeafSize(BTNode* root);
//// 二叉树第k层节点个数
//int BinaryTreeLevelKSize(BTNode* root, int k);
//// 二叉树查找值为x的节点
//BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
//// 二叉树前序遍历
//void BinaryTreePrevOrder(BTNode* root);
//// 二叉树中序遍历
//void BinaryTreeInOrder(BTNode* root);
//// 二叉树后序遍历
//void BinaryTreePostOrder(BTNode* root);
//// 层序遍历
//void BinaryTreeLevelOrder(BTNode* root);
//// 判断二叉树是否是完全二叉树
//int BinaryTreeComplete(BTNode* root);


int mdain(){

	char str[] = { "dshfkhfjsdaklh" };
	int x = 2;
	x *= x + 1; // 等价于 x*=(x+1)
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
//// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
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
//// 二叉树销毁
//void BinaryTreeDestory(BTNode** root){
//	BTNode* cur = *root;
//	if (cur){
//		BinaryTreeDestory(&cur->_left);
//		BinaryTreeDestory(&cur->_right);
//		free(cur);
//		*root = NULL;
//	}
//}
//// 二叉树节点个数: 左右子树节点 + 1
//// 遍历，累加计数器
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
//// 二叉树叶子节点个数
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
//// 二叉树第k层节点个数
//int BinaryTreeLevelKSize(BTNode* root, int k){
//
//}
//// 二叉树查找值为x的节点
//BTNode* BinaryTreeFind(BTNode* root, BTDataType x){
//
//}
//// 二叉树前序遍历
//void BinaryTreePrevOrder(BTNode* root){
//
//}
//// 二叉树中序遍历
//void BinaryTreeInOrder(BTNode* root){
//
//}
//// 二叉树后序遍历
//void BinaryTreePostOrder(BTNode* root){
//
//}
//// 层序遍历
//void BinaryTreeLevelOrder(BTNode* root){
//
//}
//// 判断二叉树是否是完全二叉树
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
//	// 遍历每一个节点 ， 判断左右子树高度相差是否超过1
//	if (root == NULL){ // 空树肯定为平衡树，因此返回true
//		return true;
//	}
//	int l = getH(root->left);
//	int r = getH(root->right);
//
//	// 需要同时保证当前节点以及左右子树都是平衡树都满足一个条件
//	// 需要保证如下三个条件时可以用以下语句
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
//		// 建立根节点
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
// 创建一棵树
// 二级指针+数组方式
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
//		// 建立根节点
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
