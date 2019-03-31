#include "button.h"
#include <iostream>
using namespace std;

button::button(sf::Color defaultColor_, sf::Color pressedColor_, sf::Color hoverColor_, sf::Vector2f position_,
	float height, float width, float outlineThickness, bool hasBoarder, string txt_
	, unsigned int fontSize
	) {
	defaultColor = defaultColor_;
	hoverColor = hoverColor_;
	pressedColor = pressedColor_;
	hb.widthX = width;
	hb.widthY = height;
	position = position_;//position needed for hitbox, therefore cant just used passed value (position_) to set location of button

	//text
	txt = txt_;
	Text.setCharacterSize(fontSize);
	Text.setStyle(sf::Text::Regular);
	Text.setFillColor(sf::Color::Black);
	Text.setOutlineColor(sf::Color::Black);
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font" << endl;
	}
	Text.setFont(font);
	Text.setString(txt);
	Text.setPosition(location::position + sf::Vector2f(width / 4, height / 4));

	shape = box(width, height, outlineThickness, position_);
}

button::button() {

}

void button::draw(sf::RenderWindow& window) {

	if (isClicked(window)) {
		shape.color = pressedColor;
	}
	else if (isHover(window)) {
		shape.color = hoverColor;
	}
	else {
		shape.color = defaultColor;
	}

	shape.position = position;//needed for boolReader and 4bitReader
	Text.setPosition(location::position + sf::Vector2f(hb.widthX / 4, hb.widthY / 4));

	shape.draw(window);
	window.draw(Text);
}