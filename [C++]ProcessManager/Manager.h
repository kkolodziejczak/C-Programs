#pragma once
#include "stdafx.h"
#include "History.h"
#include "Process.h"
#include "Strategy.h"
class Process;

#if DoTime
#define WaitTime(x) Sleep(x*1000);
#else
#define WaitTime(x) 
#endif

class Manager
{
public:
	Manager() {};
	Manager(Strategy* strat, std::vector < Process *> n) :lastAddedID(0), strat(strat)
	{
		history = new History;
		for (int i = 0; i < n.size(); i++)
		{
			this->pushToQueue(new Process(i, n[i]->getStepsToDo(), n[i]->getTimeForOneProcess(), W));
			history->addToHistory("");
		}
	}
	Manager(Strategy* strat,int n) :lastAddedID(0), strat(strat)
	{
		history = new History;
		for (int i = 0; i < n; i++)
		{
			this->pushToQueue(new Process(i, rand() % MAXSTEPS + MINSTEPS, rand() % MAXTIME + MINTIME, W));
			history->addToHistory("");
		}		
	}
	History* getHistory() { return history; };
	virtual ~Manager()
	{
		delete history;
		delete strat;
	};
	void ShowProcessHistory()	{ history->printHistory(); };
	long getlastID() const;
	void setLastID(long last_id);
	std::vector<Process*> getQueue() const;
	void pushToQueue(Process *);
	void start()
	{
		bool change= true;
		int done=0;
		while (change)
		{
			auto v = strat->getProcess(Queue);
				if (v->getStatus() != 'Z')
				{
					v->setStatus(D);
					WaitTime(v->getTimeForOneProcess());
					for (int i = 0; i < Queue.size(); i++)
					{
						if (Queue[i]->getStepsLeft() <= 0) Queue[i]->setStatus(Z);
						history->addToHistory(i, Queue[i]->getStatus());
					}
					v->subStepsLeft();
					change = true;
				}
				else
				{
					done++;
					if (done > Queue.size())
						change = false;
				}			
		}
	}
	void reset()
	{
		for (auto v: Queue)
		{
			v->setStepsLeft(v->getStepsToDo());
			v->setStatus(W);
		}
	};

private:
	long lastAddedID;
	Strategy *strat;
	History *history; // wskaŸnik na historiê zaczerpniêty od Artura, lepiej jest przechowywaæ go tutaj niz tworzyæ poza klas¹ i dodawaæ jako parametr.
	std::vector < Process *> Queue; 
};

