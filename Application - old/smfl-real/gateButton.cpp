#include "gateButton.h"

void gateButton::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	drawDescription(window);
}

void gateButton::drawDescription(sf::RenderWindow& window) {
	if (isHover(window)) {
		descriptionBox.draw(window);
		for (size_t x = 0; x < description.size(); x++) {
			Text.setString(description[x]);
			Text.setPosition(position.x + descriptionBoxOffset.x, position.y + x * 22 + descriptionBoxOffset.y);
			window.draw(Text);
		}
	}
}

void gateButton::init(std::string fileLocation, sf::Vector2f scale) {
	loadTexture(fileLocation);
	sprite.setScale(scale);
	sprite.setPosition(position);
	initDesciptionBox();
}

void gateButton::initDesciptionBox() {
	int longest = 0;
	for (size_t x = 0; x < description.size();x++) {
		if ((unsigned)longest < description[x].length()) {
			longest = description[x].length();
		}
	}
	descriptionBox = box(8 * float(longest), float(description.size()) * 22, 1, position + descriptionBoxOffset, sf::Color(200, 200, 200));
}

gateButton::gateButton() {
	Text.setCharacterSize(15);
	Text.setStyle(sf::Text::Regular);
	Text.setFillColor(sf::Color::Black);
	Text.setOutlineColor(sf::Color::Black);
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font" << endl;
	}
	Text.setFont(font);
}
gateButton::~gateButton() {}