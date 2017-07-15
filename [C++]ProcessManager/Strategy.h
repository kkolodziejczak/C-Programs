#pragma once
#include "stdafx.h"

class Process;

class Strategy
{
public:
	virtual Process* getProcess(std::vector<Process *> que) = 0;
};
