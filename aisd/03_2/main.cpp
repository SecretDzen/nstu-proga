#include <iostream>
#include <vector>
#include "avl_tree.hpp"
#include "test_tree.hpp"
using namespace std;

void func_iter(Tree<int, int>* tree) {
	int first, second;
	Tree<int, int>::Iterator i(tree);
	Tree<int, int>::reverse_Iterator i_2(tree);
	int exit = 1;
	while (exit != 0) {
		cout << "������� ��������� ����������:" << endl;
		cout << "������ ��������: ";
		try{
			cout << *i << endl;
		}
		catch (overflow_error& err) {
			cout << err.what() << endl;
		}
		cout << "�������� ��������: ";
		try
		{
			cout << *i_2 << endl << endl;
		}
		catch (overflow_error& err){
			cout << err.what() << endl;
		}
		cout << "�������:" << endl << endl;
		cout << "��� ������� ���������" << endl << endl;
		cout << "1 - ++" << endl;
		cout << "2 - --" << endl;
		cout << "3 - ��������� ������� �������" << endl;
		cout << "4 - �������� ������� �������" << endl;
		cout << "5 - ���������� � begin()" << endl;
		cout << "6 - ���������� � end()" << endl;
		cout << "7 - ��������� (iterator==begin())" << endl;
		cout << "8 - ��������� (iterator!=end())" << endl << endl;
		cout << "��� ��������� ���������" << endl << endl;
		cout << "9 - ++" << endl;
		cout << "10 - --" << endl;
		cout << "11 - ��������� ������� �������" << endl;
		cout << "12 - �������� ������� �������" << endl;
		cout << "13 - ���������� � rbegin()" << endl;
		cout << "14 - ���������� � rend()" << endl;
		cout << "15 - ��������� (reverse_iterator==begin())" << endl;
		cout << "16 - ��������� (reverse_iterator!=end())" << endl;
		cout << "_______" << endl;
		cout << "0 - �����" << endl;
		cout << "_______" << endl;
		cout << "�����: ";
		cin >> first;
		switch (first) {
		case 0:
			exit = 0;
			break;
		case 1:
			try
			{
				++i;
				cout << "�������� ������ �������" << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 2:
			try
			{
				--i;
				cout << "�������� ������ �������" << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 3:
			try
			{
				cout << "������ �������� � ���������: " << *i << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 4:
			cout << "�� ��� ��������: ";
			cin >> first;
			try
			{
				*i = first;
				cout << "�������� ������ �������" << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 5:
			i = tree->Begin();
			break;
		case 6:
			i = tree->End();
			break;
		case 7:
			cout << (i == tree->Begin()) << endl;
			break;
		case 8:
			cout << (i != tree->End()) << endl;
			break;
		case 9:
			try
			{
				++i_2;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 10:
			try
			{
				--i_2;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 11:
			try
			{
				cout << "������ �������� � ���������: " << *i_2 << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 12:
			cout << "�� ��� ��������: ";
			cin >> first;
			try
			{
				*i_2 = first;
				cout << "�������� ������ �������" << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 13:
			i_2 = tree->R_Begin();
			break;
		case 14:
			i_2 = tree->R_End();
			break;
		case 15:
			cout << (i_2 == tree->R_Begin()) << endl;
			break;
		case 16:
			cout << (i_2 != tree->R_End()) << endl;
			break;
		default:
			break;
		}
	}
	cin.get();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	AVL_Tree<int, int> tree;
	vector <int> l;
	int first, second;
	int exit = 1;
	while (exit != 0) {
		cout << "������� ��������� ������:" << endl;
		tree.Print();
		cout << "����:" << endl;
		cout << "��� ������ �� ���� ������� 0 " << endl;
		cout << "1 - ������ ������ ������" << endl;
		cout << "2 - ��������� ������ �� �������" << endl;
		cout << "3 - ������� ������ �� �����" << endl;
		cout << "4 - ������ ���� �������������� ��������� ������� ���������" << endl;
		cout << "5 - ��������� ������ �� �����" << endl;
		cout << "6 - �������� ������ �� �����" << endl;
		cout << "7 - �������� ����� �������" << endl;
		cout << "8 - ������� �������" << endl;
		cout << "9 -  ������� ������" << endl;
		cout << "10 - ������������ ������ ������ " << endl;
		cout << "11 - ������ � �����������" << endl;
		cout << "12 - �������� �����" << endl;
		cout << "________________________" << endl;
		cout << "�����: ";
		cin >> first;
		switch (first) {
		case 0:
			exit = 0;
			break;
		case 1:
			cout << "������ ������: " << tree.CheckSize() << endl;
			break;
		case 2:
				if ( tree.CheckEmpty() == 1)
					cout << "������ ������" << endl;
				else cout << "������ �� ������" << endl;
			break;
		case 3:
			tree.Print();
			break;
		case 4:
			cout << "����� �������������� ���������: " << tree.CountNodes() << endl;
			break;
		case 5:
			cout << "������� ����: ";
			cin >> first;
			try
			{
				cout << "���������� ������ ����: " << tree.GetLink(first) << endl;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 6:
			cout << "������� ����: ";
			cin >> first;
			cout << "������� ������: ";
			cin >> second;
			try
			{
				tree.GetLink(first) = second;
			}
			catch (overflow_error& err) {
				cout << err.what() << endl;
			}
			break;
		case 7:
			cout << "������� ����: ";
			cin >> first;
			cout << "������� ������: ";
			cin >> second;
			if (tree.Add(second, first)) cout << "������� ��������!" << endl;
			else cout << "������� �� �������� (���  ���� � ������)!" << endl;
			break;
		case 8:
			cout << "������� ����: ";
			cin >> first;
			if (tree.Delete(first)) cout << "���� �����!" << endl;
			else cout << "���� �� �����!" << endl;
			break;
		case 9:
			tree.DeleteTree();
			break;
		case 10:
			l = tree.getKeys();
			if (l.size() == 0) cout << "������ ������"<<endl;
			else {
				for (int i = 0; i < tree.CheckSize(); i++)
					cout << l[i] << endl;
				cout << endl;
			}
			break;
		case 11:
			func_iter(&tree);
			break;
		case 12:
			int par;
			cout << "������� ��������- " << endl;
			cin >> par;
			cout << "Test_rand: " << endl;
			test_rand(par);
			cout << endl;
			cout << "Test_ord: " << endl;
			test_ord(par);
			cout << "---------------------------" << endl;
			cout << "---------------------------" << endl;
			cout << "---------------------------" << endl;
			break;
		default:
			break;
		}
		cout << endl;
	}
	cin.get();
}
