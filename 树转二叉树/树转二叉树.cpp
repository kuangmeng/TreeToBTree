
//
//  main.cpp
//  树转二叉树
//
//  Created by 匡盟盟 on 16/3/26.
//  Copyright ? 2016年 HIT. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#define MAX 100
using namespace std;
ofstream output("output.txt");
typedef char Elem;
typedef struct Node {
	Elem data;
	struct Node *lchild, *rchild;
} BTNode, *BTree;
typedef struct TLNode {
	Elem index;
	struct TLNode *next;
} TreeLink, *LinkNode;
typedef struct {
	LinkNode link;
	Elem data;
} TNode, *TreeNode;
typedef struct Tree {
	TreeNode tree;
	struct Tree *next;
} Forest, *ForestNode;
void InsertForest(ForestNode &F, TreeNode node) {
	//此处必须另外申明f=F,否则会覆盖，最后只有最后一棵树
	ForestNode f = F;
	ForestNode p = (ForestNode)malloc(sizeof(Forest));
	while (f->next){
		f = f->next;
	}
	p->tree = node;
	f->next = p;
	p->next = NULL;
}
void ListToTree(TreeNode &T, int index, int &index1) {
	char ch;
	LinkNode p;
	LinkNode q = (LinkNode)malloc(sizeof(TreeLink));
	q->index = index1;
	q->next = NULL;
	T[index].link = q;
	while (1) {
		cin >> ch;
		if (ch == '(') {
			index = index1;
			index1++;
			cin >> T[index1].data;
			output << T[index1].data;
			T[index1].link = NULL;
			ListToTree(T, index, index1);
		}
		else if (ch == ',') {
			index1++;
			cin >> T[index1].data;
			output << T[index1].data;
			T[index1].link = NULL;
			p = (LinkNode)malloc(sizeof(TreeLink));
			p->index = index1;
			p->next = NULL;
			q->next = p;
			q = q->next;
		}
		else {
			return;
		}
	}
}
void ListToForestLink(ForestNode &F) {
	char ch;
	int index, index1;
	TreeNode t;
	cin >> ch;
	output << ch;
	while (ch != '#') {
		index1 = -1;
		t = (TreeNode)malloc(MAX * sizeof(TNode));
		index1++;
		cin >> t[index1].data;
		output << t[index1].data;
		t[index1].link = NULL;
		cin >> ch;
		output << ch;
		if (ch != ')') {
			index = index1;
			index1++;
			cin >> t[index1].data;
			output << t[index1].data;
			t[index1].link = NULL;
			ListToTree(t, index, index1);
			cin >> ch;
			output << ch;
		}
		InsertForest(F, t);
		cin >> ch;
		output << ch;
	}
}
ifstream input("input.txt");
void ListToT(TreeNode &T, int index, int &index1) {
	char ch;
	LinkNode p;
	LinkNode q = (LinkNode)malloc(sizeof(TreeLink));
	q->index = index1;
	q->next = NULL;
	T[index].link = q;
	while (1) {
		input >> ch;
		output << ch;
		if (ch == '(') {
			index = index1;
			index1++;
			input >> T[index1].data;
			output << T[index1].data;
			T[index1].link = NULL;
			ListToTree(T, index, index1);
		}
		else if (ch == ',') {
			index1++;
			input >> T[index1].data;
			output << T[index1].data;
			T[index1].link = NULL;
			p = (LinkNode)malloc(sizeof(TreeLink));
			p->index = index1;
			p->next = NULL;
			q->next = p;
			q = q->next;
		}else return;
	}
}
void ListToForest(ForestNode &F) {
	char ch;
	int index, index1;
	TreeNode t;
	input >> ch;
	output << ch;
	while (ch != '#') {
		index1 = -1;
		t = (TreeNode)malloc(MAX * sizeof(TNode));
		index1++;
		input >> t[index1].data;
		output << t[index1].data;
		t[index1].link = NULL;
		input >> ch;
		output << ch;
		if (ch != ')') {
			index = index1;
			index1++;
			input >> t[index1].data;
			output << t[index1].data;
			t[index1].link = NULL;
			ListToT(t, index, index1);
			input >> ch;
			output << ch;
		}
		InsertForest(F, t);
		input >> ch;
		output << ch;
	}
}
void TreePre(TreeNode &t, int index) {
	LinkNode p;
	cout << setw(5) << t[index].data;
	output << setw(5) << t[index].data;
	p = t[index].link;
	while (p) {
		TreePre(t, p->index);
		p = p->next;
	}
}
void ForestPre(ForestNode &F) {
	ForestNode P = F->next;
	while (P) {
		TreePre(P->tree, 0);
		P = P->next;
	}
}
void TreeNext(TreeNode &t, int index) {
	LinkNode P;
	P = t[index].link;
	while (P){
		TreeNext(t, P->index);
		P = P->next;
	}
	cout << setw(5) << t[index].data;
	output << setw(5) << t[index].data;
}
void ForestNext(ForestNode &F){
	ForestNode P = F->next;
	while (P) {
		TreeNext(P->tree, 0);
		P = P->next;
	}
}
void TreeToBT(TreeNode &t, BTree &BT, int index){
	BTree q = (BTree)malloc(sizeof(BTNode));
	q->data = t[index].data;
	q->lchild = NULL;
	q->rchild = NULL;
	BT = q;
	LinkNode p = t[index].link;
	BTree tmp = BT;
	if (p) {
		TreeToBT(t, tmp->lchild, p->index);
		p = p->next;
		tmp = tmp->lchild;
		while (p) {
			TreeToBT(t, tmp->rchild, p->index);
			p = p->next;
			tmp = tmp->rchild;
		}
	}
}
void ForestToBT(ForestNode &F, BTree &BT) {
	ForestNode p = F->next;
	BTree q = BT;
	while (p) {
		if (!BT) {
			TreeToBT(p->tree, BT, 0);
			q = BT;
		}
		else {
			TreeToBT(p->tree, q->rchild, 0);
			q = q->rchild;
		}
		p = p->next;
	}
}
void BTreePre(BTree &BT) {
	if (BT) {
		cout << setw(5) << BT->data;
		output << setw(5) << BT->data;
		if (BT->lchild != NULL)  BTreePre(BT->lchild);
		if (BT->rchild != NULL)  BTreePre(BT->rchild);
	}
}
void BTreeCenter(BTree &BT) {
	if (BT) {
		if (BT->lchild) BTreeCenter(BT->lchild);
		cout << setw(5) << BT->data;
		output << setw(5) << BT->data;
		if (BT->rchild) BTreeCenter(BT->rchild);
	}
}
void BTreeNext(BTree &BT) {
	if (BT) {
		if (BT->lchild) BTreeCenter(BT->lchild);
		if (BT->rchild) BTreeCenter(BT->rchild);
		cout << setw(5) << BT->data;
		output << setw(5) << BT->data;
	}
}
void CreateBTree(BTree &BT) {
	Elem  ch;
	cin >> ch;
	output << ch;
	if ('#' == ch) {
		BT = NULL;
	}
	else {
		BT = (BTree)malloc(sizeof(BTNode));
		BT->data = ch;
		CreateBTree(BT->lchild);
		CreateBTree(BT->rchild);
	}
}
ifstream input2("input2.txt");
void CreateBT(BTree &BT) {
	Elem  ch;
	input2 >> ch;
	output << ch;
	if ('#' == ch) {
		BT = NULL;
	}
	else {
		BT = (BTree)malloc(sizeof(BTNode));
		BT->data = ch;
		CreateBT(BT->lchild);
		CreateBT(BT->rchild);
	}
}
void BTreeToTree(TreeNode &t, BTree &BT, int &index, int index1) {
	BTree p = BT->lchild;
	LinkNode q;
	if (p != NULL) {
		index++;
		t[index].data = p->data;
		t[index].link = NULL;
		q = (LinkNode)malloc(sizeof(TreeLink));
		q->index = index;
		q->next = NULL;
		t[index1].link = q;
		BTreeToTree(t, p, index, q->index);
		while (p->rchild) {
			p = p->rchild;
			index++;
			t[index].data = p->data;
			t[index].link = NULL;
			q->next = (LinkNode)malloc(sizeof(TreeLink));
			q = q->next;
			q->index = index;
			q->next = NULL;
			BTreeToTree(t, p, index, q->index);
		}
	}
}
void BTreeToForest(ForestNode &F, BTree &BT) {
	int index, index1;
	TreeNode q;
	BTree p = BT;
	do {
		q = (TreeNode)malloc(sizeof(TNode) * MAX);
		index = 0;
		index1 = index;
		q[index].data = p->data;
		q[index].link = NULL;
		BTreeToTree(q, p, index, index1);
		InsertForest(F, q);
		p = p->rchild;
	} while (p);
}
void TreeToList(TreeNode &t, int index) {
	LinkNode p = t[index].link;
	if (p) {
		cout << "(";
		output << "(";
		cout << t[p->index].data;
		output << t[p->index].data;
		TreeToList(t, p->index);
		p = p->next;
		while (p) {
			cout << ",";
			output << ",";
			cout << t[p->index].data;
			output << t[p->index].data;
			TreeToList(t, p->index);
			p = p->next;
		}
		cout << ")";
		output << ")";
	}
}
void ForestToList(ForestNode &F) {
	int index;
	ForestNode p = F->next;
	while (p != NULL) {
		index = 0;
		cout << "(";
		output << "(";
		cout << p->tree[0].data;
		output << p->tree[0].data;
		TreeToList(p->tree, index);
		cout << ")";
		output << ")";
		p = p->next;
	}
	cout << "!";
	output << "!";
}
int main(int argc, const char * argv[]) {
	cout << "***--------------------------------------------------------------------------***" << endl;
	cout << "本程序功能：" << endl;
	cout << "                      1.以手动输入方式建森林（广义表）或二叉树；" << endl;
	cout << "                      2.以文件读入方式建森林或二叉树；" << endl;
	cout << "                      3.树转二叉树，并先，中，后序遍历；" << endl;
	cout << "                      4.二叉树转森林，并先，后序遍历，最后已广义表输出。" << endl;
	cout << "***--------------------------------------------------------------------------***" << endl;
	output << "***------------------------------------------------------------------------***" << endl;
	output << "本程序功能：" << endl;
	output << "                      1.以手动输入方式建森林（广义表）或二叉树；" << endl;
	output << "                      2.以文件读入方式建森林或二叉树；" << endl;
	output << "                      3.树转二叉树，并先，中，后序遍历；" << endl;
	output << "                      4.二叉树转森林，并先，后序遍历，最后已广义表输出。" << endl;
	output << "***--------------------------------------------------------------------------***" << endl;

	int num;
	BTree BT=NULL;
	ForestNode T;
	T = (ForestNode)malloc(sizeof(Forest));
	T->next = NULL;	
	cout << "请选择建森林方式：";
	output << "用户的选择：";
	cin >> num;
	output << num << endl;
	switch (num) {
	case 1:
		cout << "输入待转换树（以广义表表示）：";
		output << "用户输入的树：";
		ListToForestLink(T);
		break;
	case 2:
		cout << "从文件读取数据建森林！" << endl;
		output << "从文件读取数据：";
		ListToForest(T);
		break;
	default:
		break;
	}
	cout << "森林的先序遍历：";
	output << endl << "森林的先序遍历：";
	ForestPre(T);
	cout << endl << "森林的后序遍历：";
	output << endl << "森林的后序遍历：";
	ForestNext(T);
	cout << endl << "森林转化成二叉树成功！" << endl;
	output << endl << "森林转化成二叉树成功！" << endl;
	ForestToBT(T, BT);
	cout << "二叉树的先序遍历：";
	output << endl << "二叉树的先序遍历：";
	BTreePre(BT);
	cout << endl << "二叉树的中序遍历：";
	output << endl << "二叉树的中序遍历：";
	BTreeCenter(BT);
	cout << endl << "二叉树的后序遍历：";
	output << endl << "二叉树的后序遍历：";
	BTreeNext(BT);
	cout << endl;
	output << endl;
	ForestNode F;
	F = (ForestNode)malloc(sizeof(Forest));
	F->next = NULL;
	cout << "请选择建二叉树方式：";
	output << "用户选择的建树方式：";
	cin >> num;
	output << num;
	switch (num) {
	case 1:
		cout << "输入元素建二叉树：";
		output << endl << "用户输入的元素：";
		CreateBTree(BT);
		break;
	case 2:
		cout << "以文件形式建二叉树！" << endl;
		output << endl << "以文件方式建二叉树！" << endl;
		output << "文件元素为：";
		CreateBT(BT);
		break;
	default:
		break;
	}
	cout << "二叉树的先序遍历：";
	output << endl << "二叉树的先序遍历：";
	BTreePre(BT);
	cout << endl << "二叉树的中序遍历：";
	output << endl << "二叉树的中序遍历：";
	BTreeCenter(BT);
	cout << endl << "二叉树的后序遍历：";
	output << endl << "二叉树的后序遍历：";
	BTreeNext(BT);
	BTreeToForest(F, BT);
	cout << endl << "二叉树转化成树成功！" << endl;
	output << endl << "二叉树转化成树成功！" << endl << endl;
	cout << "森林的先序遍历：";
	output << "森林的先序遍历：";
	ForestPre(F);
	cout << endl << "森林的后序遍历：";
	output << endl << "森林的后序遍历：";
	ForestNext(F);
	cout << endl << "森林的广义表表示：";
	output << endl << "森林的广义表表示：";
	ForestToList(F);
	cout << endl;
	output << endl;
	system("pause");
	return 0;
}