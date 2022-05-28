#include <iostream>
#include "avl_tree.hpp"
#include <time.h>
#include <cmath>
using namespace std;
#pragma once
typedef unsigned long long INT_64;

//���������� � ��������� ���������� LineRand()
static INT_64 RRand = 15750;
const INT_64 mRand = (1ULL << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

//������� ��������� ������� ���������� ����� �� ����� ����������
void sRand() { srand(time(0)); RRand = (INT_64)rand(); }

//������� ��������� ���������� �����
//�������� ������������ ���������    Xi+1=(a*Xi+c)%m
//habr.com/ru/post/208178
INT_64 LineRand()
{
	INT_64 y1, y2;
	y1 = (aRand * RRand + cRand) % mRand;
	y2 = (aRand * y1 + cRand) % mRand;
	RRand = (y1 & 0xFFFFFFFF00000000LL) ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
	return RRand;
}

void test_rand(int n){
	//�������� ������ ��� 64 � ��������� ������ ���� INT_64
	Tree< INT_64, int > tree;
	AVL_Tree< INT_64, int > tree1;
	//������ ��� ������, ������� ������������ � ������ 
	INT_64* m = new INT_64[n];
	//��������� ������� ���������� �����
	sRand();
	//���������� ������ � ������� ���������� �� ���������� �������
	for (int i = 0; i < n; i++)
	{
		m[i] = LineRand();
		tree.Add(1, m[i]);
		tree1.Add(1, m[i]);
	}
	//����� ������� ������ �� �����
	cout << "=== RAND BST ===" << endl;
	cout << "items count:" << tree.CheckSize() << endl;
	cout << "=== RAND AVL ===" << endl;
	cout << "items count:" << tree1.CheckSize() << endl;
	//��������� ��������� ����������� �������, �������� � ������
	double I = 0;
	double D = 0;
	double S = 0;
	double I1 = 0;
	double D1 = 0;
	double S1 = 0;
	//��������� ������ ��������, 10% - ������� ��������
	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0)		//10% ��������
		{
			tree.Delete(LineRand());
			D += tree.CountNodes();
			tree.Add(1, m[rand() % n]);
			I += tree.CountNodes();
			try {
				tree.GetLink(LineRand());
				S += tree.CountNodes();
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) { S += tree.CountNodes(); }
			tree1.Delete(LineRand());
			D1 += tree1.CountNodes();
			tree1.Add(1, m[rand() % n]);
			I1 += tree1.CountNodes();
			try {
				tree1.GetLink(LineRand());
				S1 += tree1.CountNodes();
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) { S1 += tree1.CountNodes(); }
		}
		else  //90% �������� ��������
		{
			int ind = rand() % n;
			tree.Delete(m[ind]);
			D += tree.CountNodes();
			INT_64 key = LineRand();
			tree.Add(1, key);
			I += tree.CountNodes();
			m[ind] = key;
			try {
				tree.GetLink(m[rand() % n]);
				S += tree.CountNodes();
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) { S += tree.CountNodes(); }
		
		 tree1.Delete(m[ind]);
		 D1 += tree1.CountNodes();
		 INT_64 key1 = LineRand();
		 tree1.Add(1, key1);
		 I1 += tree1.CountNodes();
		 m[ind] = key1;
		 try {
			tree1.GetLink(m[rand() % n]);
			S1 += tree1.CountNodes();
		 }
		 //��������� ���������� ��� ������ �������� ������
		  catch (overflow_error& err) { S1 += tree1.CountNodes(); }
		}
	cout << "=== RAND BST AFTER ===" << endl;
	cout << "items count:" << tree.CheckSize() << endl;
	//������������� ������ ����������� �������� BST
	cout << "1.39*log2(n)=" << 1.39 * (log((double)n) / log(2.0)) << endl;
	//����������������� ������ ����������� �������
	cout << "Count insert: " << I / (n / 2) << endl;
	//����������������� ������ ����������� ��������
	cout << "Count delete: " << D / (n / 2) << endl;
	//����������������� ������ ����������� ������
	cout << "Count search: " << S / (n / 2) << endl<<endl;

	cout << "=== RAND AVL AFTER ===" << endl;
	cout << "items count:" << tree1.CheckSize() << endl;
	//������������� ������ ����������� �������� BST
	cout << "log2(n) + 0.25 =" << (log((double)n) / log(2.0)) + 0.25 << endl;
	//����������������� ������ ����������� �������
	cout << "Count insert: " << I1 / (n / 2) << endl;
	//����������������� ������ ����������� ��������
	cout << "Count delete: " << D1 / (n / 2) << endl;
	//����������������� ������ ����������� ������
	cout << "Count search: " << S1 / (n / 2) << endl<<endl;
	//������������ ������ ������� m[]
	delete[] m;
}

void test_ord(int n){
	//�������� ������ ��� 64 � ��������� ������ ���� INT_64
	Tree< INT_64, int > tree;
	AVL_Tree< INT_64, int > tree1;
	//������ ��� ������, ������� ������������ � ������ 
	INT_64* m = new INT_64[n];

	//���������� ������ � ������� ���������� � ������������� ������� //������� �� ��������� [0, 10000, 20000, ... ,10000*n]
	for (int i = 0; i < n; i++) {
		m[i] = i * 10000;
		tree.Add(1, m[i]);
		tree1.Add(1, m[i]);
	}
	//����� ������� ������ �� �����
	cout << "=== ORD BST ===" << endl;
	cout << "items count:" << tree.CheckSize() << endl;
	cout << "=== ORD AVL ===" << endl;
	cout << "items count:" << tree1.CheckSize() << endl;
	//��������� ��������� ����������� �������, �������� � ������
	double I = 0;
	double D = 0;
	double S = 0;
	double I1 = 0;
	double D1 = 0;
	double S1 = 0;
	//��������� ������� ���������� ����� 
	sRand();
	//��������� ������ ��������, 10% - ������� ��������
	for (int i = 0; i < n / 2; i++)
	{
		if (i % 10 == 0)		//10% ��������
		{
			int k = LineRand() % (10000 * n);
			k = k + !(k % 2);	//��������� �������� ����
			tree.Delete(k);
			D += tree.CountNodes();
			tree.Add(1, m[rand() % n]);
			I += tree.CountNodes();
			k = LineRand() % (10000 * n);
			k = k + !(k % 2);	// ��������� �������� ����
			try {
				tree.GetLink(k);
				S += tree.CountNodes();
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) { S += tree.CountNodes(); }
			int k1 = LineRand() % (10000 * n);
			k1 = k1 + !(k1 % 2);	//��������� �������� ����
			tree1.Delete(k1);
			D1 += tree1.CountNodes();
			tree1.Add(1, m[rand() % n]);
			I1 += tree1.CountNodes();
			k1 = LineRand() % (10000 * n);
			k1 = k1 + !(k1 % 2);	// ��������� �������� ����
			try {
				tree1.GetLink(k1);
				S1 += tree1.CountNodes();
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) {
				S1 += tree1.CountNodes();
			}
		}
		else  //90% �������� ��������
		{
			int ind = rand() % n;
			tree.Delete(m[ind]);
			D += tree.CountNodes();
			int k = LineRand() % (10000 * n);
			k = k + k % 2;		// ��������� ������ ����
			tree.Add(1, k);
			I += tree.CountNodes();;
			m[ind] = k;
			try {
				tree.GetLink(m[rand() % n]);
				S += tree.CountNodes();
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) { S += tree.CountNodes(); }
			int ind1 = rand() % n;
			tree1.Delete(m[ind1]);
			D1 += tree1.CountNodes();;
			int k1 = LineRand() % (10000 * n);
			k1 = k1 + k1 % 2;		// ��������� ������ ����
			tree1.Add(1, k1);
			I1 += tree1.CountNodes();;
			m[ind1] = k1;
			try {
				tree1.GetLink(m[rand() % n]);
				S1 += tree1.CountNodes();;
			}
			//��������� ���������� ��� ������ �������� ������
			catch (overflow_error& err) { S1 += tree1.CountNodes(); }
		}
	}

	//����� �����������:
	// ����� ������� ������ ����� �����
	cout << "=== RAND BST AFTER ===" << endl;
	cout << "items count:" << tree.CheckSize() << endl;
	//������������� ������ ����������� �������� BST
	cout << "n/2 =" << n / 2 << endl;
	//����������������� ������ ����������� �������
	cout << "Count insert: " << I / (n / 2) << endl;
	//����������������� ������ ����������� ��������
	cout << "Count delete: " << D / (n / 2) << endl;
	//����������������� ������ ����������� ������
	cout << "Count search: " << S / (n / 2) << endl<<endl<<endl;
	cout << "=== RAND AVL AFTER ===" << endl;
	// ����� ������� ������ ����� �����
	cout << "items count:" << tree1.CheckSize() << endl;
	//������������� ������ ����������� �������� BST
	cout << "log2(n) + 0.25 =" << (log((double)n) / log(2.0)) + 0.25 << endl;
	//����������������� ������ ����������� �������
	cout << "Count insert: " << I1 / (n / 2) << endl;
	//����������������� ������ ����������� ��������
	cout << "Count delete: " << D1 / (n / 2) << endl;
	//����������������� ������ ����������� ������
	cout << "Count search: " << S1 / (n / 2) << endl;
	//������������ ������ ������� m[]
	delete[] m;
}	//����� �����



