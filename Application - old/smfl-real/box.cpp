#include "box.h"
void box::draw(sf::RenderWindow& window) {
	shape.setFillColor(color);
	shape.setPosition(position);
	window.draw(shape);
}

box::box(float width_, float height_, float outlineSize, sf::Vector2f position_, sf::Color fixedColor) {
	shape.setOutlineColor(sf::Color::Black);
	shape.setSize(sf::Vector2f(width_, height_));
	shape.setOutlineThickness(outlineSize);
	color = fixedColor;
	position = position_;
}
