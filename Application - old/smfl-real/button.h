#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "gameObjectFunctions.h"
using namespace std;

class button : public clickable {
private:
	sf::Color pressedColor;
	sf::Color hoverColor;
	sf::Color defaultColor;

	sf::Text Text;
	sf::Font font;

	box shape = box(80, 40, 2);

public:
	std::string txt = "button";

	// constructor
	button(sf::Color defaultColor_, sf::Color pressedColor_, sf::Color hoverColor_, sf::Vector2f position_,
		float height = 40, float width = 80, float outlineThickness = 2, bool hasBoarder = true, string txt_ = "button"
		, unsigned int fontSize = 20
		);

	void draw(sf::RenderWindow& window);
	button();
};