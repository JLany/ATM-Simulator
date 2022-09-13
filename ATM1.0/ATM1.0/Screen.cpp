#include "Screen.h"
#include <chrono>
#include <thread>
using namespace std;

void Screen::clear() const {
	system("cls");
} // end function clear

void Screen::hold(int aDuration) const {
	chrono::seconds sleepDuration(aDuration);
	this_thread::sleep_for(sleepDuration);
} // end function hold
