#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <exception>
#include <algorithm>
#pragma warning(disable: 4996)

class Node {
public:
	Node::Node() { //konstruktor podstawowy ustawia wszystkie wartości na NULL;
		array[0] = NULL;
		key = NULL;
		right = NULL;
		left = NULL;
	};
	~Node() { ; };
	void DSW(int x);
	void rotate_right(Node *grandfather, Node *parent, Node *child);
	void rotate_left(Node* grandfather, Node* parent, Node* child);
	long findHeight(Node *aNode)
	{
		if (aNode == 0)
			return -1;

		long lefth = findHeight(aNode->left);
		long righth = findHeight(aNode->right);
		
		if (lefth > righth)
			return lefth + 1;
		else
			return righth + 1;
	}
	bool insertToNode(long int key);
	void insertToNodeN(long int x);
	void remove(long int key);
	void PreOrder(Node *a);
	void InOrder(Node *a);
	void PostOrder(Node *a);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	void search(long int key);
	void destroyTree(Node* a);
	Node *successor();
	Node *predecessor();
private:
	long int key;
	Node *left, *right;
	char array[256];
	Node *&minimal(Node *p);
	Node *maximal(Node *p);
};

Node *Root = new Node;

unsigned long int _holdrand;
unsigned long int generateNumber(long int n) {
	return (_holdrand = (_holdrand * 214013L + 2531011L) >> 32) % n;
};
void Node::DSW(int x)
{

#pragma region Faza I DSW
	Node *grandfather = NULL;
	Node *tmp = Root;
	while (tmp != NULL)
	{
		if ((tmp->left)!= NULL)//UWAGA: zmiana „root’a” obsłużona w rotacji !
		{
			Node *tmp2 = tmp->left;
			rotate_right(grandfather, tmp, tmp->left);
			tmp = tmp2;
		}
		else
		{
			grandfather = tmp;
			tmp = tmp->right;
		}
	}// Złożoność I fazy algorytmu DSW O(N)

#pragma endregion 
	Node *tmp4 = Root;
	long imt=0;
	while (tmp4->right != NULL)
	{
		tmp4 = tmp4->right;
		imt++;
	}


	std::cout << "Faza I zakonczona\n";
	
#pragma region Faza II DSW
	//Perfect tree FAZA II
	grandfather = NULL; 
	tmp = Root;
	long m = 1;
	while (m <= x) m = 2 * m + 1;
	m = m / 2;
	for (int i = 0; i < (x - m); i++)
	{
		Node *tmp2 = tmp->right;
		if (tmp2 != NULL)
		{
			rotate_left(grandfather, tmp, tmp->right);
			grandfather = tmp2;
			tmp = tmp2->right;
		}
	}
	while (m>1)
	{
		m = m / 2; 
		grandfather = NULL; 
		tmp = Root;
		for (long i = 0; i < m; i++)
		{
			Node *tmp2 = tmp->right;
			rotate_left(grandfather, tmp, tmp->right);
			grandfather = tmp2;
			tmp = tmp2->right;//right
		}
	}
#pragma endregion 
	std::cout << "Wysokosc drzewa po :" << Root->findHeight(Root) +1 << "\n";  // <==== dobrze
	std::cout << "Faza II zakonczona\n";									// <===== po wyjściu jest 0
}
void Node::rotate_right(Node *grandfather, Node *parent, Node *child)
{
	if (grandfather != NULL)
	{
		if (grandfather->right == parent)
			grandfather->right = child;
		else grandfather->left = child;
	}
	else
		Root = child;//zmiana korzenia drzewa

	Node *tmp = child->right;
	child->right = parent;
	parent->left = tmp;
}
void Node::rotate_left(Node* grandfather, Node* parent, Node* child)
{
	if (grandfather != NULL)
	{
		if (grandfather->right == parent)
			grandfather->right = child;
		else grandfather->left = child;
	}
	else
		Root = child;//zmiana korzenia drzewa

	Node *tmp = child->left;
	child->left = parent;
	parent->right = tmp;
}
bool Node::insertToNode(long int key) {
	/*	? wstawienie do drzewa nowego elementu(wraz z obsługą przypadku, w którym węzeł o zadanej wartości składowej kluczowej już znajduje się w drzewie),
	//		funkcja tablicy znaków przypisuje losowe wartości(losowe znaki);
	*/
	try {
		Node *p = this;
		Node *parent = this;
		while (p != NULL) {
			if (p->key == key) {
				//mozliwa podmiana breloka
				return 0;
			}
			parent = p;
			if (p->key > key) p = p->left;
			else p = p->right;
		}
		if (this->key == NULL) {
			this->key = key;
		/*	for (int i = 0; i < 255; i++)
				this->array[i] = rand() % 255;*/
		}
		else
			if (parent->key > key) { // nie ma sensu deklarowanie wartości tmp jeżeli możliwa będzie deklaracja w Root
				Node *tmp = new Node;
				tmp->key = key;
				parent->left = tmp;
			}
			else {
				Node *tmp = new Node;
				tmp->key = key;
				parent->right = tmp;
			}
			//std::cout << "Wstawilem element\n" << key << std::endl;
			return 1;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		throw std::exception(ex);
	}
};
void Node::insertToNodeN(long int x) {
	//? wstawienie do drzewa X nowych węzłów o wygenerowanych losowo i różnych wartościach składowych kluczowych z zakresu 10 do 1 000 012 (wartość X podana jako argument funkcji);
	long int key;
	//int tab[] = {4,6,2,1,3,5,7,8,12,10,14,9,11,13,15};
	//this->insertToNode(tab[7]);
	long int i;
	for (i = 0; i < x; i++) {

			srand(time(NULL));
				//key = tab[i];
			key = generateNumber(1000002) + 10;
			auto a = this->insertToNode(key);
			if (!a) {
				i--;
				//std::cout << "miss\n";
			}

	}
};
void Node::remove(long int key) { 
	try {
		Node *parent = NULL;
		Node *p = this;

		while (p != NULL && key != p->key)
		{
			parent = p;
			if (p->key < key) p = p->right;
			else p = p->left;
		}
		if (p == NULL) throw std::exception("Nie mozna usunac podanego klucza, poniewaz go nie ma w drzewie.");

		if (p->right == NULL && p->left == NULL)
		{
			if (p == this)
			{
				Node *tmp;
				tmp = this;
				delete tmp;
				return;
			}
			if (parent->right == p)
			{
				parent->right = NULL;
				delete p;
				return;
			}
			else
			{
				parent->left = NULL;
				delete p;
				return;
			}
		}
		if (p->right == NULL) // usuwamy wezel p ma tylko lewe poddrzewo
		{
			if (parent->right == p)
			{
				parent->right = p->left;
				delete p;
			}
			else
			{
				parent->left = p->left;
				delete p;
			}
			return;
		}
		if (p->left == NULL)
		{
			if (parent == NULL)
			{
				p = p->right;
				return;
			}
			if (parent->right == p)
			{
				parent->right = p->right;
				delete p;
				return;
			}
			else
			{
				parent->left = p->right;
				delete p;
				return;
			}
		}
		// ma oba poddrzewa
		Node *poprzednik = p->predecessor();

		if (key == this->key) // root
		{
			poprzednik->right = this->right;
			this->key = this->left->key;
			return;
		}
		if (key >= p->key)// prawe poddrzewo
		{
			if (p->right == poprzednik)
			{
				parent->right = p->left;
				poprzednik->right = p->right;
				delete p;
				return;
			}
			else
			{
				parent->left = p->left;
				poprzednik->right = p->right;
				delete p;
				parent->right = NULL;
				return;
			}
		}
		else // lewe poddrzewo
		{
			parent->left = p->left;
			poprzednik->right = p->right;
			delete p;
			return;
		}
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
};
void Node::printPreOrder() {
	PreOrder(this);
	std::cout << std::endl;
};
void Node::printInOrder() {
	InOrder(this);
	std::cout << std::endl;
}
void Node::printPostOrder() {
	PostOrder(this);
	std::cout << std::endl;
}
void Node::PreOrder(Node *a) {
	if (a != NULL)
	{
		std::cout << a->key << " ";
		PreOrder(a->left);
		PreOrder(a->right);
	}
};
void Node::InOrder(Node *a) {
	if (a != NULL)
	{
		InOrder(a->left);
		std::cout << a->key << " ";
		InOrder(a->right);
	}
};
void Node::PostOrder(Node *a) {
	if (a != NULL)
	{
		PostOrder(a->left);
		PostOrder(a->right);
		std::cout << a->key << " ";
	}
};
void Node::destroyTree(Node *a) {
	if (a != NULL)
	{
		destroyTree(a->left);
		destroyTree(a->right);
		delete a;
	}
};
void Node::search(long int key)
{
	// ? wyszukanie w drzewie elementu o podanej jako argument wartości składowej kluczowej (wraz z obsługą przypadku, w którym element nie istnieje);
	try {
		Node *p = this;

		while (p != NULL && key != p->key)
		{
			if (p->key < key) p = p->right;
			else p = p->left;
		}

		if (p == NULL) {
			throw std::exception("Nie znaleziono poszukiwanego klucza.");
		}

			std::cout << "Znaleziono poszukiwany klucz." << std::endl;

	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
};
Node* Node::successor() {//Następnik

	Node *p = this;
	if (this->right != NULL)
		return(minimal(p->right));

	throw std::exception("Wezel nie posiada nastepnika.");

};
Node* Node::predecessor() {//Poprzednik
	Node *p = this;
	if (this->left != NULL)
		return(maximal(p->left));

		throw std::exception("Wezel nie posiada poprzednika.");

};
Node*& Node::minimal(Node *p) {
	while (p->left != NULL)
		p = p->left;
	return p;
};
Node* Node::maximal(Node *p) {
	while (p->right != NULL)
		p = p->right;
	return p;
};

int main()
{
	clock_t begin, end;
	double time_spent;
	_holdrand = time(NULL);
	srand(time(NULL));
	long int x1, x2;

	FILE* fp = fopen("inlab04.txt", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %d", &x1, &x2);
	fclose(fp);


	//? czas start;
	begin = clock();


	//? wstaw X1 elementów do drzewa;
	Root->insertToNodeN(x1);
	//? oblicz i wypisz wysokość drzewa;
	std::cout <<"Wysokosc drzewa przed :"<< Root->findHeight(Root) << "\n";
	//? wykonaj algorytm DSW;
	Root->DSW(x1);
	//? usuń wszystkie elementy z drzewa;
	Root->destroyTree(Root);


	Node *Root= new Node;
	std::cout << "Drzewo Nr2. \n";
	//? wstaw X2 elementów do drzewa;
	Root->insertToNodeN(x2);
	//? oblicz i wypisz wysokość drzewa;
	std::cout << "Wysokosc drzewa przed :" << Root->findHeight(Root) << "\n";
	//? wykonaj algorytm DSW;
	Root->DSW(x2);
	//? usunięcie drzewa

	Root->destroyTree(Root);
	//? czas stop;
	end = clock();
	//? wypisz czas wykonania.
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time_spent << std::endl;

	system("PAUSE");
	return 0;
}

