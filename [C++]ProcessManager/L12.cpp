// L13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Manager.h"
#include "FIFO.h"
#include "SJF.h"

int main()
{
	srand(time(NULL));
	
	std::vector < Process *> tmp;
	for (int i = 0; i < 8; i++)
		tmp.push_back(new Process(i, rand() % MAXSTEPS + MINSTEPS, rand() % MAXTIME + MINTIME, W));

	auto tmp2(tmp);// dziwne vectory ponoæ konstruktor kopiuj¹cy tworzy kopiê obiektu a nie wskazuje na niego...

	std::cout << "======================FIFO=======================\n";
	Manager *manager = new Manager(new FIFO,tmp);
	manager->start();
	manager->ShowProcessHistory();

	std::cout << "======================SJF========================\n";

	Manager *manager2 = new Manager(new SJF,tmp2);
	manager2->start();
	manager2->ShowProcessHistory();
	
	delete manager;
	delete manager2;

	system("PAUSE");
	return 0;
}

