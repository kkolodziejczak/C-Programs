#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <exception>

#define DEBUG 0

#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif

unsigned int _holdrand;

struct Element {
	long int key;
	double n1, n2, n3;
};
struct Node {
	Element dane;
	Node* next;
	Node* prev;
};

long int generateNumber(long int n) {
	return (_holdrand = (_holdrand * 214013L + 2531011L) >> 32) % n;
};

Node *add(Node*  &Head, Element dane) {
	/*TODO: inicjalizacja pustej listy
	wstawienie do listy nowego elementu(uwzgl�dni� przypadek, w kt�rym w�ze� o zadanej warto�ci sk�adowej kluczowej ju� znajduje si� w li�cie);
	funkcja ustawia pola typu double na losowe warto�ci;*/
	Node *tmp;
	Node *Przetrzymanie = Head;
	Node *Test = Head;

	tmp = (Node*)malloc(sizeof(Node));
	tmp->dane = dane;
	tmp->next = NULL;
	tmp->prev = Head;

	if (Head == NULL) { // pierwszy element listy
		tmp->prev = NULL;
		Head = tmp;
		return Head;
	}
	while (Test != NULL) { // znalezienie klucza kt�ry si� powtarza.
		if (Test->dane.key == dane.key) {
			LOG("wykryto klucz podmieniono dane pod danym kluczem.");
			Test->dane = tmp->dane;
			return Przetrzymanie;
		}
		else {
			Test = Test->next;
		}
	}


	if (Head->dane.key > dane.key) {//  poczatek
		tmp->dane = dane;
		tmp->next = Head;
		tmp->prev = NULL;
		Head->prev = tmp;
		Head = tmp;
		return tmp;
	}
	else {// element trzeba doda� w �rodku/na ko�cu.
		do { // p�tla znajduj�ca miejsce dla elementu. 
			if (Head->next == NULL) { break; }
			if (Head->dane.key < dane.key && Head->next->dane.key > dane.key) {
				break;
			}
			else {
				Head = Head->next;
			}
		} while (Head != NULL);

		if (Head->next == NULL) { // Sprawdzenie ostatniego elementu dodanie na ko�cu.
			Head->next = tmp;
			tmp->prev = Head;
			return Przetrzymanie;
		}

		if (Head->next->dane.key > dane.key && Head->dane.key < dane.key) // dodanie w �rodku.
		{
			tmp->prev = Head;
			tmp->next = Head->next;
			Head->next->prev = tmp;
			Head->next = tmp;

			return Przetrzymanie;
		}
	}
}
Node *add(Node*  &Head, long int dane) {
	Node *tmp;
	Node *Przetrzymanie = Head;
	Node *Test = Head;

	tmp = (Node*)malloc(sizeof(Node));
	tmp->dane.key = dane;
	tmp->dane.n1 = rand();
	tmp->dane.n2 = rand();
	tmp->dane.n3 = rand();
	tmp->next = NULL;
	tmp->prev = Head;

	if (Head == NULL) { // pierwszy element listy
		tmp->prev = NULL;
		Head = tmp;
		return Head;
	}
	do { // znalezienie klucza kt�ry si� powtarza.
		if (Test->dane.key == dane) {
			LOG("wykryto klucz, podmieniono dan� pod danym kluczem.");
			Test->dane = tmp->dane;
		}
		else {
			Test = Test->next;
		}
	} while (Test->next != NULL);

	if (Head->dane.key > dane) {//  poczatek
		tmp->next = Head;
		tmp->prev = NULL;
		Head->prev = tmp;
		Head = tmp;
		return tmp;
	}
	else {// element trzeba doda� w �rodku/na ko�cu.
		do { // p�tla znajduj�ca miejsce dla elementu. 
			if (Head->next == NULL) { break; }
			if (Head->dane.key < dane && Head->next->dane.key > dane) {
				break;
			}
			else {
				Head = Head->next;
			}
		} while (Head != NULL);

		if (Head->next == NULL) { // Sprawdzenie ostatniego elementu dodanie na ko�cu.
			Head->next = tmp;
			tmp->prev = Head;
			return Przetrzymanie;
		}

		if (Head->next->dane.key > dane && Head->dane.key < dane) // dodanie w �rodku.
		{
			tmp->prev = Head;
			tmp->next = Head->next;
			Head->next->prev = tmp;
			Head->next = tmp;

			return Przetrzymanie;
		}
	}
}
Node *generate(Node *Head, long int x) {
	//TODO: generate x ammount of record
	for (long int i = 0; i < x; i++) {
		Element dane;
		dane.key = generateNumber(99990) + 10;
		dane.n1 = rand();
		dane.n2 = rand();
		dane.n3 = rand();
		LOG(dane.key);
		Head = add(Head, dane);
	}
	return Head;
}
Node *Usun(Node *Head, long int szukana) {
	if (Head == NULL) {
		printf("Lista jest Pusta");
		return Head;
	}
	Node *biezacy;
	Node *poprzednik;
	poprzednik = NULL;
	biezacy = Head;
	while (biezacy != NULL) {
		if (biezacy->dane.key == szukana) {
			if (poprzednik == NULL) { /// poprzednik == null -> pierwszy element listy
				Node *tmp;
				tmp = biezacy;
				Head = Head->next;
				Head->prev = NULL;
				free(tmp);
				biezacy = Head;
				return Head;

			}
			else {
				Node *tmp;
				tmp = biezacy;
				poprzednik->next = tmp->next;
				poprzednik->next->prev = tmp->prev;
				free(tmp);
				biezacy = poprzednik->next;
			}
		}
		if (biezacy->next == NULL && biezacy->dane.key != szukana)
		{
			printf("Nie ma elementu o podanej wartosci kluczowej.");
		}
		if (biezacy != NULL) {
			poprzednik = biezacy;
			biezacy = biezacy->next;
		}
	}
	return Head;
}
Node* UsunWszystkie(Node *poczatek) {
	Node *tmp;
	while (poczatek != NULL) {
		tmp = poczatek;
		poczatek = tmp->next;
		free(tmp);
	}
	return poczatek;
}
void Wyszukaj(Node *Head, long int szukana) {
	Node *biezacy;
	biezacy = Head;
	while (biezacy != NULL) {
		if (biezacy->dane.key == szukana) {
			printf("  Klucz: %d\n", biezacy->dane.key);
			printf("  Double 1: %d\n", biezacy->dane.n1);
			printf("  Double 2: %d\n", biezacy->dane.n2);
			printf("  Double 3: %d\n", biezacy->dane.n3);
			printf("--------------------------\n");
			break;
		}
		if (biezacy->next == NULL && biezacy->dane.key != szukana)
		{
			printf("Nie ma elementu o podanej wartosci kluczowej.");
			break;
		}
		biezacy = biezacy->next;
	}
}
void DrukujListe(Node *Head, char kierunek) {
	if (Head != NULL) {
		if (kierunek == 'F') { // normalnie do przodu.
			Node *biezacy;
			biezacy = Head;
			while (biezacy != NULL) {
				printf("  Klucz: %d\n", biezacy->dane.key);
				printf("  Double 1: %f\n", biezacy->dane.n1);
				printf("  Double 2: %f\n", biezacy->dane.n2);
				printf("  Double 3: %f\n", biezacy->dane.n3);
				printf("--------------------------\n");
				biezacy = biezacy->next;
			}
		}
		else { // wstecz Znak != F.
			Node *biezacy;
			biezacy = Head;
			while (biezacy != NULL)
			{
				if (biezacy->next == NULL) break;
				biezacy = biezacy->next;
			}
			while (biezacy != NULL) {
				printf("  Klucz: %d\n", biezacy->dane.key);
				printf("  Double 1: %f\n", biezacy->dane.n1);
				printf("  Double 2: %f\n", biezacy->dane.n2);
				printf("  Double 3: %f\n", biezacy->dane.n3);
				printf("--------------------------\n");
				biezacy = biezacy->prev;
			}

		}
	}
	else
	{
		printf("\nLista jest pusta.");
	}


}

int main()
{
	clock_t begin, end;
	double time_spent;
	_holdrand = time(NULL);
	srand(time(NULL));

	//////////////////////// Otwieranie pliku./////////////////////////////
	long int x, k1, k2, k3, k4;
	FILE* fp = fopen("inlab02.txt", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %d %d %d %d", &x, &k1, &k2, &k3, &k4);
	fclose(fp);

	/////////////////////////czas start////////////////////////////////////
	begin = clock();

	/////////////////////////Inicjalizacja listy///////////////////////////
	Node *Head = NULL;

	//////////////////////////Usun k1//////////////////////////////////////
	Head = Usun(Head, k1);

	//////////////////////////Wstawienie X elementow///////////////////////
	Head = generate(Head, x);

	////////////////////Wstaw element k2///////////////////////////////////
	Head = add(Head, k2);

	/////////////////////Usun element k2///////////////////////////////////
	Head = Usun(Head, k2);

	/////////////////////////Wyszukaj K3///////////////////////////////////
	Wyszukaj(Head, k3);

	/////////////////////////Dodaj K4//////////////////////////////////////
	Head = add(Head, k4);

	/////////////////////////usun k4///////////////////////////////////////
	Head = Usun(Head, k4);

	///////////////////////// ============> ///////////////////////////////
	DrukujListe(Head, 'F');

	///////////////////////// <=========== ////////////////////////////////
	DrukujListe(Head, 'B');

	///////////////////////Usun Wszystkie//////////////////////////////////
	UsunWszystkie(Head);

	/////////////////////////czas stop/////////////////////////////////////
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\n\n\n\n%f\n", time_spent);
	///////////////////////////////////////////////////////////////////////
	system("PAUSE");
	return 0;
}