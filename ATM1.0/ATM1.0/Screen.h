#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
public:
	void displayMessage(const std::string&) const;
	void displayMessageLine(const std::string&) const;
}; // end class Screen

#endif // SCREEN_H
