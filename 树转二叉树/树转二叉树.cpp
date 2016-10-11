
//
//  main.cpp
//  ��ת������
//
//  Created by ������ on 16/3/26.
//  Copyright ? 2016�� HIT. All rights reserved.
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
	//�˴�������������f=F,����Ḳ�ǣ����ֻ�����һ����
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
	cout << "�������ܣ�" << endl;
	cout << "                      1.���ֶ����뷽ʽ��ɭ�֣���������������" << endl;
	cout << "                      2.���ļ����뷽ʽ��ɭ�ֻ��������" << endl;
	cout << "                      3.��ת�����������ȣ��У����������" << endl;
	cout << "                      4.������תɭ�֣����ȣ��������������ѹ���������" << endl;
	cout << "***--------------------------------------------------------------------------***" << endl;
	output << "***------------------------------------------------------------------------***" << endl;
	output << "�������ܣ�" << endl;
	output << "                      1.���ֶ����뷽ʽ��ɭ�֣���������������" << endl;
	output << "                      2.���ļ����뷽ʽ��ɭ�ֻ��������" << endl;
	output << "                      3.��ת�����������ȣ��У����������" << endl;
	output << "                      4.������תɭ�֣����ȣ��������������ѹ���������" << endl;
	output << "***--------------------------------------------------------------------------***" << endl;

	int num;
	BTree BT=NULL;
	ForestNode T;
	T = (ForestNode)malloc(sizeof(Forest));
	T->next = NULL;	
	cout << "��ѡ��ɭ�ַ�ʽ��";
	output << "�û���ѡ��";
	cin >> num;
	output << num << endl;
	switch (num) {
	case 1:
		cout << "�����ת�������Թ�����ʾ����";
		output << "�û����������";
		ListToForestLink(T);
		break;
	case 2:
		cout << "���ļ���ȡ���ݽ�ɭ�֣�" << endl;
		output << "���ļ���ȡ���ݣ�";
		ListToForest(T);
		break;
	default:
		break;
	}
	cout << "ɭ�ֵ����������";
	output << endl << "ɭ�ֵ����������";
	ForestPre(T);
	cout << endl << "ɭ�ֵĺ��������";
	output << endl << "ɭ�ֵĺ��������";
	ForestNext(T);
	cout << endl << "ɭ��ת���ɶ������ɹ���" << endl;
	output << endl << "ɭ��ת���ɶ������ɹ���" << endl;
	ForestToBT(T, BT);
	cout << "�����������������";
	output << endl << "�����������������";
	BTreePre(BT);
	cout << endl << "�����������������";
	output << endl << "�����������������";
	BTreeCenter(BT);
	cout << endl << "�������ĺ��������";
	output << endl << "�������ĺ��������";
	BTreeNext(BT);
	cout << endl;
	output << endl;
	ForestNode F;
	F = (ForestNode)malloc(sizeof(Forest));
	F->next = NULL;
	cout << "��ѡ�񽨶�������ʽ��";
	output << "�û�ѡ��Ľ�����ʽ��";
	cin >> num;
	output << num;
	switch (num) {
	case 1:
		cout << "����Ԫ�ؽ���������";
		output << endl << "�û������Ԫ�أ�";
		CreateBTree(BT);
		break;
	case 2:
		cout << "���ļ���ʽ����������" << endl;
		output << endl << "���ļ���ʽ����������" << endl;
		output << "�ļ�Ԫ��Ϊ��";
		CreateBT(BT);
		break;
	default:
		break;
	}
	cout << "�����������������";
	output << endl << "�����������������";
	BTreePre(BT);
	cout << endl << "�����������������";
	output << endl << "�����������������";
	BTreeCenter(BT);
	cout << endl << "�������ĺ��������";
	output << endl << "�������ĺ��������";
	BTreeNext(BT);
	BTreeToForest(F, BT);
	cout << endl << "������ת�������ɹ���" << endl;
	output << endl << "������ת�������ɹ���" << endl << endl;
	cout << "ɭ�ֵ����������";
	output << "ɭ�ֵ����������";
	ForestPre(F);
	cout << endl << "ɭ�ֵĺ��������";
	output << endl << "ɭ�ֵĺ��������";
	ForestNext(F);
	cout << endl << "ɭ�ֵĹ�����ʾ��";
	output << endl << "ɭ�ֵĹ�����ʾ��";
	ForestToList(F);
	cout << endl;
	output << endl;
	system("pause");
	return 0;
}