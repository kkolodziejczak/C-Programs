#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#pragma warning(disable: 4996)


unsigned long int _holdrand;
unsigned long generateNumber( long n)
{
	return (rand()*rand() + rand()) % n;
}
//unsigned long int generateNumber(long int n) {
//	return (_holdrand = (_holdrand * 214013L + 2531011L) >> 32) % n;
//};

std::string IntToBin(long value)
{
	long r;
	long Value = value;
	std::stringstream arr,temp;

	while (Value != 0)
	{
		r = Value % 2;
		arr << r;
		Value /= 2;
	}

	for (int i = arr.str().size(); i > 0;i--)
	{
		temp << arr.str()[i-1];
	}
	return temp.str();
}

enum level{
	minimum,
	maximum
};

struct HeapNode
{
	long Value;
	level Level;
	HeapNode *right = NULL;
	HeapNode *left = NULL;
};


class Heap
{
public:
	Heap() : NumberOfNodes(0)
	{
		root = new HeapNode;
	};

	void insert(long Value)
	{// wstawienie do kopca nowego elementu o wartości składowej kluczowej podanej jako argument funkcji;
		//idz na koniec według ilości dodanych elementów

#pragma region Faza I
		NumberOfNodes++;
		std::string road = IntToBin(NumberOfNodes); // dorga do nowego elementu

		if (road.size() == 1) // jeżeli Root jest pusty.
		{
			root->Value = Value;
			root->Level = minimum;
		}
		else
		{
			int i = 0;
			HeapNode *tmp = this->root;
			while (i < road.size() - 2) // znajdowanie miejsca do wstawienia. // poziomów
			{
				if (road[i + 1] == '1') tmp = tmp->right;
				else tmp = tmp->left;
				i++;
			}

			//tworzymy nowy obiekt do kopca 
			HeapNode *newNode = new HeapNode;
			newNode->Value = Value;
			if (road.size() % 2 == 1) newNode->Level = minimum;
			else newNode->Level = maximum;
			///////////////////////////////

			if (tmp->left == NULL) // jeżeli lewe poddrzewo Roota jest puste to wstaw tam
				tmp->left = newNode;
			else
				tmp->right = newNode;
		}
#pragma endregion 

//FAZA II
		if (road.size() > 1)
		{
			//sprawdzenie czy wstawiony element nie psuje szyku kopca MINIMAKSOWEGO.

			std::string Parent = "", Grandfather = "";
			for (int i = 0; i < road.size() - 1; i++)
				Parent += road[i];
			for (int i = 0; i < road.size() - 2; i++)
				Grandfather += road[i];

			HeapNode *newNode, *parent, *grandfather;
			

			newNode = getNode(this->root, road);
			parent = getNode(this->root, Parent);
			grandfather = getNode(this->root, Grandfather);

			//root case;
			if (grandfather == NULL)
			{
				if (newNode->Value < parent->Value)
				{
					auto tmp = newNode->Value;
					newNode->Value = parent->Value;
					parent->Value = tmp;
				}
			}
			else
			{
			HeapNode * NewNodePos = NULL;
			std::string newNodeRoad = "";
				if (parent->Level == 0 && grandfather->Level == 1) // parent = min gfather = max
				{
					if (newNode->Value > parent->Value && newNode->Value < grandfather->Value)
					{
						//jeżeli wartość klucza nowego węzła mieści się w przedziale wyznaczonym przez wartości kluczy obu przodków,
						// to kończy się rekonstrukcję(węzeł pozostaje na swoim miejscu);
					}
					else
					{
						//jeżeli wartość klucza nowego węzła jest mniejsza od wartości klucza tego z przodków, który znajduje się na poziomie „minimum”,
						//	to nowy węzeł jest zamieniany z tym przodkiem miejscami i następuje przejście do fazy 3;
						if (newNode->Value < parent->Value) // min
						{
							auto tmp = newNode->Value;
							newNode->Value = parent->Value;
							parent->Value = tmp;
							NewNodePos = parent;
							newNodeRoad = Parent;
						}else
						{
							//jeżeli wartość klucza nowego węzła jest większa od wartości klucza tego z przodków, który znajduje się na poziomie „maksimum”,
							//	to nowy węzeł jest zamieniany z tym przodkiem miejscami i następuje przejście do fazy 3.
							if (newNode->Value > grandfather->Value) // max
							{
								auto tmp = newNode->Value;
								newNode->Value = grandfather->Value;
								grandfather->Value = tmp;
								NewNodePos = grandfather;
								newNodeRoad = Grandfather;
							}	
						}
					}
				}
				else// parent = max gfather = min
				{
					if (newNode->Value < parent->Value && newNode->Value > grandfather->Value)
					{
						//jeżeli wartość klucza nowego węzła mieści się w przedziale wyznaczonym przez wartości kluczy obu przodków,
						// to kończy się rekonstrukcję(węzeł pozostaje na swoim miejscu);
					}
					else
					{
						//jeżeli wartość klucza nowego węzła jest większa od wartości klucza tego z przodków, który znajduje się na poziomie „maksimum”,
						//	to nowy węzeł jest zamieniany z tym przodkiem miejscami i następuje przejście do fazy 3.
						if (newNode->Value > parent->Value) // max
						{
							auto tmp = newNode->Value;
							newNode->Value = parent->Value;
							parent->Value = tmp;
							NewNodePos = parent;
							newNodeRoad = Parent;
						}else
						{
							//jeżeli wartość klucza nowego węzła jest mniejsza od wartości klucza tego z przodków, który znajduje się na poziomie „minimum”,
							//	to nowy węzeł jest zamieniany z tym przodkiem miejscami i następuje przejście do fazy 3;
							if (newNode->Value < grandfather->Value) // min
							{
								auto tmp = newNode->Value;
								newNode->Value = grandfather->Value;
								grandfather->Value = tmp;
								NewNodePos = grandfather;
								newNodeRoad = Grandfather;
							}
						}
					}
				}
//FAZA III
		/*
		”Wędrówka” w górę kopca i kolejne zamiany(dopóki nie zostanie przywrócony porządek kopcowy lub nie dotrze się do korzenia,
		  albo jego bezpośrednich potomków znajdujących się na poziomie „maksimum”); 
		  w tej fazie analizowane są wyłącznie relacje kluczy „wędrującego” węzła i kluczy węzłów na poziomach takich samych, 
		  jak zajęty przez nowy węzeł po zakończeniu fazy 2 („maksimum” albo „minimum” – porównania dokonywane są co drugi poziom).
		*/
				while (newNodeRoad.size() >0)
				{
					
					if (newNodeRoad.size() >0 && NewNodePos != this->root)
					{
						Grandfather = "";
						for (int i = 0; i < newNodeRoad.size() - 2; i++)
							Grandfather += road[i];
					
						if (Grandfather == "")
						{
							if (NewNodePos->Level == 0)// grandfather == "" root i root tylko minimum
							{
								if (NewNodePos->Value < this->root->Value)
								{
									swap(newNode, root);
									NewNodePos = root;
									newNodeRoad = Grandfather;
								}

							}
							newNodeRoad = Grandfather;
						}
						else
						{
							newNode = getNode(this->root, newNodeRoad);
							grandfather = getNode(this->root, Grandfather);
						
							if (newNode->Level == 0)// sprawdzanie czy max czy min
							{
								if (newNode->Value < grandfather->Value)
								{
									swap(newNode, grandfather);
									NewNodePos = grandfather;
									newNodeRoad = Grandfather;
								}
							}
							else
							{
								if (newNode->Value > grandfather->Value)
								{
									swap(newNode, grandfather);
									NewNodePos = grandfather;	
									newNodeRoad = Grandfather;
								}
							}
						}
					}
					if (Grandfather == "1")
						newNodeRoad = "";
					else
						newNodeRoad = Grandfather;
				}//endWhile
			}



		}




#pragma endregion 
}
	HeapNode * getNode(HeapNode* Root, std::string road)
	{// Root-> początek kopca// road-> droga w postaci binarnego numeru noda 
		if (road.size()>=1)
		{
		HeapNode *tmp = Root;
		int i = 0;
			while (i < road.size() - 1) // znajdowanie miejsca do wstawienia. // poziomów
			{
				if (road[i + 1] == '1') tmp = tmp->right;
				else tmp = tmp->left;
				i++;
			}

			return tmp;
		}
		else
		{
			return NULL;
		}
	}
	void swap(HeapNode*& wsk1, HeapNode *&wsk2)
	{
		auto tmp = wsk1->Value;
		wsk1->Value = wsk2->Value;
		wsk2->Value = tmp;
	}
	void insertN(int N)
	{// wstawienie do kopca X nowych elementów o wygenerowanych losowo wartościach składowych kluczowych z zakresu 10 do 1 000 000 (wartość X podana jako argument funkcji);
		//int tab[] = {5,70,40,30,9,7,15,45,50,30,20,12,10,45,2};
		//15
		for (int i = 0; i < N;i++) // wstawienie N elementów do kopca
		{
			long value = generateNumber(999990) + 10;// zakres 10 -> 1 000 000
			//insert(tab[i]);
			insert(value);
		}
	};
	void deleteMinMax(int i)
	{// usunięcie z kopca elementu o : i<0 min i>0 max
		//FAZA I
		//Usunięcie węzła(węzeł o najmniejszej wartości klucza jest korzeniem; węzeł o największej wartości klucza jest jednym z dwóch jego potomków –
		//należy wybrać jednego z nich porównując ich klucze) i umieszczenie na jego miejscu skrajnego prawego liścia z ostatniego poziomu kopca(niezależnie od poziomu, na którym się znajduje).
		HeapNode *newNode;
		if (i > 0) // max
		{
			HeapNode *max;
			if (root->left->Value > root->right->Value)	max = root->left;// znalezienie maxymalnej liczby
			else max = root->right;
			std::string roadToLast = IntToBin(NumberOfNodes);
			std::string roadToLastParent;
			for (int i = 0; i < roadToLast.size() - 1; i++)
				roadToLastParent += roadToLast[i];
			auto where = 'r';
			HeapNode *last = getNode(root, roadToLast); // znalezienie ostatniego wstawionego noda
			HeapNode *parent = getNode(root, roadToLastParent);
			if (parent->right == last)
				where = 'r';
			else
				where = 'l';
			
			swap(max, last); //zamiana wartości , i usunięcie maxa
			
			delete last;
			NumberOfNodes--;
			if (where == 'r')
				parent->right = NULL;
			else
				parent->left = NULL;
			newNode = max;// deklaracja dla jasnośći 
		}
		else // min
		{
			HeapNode *min;
			min = root;
			std::string roadToLast = IntToBin(NumberOfNodes);
			std::string roadToLastParent;
			for (int i = 0; i < roadToLast.size() - 1; i++)
				roadToLastParent += roadToLast[i];
			auto where = 'l';
			HeapNode *last = getNode(root, roadToLast); // znalezienie ostatniego wstawionego noda
			HeapNode *parent = getNode(root, roadToLastParent);
			if (parent->right == last)
			where = 'r';
			else
			where = 'l';

			swap(min, last); //zamiana wartości , i usunięcie maxa

			delete last;
			NumberOfNodes--;
			if (where == 'r')
				parent->right = NULL;
			else
				parent->left = NULL;
			newNode = min;// deklaracja dla jasnośći 
		}

		//FAZA II
		//”Wędrówka” w dół kopca i kolejne zamiany(dopóki nie osiągnie się porządku kopcowego lub nie dotrze się do poziomu ostatniego lub przedostatniego); 
		//♦jeżeli osiągnięto jeden z dwóch ostatnich poziomów, to następuje przejście do fazy 3; 
		//♦jeżeli przed osiągnięciem poziomu ostatniego lub przedostatniego przywrócono porządek kopcowy, to następuje koniec rekonstrukcji.
		HeapNode *LL, *LR, *RL, *RR;
		bool can = true;
		bool change = false;
		//jakieś zapętlnie dopuki nie będzie ostatniego przedostatniego
		while (can)
		{
			change = false;
			if (newNode->left != NULL && newNode->left->left != NULL)
				LL = newNode->left->left;
			else LL = NULL;

			if (newNode->left != NULL && newNode->left->right != NULL)
				LR = newNode->left->right;
			else LR = NULL;

			if (newNode->right != NULL && newNode->right->left != NULL)
				RL = newNode->right->left;
			else RL = NULL;

			if (newNode->right != NULL && newNode->right->right != NULL)
				RR = newNode->right->right;
			else RR = NULL;
			//tak długo puki nie dotrzemy na koniec albo nie będzie dobrze uporzątkowany kopiec.
			if (LL == NULL || LR == NULL || RL == NULL || RR == NULL)
				can = false;

			if (LL != NULL || LR != NULL || RL != NULL || RR != NULL) 
			{

				if (newNode->Level == maximum) // zamiana odwrotna jeżeli jest max i jest mniejsze od poprzedniego to zamina.
				{
					//wyszukanie największego klucza

					HeapNode * maxNode = LL;
					//wyszukanie najmniejszego klucza
					if (LL != NULL && LR != NULL) // jeżeli LL < LR to min = LL
						if (LL->Value > LR->Value)
							maxNode = LL;
						else
							maxNode = LR;
					if (RL != NULL)
						if (RL->Value > maxNode->Value) // jezeli RL < minnode to min = RL
							maxNode = RL;
					if (RR != NULL)
						if (RR->Value > maxNode->Value) //jeżeli RR < min node to min = RR
							maxNode = RR;

					if (newNode->Value < maxNode->Value)
					{
						swap(maxNode, newNode);
						newNode = maxNode;
						change = true;
					}
				}
				else
				{
					HeapNode * minNode = LL;
					//wyszukanie najmniejszego klucza
					if (LL != NULL && LR != NULL) // jeżeli LL < LR to min = LL
						if (LL->Value < LR->Value)
							minNode = LL;
						else
							minNode = LR;
					if (RL != NULL)
						if(RL->Value < minNode->Value) // jezeli RL < minnode to min = RL
							minNode = RL;
					if (RR != NULL)
						if(RR->Value < minNode->Value) //jeżeli RR < min node to min = RR
							minNode = RR;

					if (newNode->Value > minNode->Value)
					{
						swap( minNode, newNode );
						newNode = minNode;
						change = true;
					}
				}
			if (!change) return;
		}
	}// END WHILE		

//TOTO USUWANIE FAZA III

		LL = NULL, RR = NULL;
		if (newNode->left != NULL)
			LL = newNode->left;
		if (newNode->right != NULL)
			RR = newNode->right;

		if (LL != NULL || RR!= NULL)
			if (newNode->Level == minimum)
			{ 
				HeapNode * minNode = LL;
				if (LL != NULL && RR != NULL) // jeżeli LL < LR to min = LL
					if (LL->Value < RR->Value)
						minNode = LL;
					else
						minNode = RR;

				if (newNode->Value >minNode->Value)
					swap(newNode, minNode);
			}
			else // level = max
			{
				HeapNode * maxNode = LL;
				if (LL != NULL && RR != NULL) // jeżeli LL < LR to min = LL
					if (LL->Value < RR->Value)
						maxNode = LL;
					else
						maxNode = RR;

				if (newNode->Value < maxNode->Value)
					swap(newNode, maxNode);
			}
		// rozdzielenie na max i min. w porównywaniu 
		//Porównanie wartości klucza „wędrującego” węzła z kluczami bezpośredniego przodka i ewentualnych potomków; 
		//jeżeli jest to konieczne dla zachowania porządku w kopcu minimaksowym, to dokonuje się zamiany węzłów.
		// jeżeli jest min na max i max na min
}
	void deleteHeap(HeapNode *a)
	{// usunięcie wszystkich elementów z kopca(kolejne usuwanie węzłów o najmniejszej lub największej wartości dopóki kopiec będzie pusty);
		while(NumberOfNodes >0)
		{
			std::string roadToLast = IntToBin(NumberOfNodes);
			HeapNode *nodetoDelete = getNode(root, roadToLast);
			NumberOfNodes--;
			delete nodetoDelete;
		}
		root = NULL;
	}
	void printMaxMin()
	{// wyświetlenie wartość najmniejszej i największej składowej kluczowej;
		if (this->root != NULL)
		{
			std::cout << "\nMin :"<<this->root->Value << "\n";
			
			if (this->root->left != NULL)
			{
				if(root->left->Value > root->right->Value)
					std::cout << "Max :"<<this->root->left->Value << "\n";
				else
					std::cout << "Max :"<<this->root->right->Value << "\n";
			}
			else 
				std::cout << "Max :" <<this->root->Value<<"\n";
		}
		else
			std::cout << "Kopiec jest pusty!\n";
	}
	void printLevels(HeapNode *tmp, int level)
	{// wyświetlenie 4 pierwszych poziomów kopca w dowolny sposób pokazujący zależności pomiędzy węzłami.
		int i;
		if (tmp != NULL)
		{
			if (level +1 < 5)
			printLevels(tmp->right, level + 1);
			printf("\n");
			if (tmp == root)
				std::cout << "Root -> ";
			for (i = 0; i < level && tmp != root; i++)
				std::cout << "        ";
			std::cout << tmp->Value;
			if (level + 1 < 5)
			printLevels(tmp->left, level + 1);
		}
	}
	HeapNode * getRoot() { return root; }
private:
	long NumberOfNodes;
	HeapNode *root;
};

int main()
{
	clock_t begin, end;
	double time_spent;
	_holdrand = 1;
	srand(time(NULL));

	long int x1, x2, k1, k2;
	FILE* fp = fopen("inlab06.txt", "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %d %d %d", &x1, &x2, &k1, &k2);
	fclose(fp);

	// czas start;
	begin = clock();

	// zainicjuj kopiec;
	Heap *heap = new Heap;
	// wstaw X1 elementów do kopca;
	heap->insertN(x1);
	// wstaw element o wartości klucza k1;
	heap->insert(k1);
	// wstaw element o wartości klucza k2;
	heap->insert(k2);
	// usuń minimum;
	heap->deleteMinMax(-1);
	// usuń maksimum;
	heap->deleteMinMax(1);
	// wyświetl 4 pierwsze poziomy kopca;	
	heap->printLevels(heap->getRoot(), 1);
	std::cout << "\n\n\n\n";
	// usuń wszystkie elementy z kopca;
	heap->deleteHeap(heap->getRoot());



	Heap *heap2 = new Heap;
	// wstaw X2 elementów do kopca;
	heap2->insertN(x2);
	// usuń minimum;
	heap2->deleteMinMax(-1);
	// usuń maksimum;
	heap2->deleteMinMax(1);
	// wstaw element o wartości klucza k1;
	heap2->insert(k1);
	// wstaw element o wartości klucza k2;
	heap2->insert(k2);
	// wyświetl największą i najmniejszą wartość;
	heap2->printMaxMin();
	// usuń wszystkie elementy z kopca;
	heap2->deleteHeap(heap2->getRoot());
	// wyświetl największą i najmniejszą wartość; // powinno wypisać, że kopiec jest pusty
	heap2->printMaxMin();


	// czas stop;
	end = clock();
	// wypisz czas wykonania.
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time_spent << std::endl;
	delete heap;
	delete heap2;
	system("PAUSE");
    return 0;
}