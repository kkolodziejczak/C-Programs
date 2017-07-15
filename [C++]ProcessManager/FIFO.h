#pragma once
#include "Process.h"

class Process;

class FIFO: public Strategy
{
public:
	virtual Process* getProcess(std::vector<Process *> que) override
	{//First In First Out.
			int i = 0;
			while (que[i]->getStatus() == Z && i<que.size())
			{
					++i;
					if (i >= que.size())
					{
						i--;
						break;
					}
			}
	return que[i];
	};
};
