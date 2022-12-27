#include "wheel.h"
using namespace std;

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}

Wheel::Wheel() {
	for (int i = 0; i < 10; i++)
		cycle[i] = i / 2;

	int shuffle_times = rand() % 50;
	while (shuffle_times > 0) {
		int tmpindex = rand() % 10;
		int swapindex = rand() % 10;

		int tmp = cycle[tmpindex];
		int tmp2 = cycle[swapindex];
		cycle[tmpindex] = tmp2;
		cycle[swapindex] = tmp;
		shuffle_times--;
	}

	place_tracker = 1;
}

void Wheel::update() {
	if (place_tracker < 8)
		place_tracker++;
	else
		place_tracker = 0;
}

int Wheel::get_first() {
	return cycle[place_tracker];
}

int Wheel::get_second() {
	return cycle[place_tracker + 1];
}

int Wheel::get_third() {
	return cycle[place_tracker + 2];
}

