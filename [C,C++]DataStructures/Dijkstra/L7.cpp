#include "stdafx.h"
#include <time.h>
#include "inlab07.h"
#include <iostream>
#include <vector>

clock_t begin, end;
double time_spent;

struct CityBeen
{
	std::string name;
	std::string parent;
	int dist=0;
};

std::vector<CityBeen> been;

std::vector<CityBeen> sort(std::vector<CityBeen> tmp)
{
	for (int i = 0; i < tmp.size(); i++)
	{
		for (int j = 0; j < tmp.size() - 1; j++)
		{
			if (tmp[j].dist > tmp[j + 1].dist)
				std::swap(tmp[j], tmp[j + 1]);

		}
	}
	return tmp;
}

int findCityNumber(std::string city)
{
	for (int i = 0; i < 39;i++)
		if (miastoLabel[i] == city) return i;
	return 1;
}

std::vector<CityBeen> getposibleRoutes(std::string city)
{
	std::vector <CityBeen> tmp;

	int number = findCityNumber(city);

	for (int i = 0; i < 39;i++)
	{
		if (distances[number][i] > 0)
		{
			CityBeen tmp2;
			tmp2.name = miastoLabel[i];
			tmp2.dist = distances[number][i];
			tmp.push_back(tmp2);
		}
	}
	for (int i = 0; i < tmp.size(); i++)
	{
		for (int j = 0; j < tmp.size() - 1; j++)
		{
			if (tmp[j].dist > tmp[j + 1].dist)
				std::swap(tmp[j], tmp[j + 1]);

		}
	}
	return tmp;
}


bool IsConnected(std::string city1, std::string city2)
{
	auto a = getposibleRoutes(city1);
	for (auto b : a)
		if (b.name == city2)
			return true;
	return false;
};

int getDist(std::string start, std::string goal)
{
	return distances[findCityNumber(start)][findCityNumber(goal)];
}

CityBeen getParent(std::string parent)
{
	for (auto a :been)
	{
		if (a.name == parent)
			return a;
	}

}

int getRoute()
{
	int dist = 0;

	CityBeen current = been[been.size() - 1];
	
	while (current.parent != "")
	{
		dist += getDist(current.name,current.parent);
		//std::cout << current.name << "->" << current.parent << " [" << getDist(current.name, current.parent) << "] -> ";
		current = getParent(current.parent);
	}
	been.erase(been.begin() + been.size() - 1);
	return dist;
};
//do beena dodawanie kolejnych miast +1 i wten sposób będziemy wiedzieli któe po kolei nastoąpiły :d (Y) !! SAD :ASDSA
bool Been(std::string city)
{
	for (auto a : been)
		if (a.name == city)
			return true;
	return false;
}

int Dijkstry(std::string beginning, std::string destiny)
{
	if (beginning == destiny)
		return 0;
		//Krok 0: Przyjmij, że na początku nie byłeś w żadnym polu labiryntu, a więc wszystkie pola są nieodwiedzone.
		//Krok 1 : Umieść w kolejce Q pole s.W polu s umieść liczbę 0 (zero).
	std::vector<CityBeen> que;
	CityBeen Q;
	Q.name = beginning;
	que.push_back(Q);

	int dist = 32716;
		//Krok 2 : Dopóki kolejka Q nie jest pusta wykonuj kroki 3 - 5
		
	que = sort(que);
		CityBeen tmp2;
		tmp2 = que.front();

		been.push_back(tmp2);
	while (!que.empty())
	{

		//Krok 3 : Usuń z kolejki Q jej pierwszy element - oznaczmy to pole przez v
		auto v = que.front();
		que.erase(que.begin());
		//Krok 4 : Dla każdego pola w sąsiedniego względem v i nie oddzielonego od niego ścianą wykonaj krok 5
		std::vector<CityBeen> routes = getposibleRoutes(v.name);
		for (auto w : routes)
		{
			//Krok 5 : Jeśli nie byłeś jeszcze w polu w, to umieść w nim liczbę o jeden wiesza od liczby znajdującej się w polu v.
			//		   Jeśli pole w zawiera wyjście to przejdź do kroku 6, a w przeciwnym razie dołącz w do końca kolejki Q
			if (!Been(w.name) || w.name == destiny)
			{
				if (w.name == destiny)
				{
					CityBeen W;
					W.name = w.name;
					W.parent = v.name;
					W.dist = v.dist + w.dist;
					been.push_back(W);
						auto a = getRoute();
					if (dist > a)
						dist = a;
					//std::cout << dist<<"\n";
				}
				else
				{
					que.push_back(w);
					CityBeen tmp2;
					tmp2.name = w.name;
					tmp2.parent = v.name;
					tmp2.dist = w.dist + v.dist;
					been.push_back(tmp2);
				}
			}
		}
	}
		//Krok 6 : {W tym kroku budujemy od końca listę pól tworzących najkrótszą drogę z pola s do pola w, na którym zakończył działanie krok 5}
		//Dopóki w nie jest polem s, wykonuj : za kolejne(od końca) pole drogi przyjmij w i za nową wartość w przyjmij sąsiednie względem w, w którym znajduje się liczba o jeden mniejsza od liczby znajdującej się w obecnym polu w.
	been.clear(); // czyszczenie vectora z odwiedzonymi miastami :D (facepalm)
	return dist;
}

int distBetween(std::string start, std::string goal)
{
	auto x = miasta[findCityNumber(goal)][0] - miasta[findCityNumber(start)][0];
	auto y = miasta[findCityNumber(goal)][1] - miasta[findCityNumber(start)][1];
	return sqrt(x*x + y*y);
};

std::vector<CityBeen> getposibleRoutesA(std::string city, std::string goal)
{
	std::vector <CityBeen> tmp;

	int number = findCityNumber(city);

	for (int i = 0; i < 39; i++)
	{
		if (distances[number][i] > 0)
		{
			CityBeen tmp2;
			tmp2.name = miastoLabel[i];
			tmp2.dist = distBetween(city, goal);
			tmp.push_back(tmp2);
		}
	}
	
	return sort(tmp);
}

bool BeenOpen(std::vector<CityBeen> que, std::string city)
{
	for (auto a: que)
	{
		 if (a.name == city)
		 {
			 return true;
		 }
	}
	return false;
};

int AStar(std::string beginning, std::string destiny)
{
	if (beginning == destiny)
		return 0;
	//Krok 0: Przyjmij, że na początku nie byłeś w żadnym polu labiryntu, a więc wszystkie pola są nieodwiedzone.
	//Krok 1 : Umieść w kolejce Q pole s.W polu s umieść liczbę 0 (zero).
	std::vector<CityBeen> que;
	CityBeen Q;
	Q.name = beginning;
	que.push_back(Q);

	int dist = distBetween(beginning, destiny);
	//Krok 2 : Dopóki kolejka Q nie jest pusta wykonuj kroki 3 - 5
	CityBeen tmp2;
	tmp2 = que.front();
	been.push_back(tmp2);
	
	int g[39];
	int h[39];
	int f[39];

	while (!que.empty())
	{
		//TODO que = sort(que);
		//Krok 3 : Usuń z kolejki Q jej pierwszy element - oznaczmy to pole przez v
		auto v = que.front();
		que.erase(que.begin());
		//Krok 4 : Dla każdego pola w sąsiedniego względem v i nie oddzielonego od niego ścianą wykonaj krok 5
		std::vector<CityBeen> routes = getposibleRoutesA(v.name, destiny);

		for (auto b : routes)
			que.push_back(b);

		que = sort(que);
		for (auto w : routes)
		{

			if (!Been(w.name))
				continue;

			int tmp_g = g[findCityNumber(w.name)] + getDist(v.name, w.name);
			bool better = false;

			if (!BeenOpen(que, w.name))
			{
				better = true;
			}
			else
			{
				if( tmp_g < g[findCityNumber(w.name)] || g[findCityNumber(w.name)] == -10)
				{
					better = true;
				}
			}

			if(better == true)
			{
				g[findCityNumber(w.name)] = tmp_g;
				f[findCityNumber(w.name)] = g[findCityNumber(w.name)] + h[findCityNumber(w.name)];
			}
			/*
			if (!Been(w.name) || w.name == destiny)
			{
				if (w.name == destiny)
				{
					CityBeen W;
					W.name = w.name;
					W.parent = v.name;
					been.push_back(W);
					auto a = getRoute();
					if (dist > a)
						dist = a;
					//std::cout << dist << "\n";
				}
				else
				{
					que.push_back(w);
					CityBeen tmp2;
					tmp2.name = w.name;
					tmp2.parent = v.name;
					been.push_back(tmp2);
				}
			}*/
		}
	}
	//Krok 6 : {W tym kroku budujemy od końca listę pól tworzących najkrótszą drogę z pola s do pola w, na którym zakończył działanie krok 5}
	//Dopóki w nie jest polem s, wykonuj : za kolejne(od końca) pole drogi przyjmij w i za nową wartość w przyjmij sąsiednie względem w, w którym znajduje się liczba o jeden mniejsza od liczby znajdującej się w obecnym polu w.
	been.clear(); // czyszczenie vectora z odwiedzonymi miastami :D (facepalm)
	return dist;
}

void printTimeSpent()
{
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << time_spent << std::endl;

	begin = 0;
	end = 0;
	time_spent = 0;
}

void test()
{
	for (int i = 0; i < 39; i++)
	{
		std::cout << miastoLabel[i] << " : \t\tDijkstry -> " << Dijkstry("Szczecin", miastoLabel[i]) << "\tA* -> " << AStar("Szczecin", miastoLabel[i])<< "[km]\n";
	}
}

int main()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~dijksty~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// czas start;

	test();

	begin = clock();
		// oblicz i wypisz najkrótszą ścieżkę za pomocą algorytmu Dijkstry pomiędzy Szczecinem a Krakowem
		std::cout << "Droga z Szczecina do Krakowa to "<<Dijkstry("Szczecin", "Krakow") << "km.\n";
		std::cout << AStar("Szczecin", "Przemysl") << "\n";
	//	 czas stop, wypisz czas;
	end = clock();
	printTimeSpent();

	// czas start;
	begin = clock();
		// wykonaj 1.000.000 razy:
		for (long i = 0; i < 1000000;i++) // 1 000 000
		{
			Dijkstry("Szczecin", "Przemysl");
			//o oblicz najkrótszą ścieżkę za pomocą algorytmu Dijkstry pomiędzy Szczecinem a Przemyślem
		}
	//	 czas stop, wypisz czas;
	end = clock();
	printTimeSpent();


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~A*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// czas start;
	begin = clock();
		// oblicz i wypisz najkrótszą ścieżkę za pomocą algorytmu A* pomiędzy Szczecinem a Krakowem
		AStar("Szczecin", "Krakow");
	//	 czas stop, wypisz czas;
	end = clock();
	printTimeSpent();

	// czas start;
	begin = clock();
		// wykonaj 1.000.000 razy:
		for (long i = 0; i < 1000000; i++) // 1 000 000
		{
			//o oblicz najkrótszą ścieżkę za pomocą algorytmu A* pomiędzy Szczecinem a Przemyślem
			AStar("Szczecin", "Przemysl");
		}
	//	 czas stop, wypisz czas;
	end = clock();
	printTimeSpent();

	system("PAUSE");
    return 0;
}

