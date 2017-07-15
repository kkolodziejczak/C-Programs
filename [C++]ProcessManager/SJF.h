#pragma once
#include "stdafx.h"
#include "Strategy.h"

class Process;

class SJF : public Strategy
{
public:
	virtual Process* getProcess(std::vector<Process *> que) override
	{
		int i=0;
		int min=32000;
		int minPosition=0;

		for (i = 0; i < que.size();i++)
		{			
			if (que[i]->getStepsLeft() < min && que[i]->getStatus() != Z)
			{
				min = que[i]->getStepsLeft();
				minPosition = i;
			}
		}

		return que[minPosition];
	};
};