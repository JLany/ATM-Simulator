#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <iomanip>


class Screen {
public:
	void displayMessage() const { /* empty body */ } // base function for template
	template<typename T, typename... Types>
	void displayMessage(const T& arg, const Types&... args) const {
		std::cout << std::fixed << std::setprecision(2); // set output formatting
		std::cout << arg;
		displayMessage(args...);
	} // end function template displayMessage

	void displayMessageLine() const { std::cout << "\n"; } // base function for template
	template<typename T, typename... Types>
	void displayMessageLine(const T& arg, const Types&... args) const {
		std::cout << std::fixed << std::setprecision(2); // set output formatting
		std::cout << arg;
		displayMessageLine(args...);
	} // end function template displayMessageLine

	void clear() const;
	void hold(int) const;
}; // end class Screen

#endif // SCREEN_H
