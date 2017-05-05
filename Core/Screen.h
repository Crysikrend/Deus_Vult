#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen abstract {
public:
	virtual void init() = 0;
	virtual bool update(const sf::Time&) = 0;
	virtual void render(const sf::Time&) = 0;
	virtual void quit() = 0;
};

#endif