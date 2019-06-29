#include "allGateButtons.h"


andGateButton::andGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = 40;
	hb.widthY = 40;

	description.push_back("And Gate");
	description.push_back("0 + 0 --> 0");
	description.push_back("0 + 1 --> 0");
	description.push_back("1 + 1 --> 1");
	description.push_back("1 + 0 --> 0");
	
	init("gate-and.png", sf::Vector2f(0.1f, 0.1f));
}
andGateButton::~andGateButton() {}

orGateButton::orGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = 40;
	hb.widthY = 40;

	description.push_back("Or Gate");
	description.push_back("0 + 0 --> 0");
	description.push_back("0 + 1 --> 1");
	description.push_back("1 + 1 --> 1");
	description.push_back("1 + 0 --> 1");

	init("gate-or.png", sf::Vector2f(0.1f, 0.1f));
}
orGateButton::~orGateButton() {}

notGateButton::notGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = 20;
	hb.widthY = 20;

	description.push_back("Not Gate");
	description.push_back("0 --> 1");
	description.push_back("1 --> 0");
	
	init("gate-not.png", sf::Vector2f(0.13f, 0.13f));
}
notGateButton::~notGateButton() {}

xOrGateButton::xOrGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = 40;
	hb.widthY = 40;

	description.push_back("X-Or Gate");
	description.push_back("0 + 0 --> 0");
	description.push_back("0 + 1 --> 1");
	description.push_back("1 + 1 --> 0");
	description.push_back("1 + 0 --> 1");

	init("gate-xOr.png", sf::Vector2f(0.1f, 0.15f));
}
xOrGateButton::~xOrGateButton() {}

splitterGateButton::splitterGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = 65;
	hb.widthY = 40;

	description.push_back("Splitter Gate");
	description.push_back("Duplicates input signal");

	init("Splitter-gate.png", sf::Vector2f(0.12f, 0.12f));
}
splitterGateButton::~splitterGateButton() {}

inputGateButton::inputGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = dimension;
	hb.widthY = dimension;
	shape = box(dimension, dimension, 2, position);
	shape.color = sf::Color::Red;
	circle.setFillColor(sf::Color::Black);
	circle.setRadius(5);
	circle.setPosition(position.x - 1, position.y);

	description.push_back("Input Gate");
	description.push_back("Displays input color");
	initDesciptionBox();
	
}

void inputGateButton::draw(sf::RenderWindow& window) {
	shape.draw(window);
	window.draw(circle);
	drawDescription(window);
}

inputGateButton::~inputGateButton() {}

outputGateButton::outputGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = dimension;
	hb.widthY = dimension;
	shape = box(dimension, dimension, 2, position);
	shape.color = sf::Color::Red;
	circle.setFillColor(sf::Color::Black);
	circle.setRadius(5);
	circle.setPosition(position.x + dimension, position.y);

	description.push_back("Output Gate");
	description.push_back("Emmits signal 1/0");
	initDesciptionBox();
}


void outputGateButton::draw(sf::RenderWindow& window) {
	shape.draw(window);
	window.draw(circle);
	drawDescription(window);
}

outputGateButton::~outputGateButton() {}


pulseEmitterGateButton::pulseEmitterGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = dimension;
	hb.widthY = dimension;
	shape1 = box(dimension / 2, dimension, 2, position);
	shape2 = box(dimension / 2, dimension, 2, position + sf::Vector2f(dimension/2,0));

	shape1.color = sf::Color::Red;
	shape2.color = sf::Color::Black;
	circle.setFillColor(sf::Color::Black);
	circle.setRadius(5);

	circle.setPosition(position.x + dimension, position.y);

	description.push_back("Pulse Gate");
	description.push_back("Switches signal every x seconds");
	initDesciptionBox();
}

void pulseEmitterGateButton::draw(sf::RenderWindow& window) {
	shape1.draw(window);
	shape2.draw(window);
	window.draw(circle);
	drawDescription(window);
}

pulseEmitterGateButton::~pulseEmitterGateButton(){}


fourBitMemoryGateButton::fourBitMemoryGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = dimensionX;
	hb.widthY = dimensionY;
	shape = box(dimensionX, dimensionY, 2, position);
	shape.color = sf::Color::Transparent;
	for (int x = 0; x < 4; x++) {
		sf::CircleShape newCircle;
		newCircle.setFillColor(sf::Color::Black);
		newCircle.setRadius(5);
		circles.push_back(newCircle);
	}
	description.push_back("4 bit memory Gate");
	description.push_back("Emmits 4 different signals from attachers");
	initDesciptionBox();
}

void fourBitMemoryGateButton::draw(sf::RenderWindow& window) {
	shape.draw(window);
	for (size_t x = 0; x < circles.size();x++) {
		circles[x].setPosition(position.x + dimensionX, position.y + x * 10);
		window.draw(circles[x]);
	}
	drawDescription(window);
}

boolReaderGateButton::boolReaderGateButton(sf::Vector2f position_) {
	position = position_;
	hb.widthX = dimensionX;
	hb.widthY = dimensionY;
	shape = box(dimensionX, dimensionY, 2, position);
	shape.color = sf::Color::Transparent;
	circle.setFillColor(sf::Color::Black);
	circle.setRadius(5);
	description.push_back("1 bit memory Gate");
	description.push_back("Emmits signals from attacher");
	initDesciptionBox();
}

void boolReaderGateButton::draw(sf::RenderWindow& window) {
	shape.draw(window);
	circle.setPosition(position.x + dimensionX, position.y);
	window.draw(circle);
	drawDescription(window);
}
