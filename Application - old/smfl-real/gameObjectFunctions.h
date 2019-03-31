#pragma once
#include "location.h"
#include <SFML/Graphics.hpp>

class hitBox {
public:
	float widthX;
	float widthY;
};

class clickable : public location {
public:
	hitBox hb;

	bool isHover(sf::RenderWindow& window);
	bool isClicked(sf::RenderWindow& window);
};

class dragable : public clickable {
public:
	void drag(sf::RenderWindow& window);
};

class rotation : public dragable {
public:
	float rotationAmount = 0;

	void checkRotation(sf::RenderWindow& window);
};