#include <iostream>
#include <fstream>
//#include "stdafx.h"

struct Tree
{
	int data;
	Tree* left;
	Tree* right;
	Tree* parent;
};

//????????
Tree* Make(int data, Tree* p)
{
	Tree* q = new Tree;
	q->data = data;
	q->left = nullptr;
	q->right = nullptr;
	q->parent = p;
	return q;
}

//??????????
void Add(int data, Tree*& root)
{
	if (root == nullptr)
	{
		root = Make(data, nullptr);
		return;
	}
	Tree* v = root;
	while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
		if (data < v->data)
			v = v->left;
		else
			v = v->right;
	if (data == v->data)
		return;
	Tree* u = Make(data, v);
	if (data < v->data)
		v->left = u;
	else
		v->right = u;
}

//?????
void Output(Tree* v)
{
	if (v == nullptr)
		return;
	Output(v->left);
	std::cout << v->data << std::endl;
	Output(v->right);
}

//?????
Tree* Search(int data, Tree* v)
{
	if (v == nullptr)
		return v;
	if (v->data == data)
		return v;
	if (data < v->data)
		return  Search(data, v->left);
	else
		return Search(data, v->right);
}

//????????
void Delete(int data, Tree*& root)
{
	Tree* u = Search(data, root);
	if (u == nullptr)
		return;
	if (u->left == nullptr && u->right == nullptr && u == root)
	{
		delete root;
		root = nullptr;
		return;
	}
	if (u->left == nullptr && u->right != nullptr && u == root)
	{
		Tree* t = u->right;
		while (t->left != nullptr)
			t = t->left;
		u->data = t->data;
		u = t;
	}
	if (u->left != nullptr && u->right == nullptr && u == root)
	{
		Tree* t = u->left;
		while (t->right != nullptr)
			t = t->right;
		u->data = t->data;
		u = t;
	}
	if (u->left != nullptr && u->right != nullptr)
	{
		Tree* t = u->right;
		while (t->left != nullptr)
			t = t->left;
		u->data = t->data;
		u = t;
	}
	Tree* t;
	if (u->left == nullptr)
		t = u->right;
	else
		t = u->left;
	if (u->parent->left == u)
		u->parent->left = t;
	else
		u->parent->right = t;
	if (t != nullptr)
		t->parent = u->parent;
	delete u;
}

void Search(int data, Tree* v, int number)
{
	std::ofstream out("output.txt");
	if (v == nullptr)
	{
		std::cout << data << " - n";
		out << data << " - n";
		return;
	}
	else if (v->data == data)
	{
		std::cout << data << " - " << number;
		out << data << " - " << number;
		return;
	}
	else if (data < v->data)
		Search(data, v->left, number + 1);
	else
		Search(data, v->right, number + 1);

}

int main()
{
	Tree* root = nullptr;
	std::ifstream file;
	file.open("input.txt");
	if (!file.is_open())
		std::cout << "ERROR" << std::endl;
	else
	{
		std::cout << "File is open" << std::endl;
		char a;
		int b;
		while (!file.eof())
		{
			file >> a;
			file >> b;
			if (a == '+')
			{
				Add(b, root);
			}
			else if (a == '-')
			{
				Delete(b, root);
			}
			else if (a == '?')
			{
				Search(b, root, 1);
				std::cout << '\n';
			}
			else if (a == 'E')
				break;
		}
	}

	file.close();
	return 0;
}