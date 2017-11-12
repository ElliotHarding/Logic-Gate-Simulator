#include "attachers.h"

void attacher::draw(sf::RenderWindow& window,sf::Transform t) {
	sf::CircleShape circle;//for some reason I need to create a new circle each time i draw it. Something to do with the SFML library
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPosition(position);
	window.draw(circle,t);
}

attacher::attacher() {
	position = sf::Vector2f(0, 0);
	hb.widthX = radius * 2;
	hb.widthY = radius * 2;
}

attacher::~attacher() {}
inputAttacher::~inputAttacher() {

}
outputAttacher::~outputAttacher() {

}