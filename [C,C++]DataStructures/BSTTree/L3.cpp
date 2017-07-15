#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <exception>

#pragma warning(disable: 4996)

class Node{
public:
	Node();
	~Node() { ; };
	void insertToNode(long int key);
	void insertToNodeN(long int x);
	void remove(long int key);
	void PreOrder(Node *a);
	void InOrder(Node *a);
	void PostOrder(Node *a);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	void search(long int key);
	Node *successor();
	Node *predecessor();
private:
	long int key;
	Node *left, *right;
	char array[256];
	Node *&minimal(Node *p);// private
	Node *maximal(Node *p);// private
};

unsigned long int _holdrand;
long int generateNumber(long int n) {
	return (_holdrand = (_holdrand * 214013L + 2531011L) >> 32) % n;
};

Node::Node() { //konstruktor podstawowy ustawia wszystkie warto�ci na NULL;
	this->array[0] = NULL;
	this->key = NULL;
	this->right = NULL;
	this->left = NULL;
};
void Node::insertToNode(long int key) {
/*	? wstawienie do drzewa nowego elementu(wraz z obs�ug� przypadku, w kt�rym w�ze� o zadanej warto�ci sk�adowej kluczowej ju� znajduje si� w drzewie),
//		funkcja tablicy znak�w przypisuje losowe warto�ci(losowe znaki);
*/
	try {
		Node *p = this;
		Node *parent= this;
		while (p != NULL) {
			if (p->key == key) {
				//mozliwa podmiana breloka
				throw -1;
			}
			parent = p;
			if (p->key > key) p = p->left;
			else p = p->right;
		}
		if (this->key == NULL) {
			this->key = key;
			for (int i = 0; i < 255; i++)
				this->array[i] = rand() % 255;
		}
		else 
			if (parent->key > key) { // nie ma sensu deklarowanie warto�ci tmp je�eli mo�liwa b�dzie deklaracja w Root
				Node *tmp = new Node;
				tmp->key = key;
				for (int i = 0; i < 255; i++)
					tmp->array[i] = rand() % 255;
				parent->left = tmp;
			}
			else {
				Node *tmp = new Node;
				tmp->key = key;
				for (int i = 0; i < 255; i++)
					tmp->array[i] = rand() % 255;
				parent->right = tmp;
			}
			std::cout << "Wstawilem element\n" << key << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		throw std::exception(ex);
	}
	catch (int a)
	{
		;
	}
};
void Node::insertToNodeN(long int x) {
//? wstawienie do drzewa X nowych w�z��w o wygenerowanych losowo i r�nych warto�ciach sk�adowych kluczowych z zakresu 10 do 1 000 012 (warto�� X podana jako argument funkcji);
		long int key;
		//int tab[] = {4,6,2,1,3,5,7,8,12,10,14,9,11,13,15};
		//this->insertToNode(tab[7]);
		for (long int i = 0; i < x; i++) {
			try {
				srand(time(NULL));
			//	key = tab[i];
				key = generateNumber(1000002)+10;
				this->insertToNode(key);
			}
			catch (std::exception &ex) {
				i--;
			}
		}

};
void Node::remove(long int key) { // TODO Usuwanie !!!!
	// ? usuni�cie z drzewa elementu o podanej jako argument warto�ci sk�adowej kluczowej (wraz z obs�ug� przypadku, w kt�rym brak w drzewie w�z�a o zadanej warto�ci sk�adowej kluczowej;
	// w przypadku usuwania w�z�a stopnia 2 - go nale�y zaimplementowa� wybran� wersje post�powania, odwo�uj�ce si� do poprzednika lub nast�pnika usuwanego w�z�a);
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
				if(parent->right == p)
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
				}else
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
				this->right = this->left->right;
				this->left = this->left->left;
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
				}else
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
void Node::search(long int key)
{
	// ? wyszukanie w drzewie elementu o podanej jako argument warto�ci sk�adowej kluczowej (wraz z obs�ug� przypadku, w kt�rym element nie istnieje);
	try {
		Node *p = this;
		Node *parent = NULL;
		while (p != NULL && key != p->key)
		{
			parent = p;
			if (p->key < key) p = p->right;
			else p = p->left;
		}

		if (p == NULL) {
			throw std::exception("Nie znaleziono poszukiwanego klucza.");
		}
		else {
			std::cout << "Znaleziono poszukiwany klucz." << std::endl;
			return;
		}
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
};
Node* Node::successor() {//Nast�pnik
	bool found = false;
	Node *p = this;
	if (this->right != NULL)
		return(minimal(p->right));
	else {
		throw std::exception("Wezel nie posiada nastepnika.");
	}
};
Node* Node::predecessor() {//Poprzednik
	bool found = false;
	Node *p = this;
	if (this->left != NULL)
		return(maximal(p->left));
	else {
		throw std::exception("Wezel nie posiada poprzednika.");
	}
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

	long int x, k1, k2, k3, k4;
	FILE* fp = fopen("inlab03.txt", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %d %d %d %d", &x, &k1, &k2, &k3, &k4);
	fclose(fp);

/*
		try {
			Node Root;

			Root.insertToNodeN(15);

			Root.search(51);

			Root.search(3);

			Root.remove(8);
			Root.remove(6);
			Root.remove(50);

			Root.printPreOrder();

			Root.printInOrder();

			Root.printPostOrder();


		}
		catch (std::exception &ex) {
			std::cout << ex.what() << std::endl;
		}
*/

	try {
		/////////////////////////////////////////////////////////////////////////////////////////////
		//	? czas start; 
		begin = clock();
		//	? zainicjuj drzewo;
		Node Root;
		//	? usu� element o warto�ci klucza k1; //powinno zwr�ci� b��d, bo drzewo jest puste;
		Root.remove(k1);
		//	? wstawienie X element�w do drzewa;
		Root.insertToNodeN(x);
		//	? wstaw element o warto�ci klucza k1;
		Root.insertToNode(k1);
		//	? wstaw element o warto�ci klucza k2;
		Root.insertToNode(k2);
		//	? wstaw element o warto�ci klucza k3;
		Root.insertToNode(k3);
		//	? wstaw element o warto�ci klucza k4;
		Root.insertToNode(k4);
		//	? usu� element o warto�ci klucza k1;
		Root.remove(k1);
		//	? wyszukaj element o warto�ci k1; //powinno zwr�ci� b��d, bo element zosta� usuni�ty;
		Root.search(k1);
		//	? usu� element o warto�ci klucza k2;
		Root.remove(k2);
		//	? usu� element o warto�ci klucza k3;
		Root.remove(k3);
		//	? usu� element o warto�ci klucza k4;
		Root.remove(k4);
		//	? czas stop;
		end = clock();

		//	? wypisz czas wykonania;
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << time_spent << std::endl;
		/////////////////////////////////////////////////////////////////////////////////////////////
		std::cout << "--------------------------------------------------\n";
		Root.printPreOrder();
		Root.printInOrder();
		Root.printPostOrder();
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	system("PAUSE");
    return 0;
}