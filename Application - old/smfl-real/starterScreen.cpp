#include <SFML/Graphics.hpp>
#include "starterScreen.h"

void starterScreen::closeEvent() {
	sf::Event event;
	while (SSwindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			quit = true;
			SSwindow->close();
		}
	}
}
void starterScreen::gui() {
	goButton.draw(*SSwindow);
	if (goButton.isClicked(*SSwindow)) {
		SSwindow->close();
	}
	plusWidth.draw(*SSwindow);
	if (plusWidth.isClicked(*SSwindow)) {
		gameWidth += 10;
		sf::sleep(sf::milliseconds(100));
	}
	minusWidth.draw(*SSwindow);
	if (minusWidth.isClicked(*SSwindow)) {
		if (gameWidth>400) { // width must be > 400
			gameWidth -= 10;
			sf::sleep(sf::milliseconds(100));
		}

	}
	plusHeight.draw(*SSwindow);
	if (plusHeight.isClicked(*SSwindow)) {
		gameHeight += 10;
		sf::sleep(sf::milliseconds(100));
	}
	minusHeight.draw(*SSwindow);
	if (minusHeight.isClicked(*SSwindow)) {
		if (gameHeight>700) { // Height must be > 700
			gameHeight -= 10;
			sf::sleep(sf::milliseconds(100));
		}
	}

	gameWidthText.setString("Sim Width: " + std::to_string((int)gameWidth));
	gameHeightText.setString("Sim Height: " + std::to_string((int)gameHeight));
	SSwindow->draw(gameWidthText);
	SSwindow->draw(gameHeightText);
}

void starterScreen::windowLoop() {
	while (SSwindow->isOpen()) {
		SSwindow->clear(sf::Color(255, 255, 255, 255));

		closeEvent();
		gui();

		SSwindow->display();
	}
}
void starterScreen::start() {
	windowLoop();
}

bool starterScreen::checkQuit() {
	return quit;
}

float starterScreen::getHeight() {
	return gameHeight;
}
float starterScreen::getWidth() {
	return gameWidth;
}


starterScreen::starterScreen() {
	SSwindow = new sf::RenderWindow(sf::VideoMode(starterScreenWidth, starterScreenHeight), "Logic Gate Simulator");

	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font" << endl;
	}

	gameHeightText.setFont(font);
	gameHeightText.setFillColor(sf::Color::Black);
	gameHeightText.setOutlineColor(sf::Color::Black);
	gameWidthText.setPosition(25, 25);

	gameWidthText.setFont(font);
	gameWidthText.setFillColor(sf::Color::Black);
	gameWidthText.setOutlineColor(sf::Color::Black);
	gameHeightText.setPosition(25, 150);
}
starterScreen::~starterScreen() {
	delete SSwindow;
}