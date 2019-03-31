#pragma once
#include <SFML/Graphics.hpp>
#include "gameObjectFunctions.h"
#include "image.h"
#include <iostream>
#include "box.h"
using namespace std;

class gateButton : public clickable, public image {
private:
	using::clickable::isHover;
	sf::Text Text;
	sf::Font font;
	sf::Vector2f descriptionBoxOffset = sf::Vector2f(10, 10);
public:
	void draw(sf::RenderWindow& window);
	void init(std::string fileLocation, sf::Vector2f scale);
	void initDesciptionBox();
	gateButton();
	~gateButton();

	//shall be made private later with "using::"
	void drawDescription(sf::RenderWindow& window);
	std::vector<std::string> description;
	box descriptionBox = box(40, 40, 1, sf::Vector2f(0, 0));
	using::clickable::isClicked; //code here as a reminder, as aready inherited correctly
};