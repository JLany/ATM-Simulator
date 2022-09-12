#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include "Screen.h"
using namespace std;


void displayMessage() {}
template <class T, class... Types>
void Screen::displayMessage(const T& arg, const Types&... args) const {
	cout << fixed << setprecision(2); // set output formatting
	cout << arg;

	displayMessage(args...);
}

void displayMessageLine() { cout << "\n"; }
template <class T, class... Types>
void Screen::displayMessageLine(const T& arg, const Types&... args) const {
	cout << fixed << setprecision(2); // set output formatting
	cout << arg;

	displayMessageLine(args...);
}

void Screen::hold(int aDuration) const {
	chrono::seconds duration(aDuration);
	this_thread::sleep_for(duration);
} // end function hold

void Screen::clear() const {
	system("clear");
} // end function clear
