// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//Define: Ilo�� krok�w
#define MAXSTEPS 6
#define MINSTEPS 2
//Define: D�ugo�� kroku
#define MAXTIME 8
#define MINTIME 1
//Define: z op�nieniem czy nie
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
	D = 'D', //Dzia�a
	W = 'W', //Wstrzymany oczekuje na przydzia� procesora
	Z = 'Z'  //Zako�czony
};