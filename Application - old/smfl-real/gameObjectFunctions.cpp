#include <SFML/Graphics.hpp>
#include "gameObjectFunctions.h"

bool clickable::isHover(sf::RenderWindow& window) {
	if (sf::Mouse::getPosition(window).x > position.x
		&& sf::Mouse::getPosition(window).x < position.x + hb.widthX
		&& sf::Mouse::getPosition(window).y > position.y
		&& sf::Mouse::getPosition(window).y < position.y + hb.widthY
		) {
		return true;
	}
	return false;
}

bool clickable::isClicked(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHover(window)
		) {
		return true;
	}
	return false;
}


void dragable::drag(sf::RenderWindow& window) {
	if (isClicked(window)) {
		position = sf::Vector2f(sf::Mouse::getPosition(window).x - hb.widthX / 2, sf::Mouse::getPosition(window).y - hb.widthY / 2);
	}
}


void rotation::checkRotation(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isHover(window)) {
		if (rotationAmount > 269) {
			rotationAmount = 0;
		}
		else {
			rotationAmount += 90;
		}
		sf::sleep(sf::milliseconds(100));
	}
}