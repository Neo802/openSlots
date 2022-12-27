#pragma once
#include <iostream>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

void usleep(__int64 usec);

class Wheel {
private:
	int cycle[10];
	int place_tracker;
public:
	Wheel();
	void update();
	int get_first();
	int get_second();
	int get_third();
};