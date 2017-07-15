#pragma once
#include "stdafx.h"

class History
{
public:
	History() :numbersOfCycles(0){};
	std::vector<std::string> getQueueHistory();
	void set_queue_history(const std::vector<std::string>& basic_strings);
	void addToHistory(std::string a);
	void addToHistory(char a);
	void addToHistory(int n, char a);
	void printHistory();
	long numbers_of_cycles() const;
	void addCycle() { numbersOfCycles++; };
	void set_numbers_of_cycles(long numbers_of_cycles);
private:
	long numbersOfCycles;
	std::vector <std::string> QueueHistory;
};

/*
00001:  DWDDDWWDZZZZZZZZZZ
00002 : WDWWWDDZZZZZZZZZZZ
00003 : WWWWWWWDDWWDDZZZZZ
00004 : WWWWWWWWWWWWWDDZZZ
00005 : WWWWWWWWWWWWWWWDDZ
*/