#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
public:
	template <class T, class... Types>
	void displayMessage(const T&, const Types&...) const;

	template <class T, class... Types>
	void displayMessageLine(const T&, const Types&...) const;

	void hold(int) const;
}; // end class Screen

#endif // SCREEN_H
