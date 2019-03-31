#pragma once
#include <SFML/Graphics.hpp>
#include "location.h"
class box : public location {
private:
	sf::RectangleShape shape;
public:
	sf::Color color = sf::Color(175, 175, 175);

	void draw(sf::RenderWindow& window);

	box(float width_, float height_, float outlineSize, sf::Vector2f position_ = sf::Vector2f(0, 0),
		sf::Color fixedColor = sf::Color(0, 0, 0, 0));
};