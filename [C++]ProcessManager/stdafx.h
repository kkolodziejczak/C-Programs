// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//Define: Iloœæ kroków
#define MAXSTEPS 6
#define MINSTEPS 2
//Define: D³ugoœæ kroku
#define MAXTIME 8
#define MINTIME 1
//Define: z opóŸnieniem czy nie
#define DoTime 0

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <queue>
#include <vector>
#include <windows.h>
enum status
{
	D = 'D', //Dzia³a
	W = 'W', //Wstrzymany oczekuje na przydzia³ procesora
	Z = 'Z'  //Zakoñczony
};