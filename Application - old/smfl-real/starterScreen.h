#pragma once
#include "button.h"
#include "box.h"
#include <string>     // std::string, std::to_string
#include <iostream>
using namespace std;
class starterScreen {
private:
	sf::RenderWindow* SSwindow;

	bool quit = false;

	const int starterScreenWidth = 350;
	const int starterScreenHeight = 300;

	float gameWidth = 700;
	float gameHeight = 700;

	sf::Text gameWidthText;
	sf::Text gameHeightText;
	sf::Font font;

	button goButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(250, 250), 40, 80, 2, true, "Start",17);
	button plusWidth = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(75, 80), 30, 30, 2, true, "+");
	button minusWidth = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(25, 80), 30, 30, 2, true, "-");
	button plusHeight = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(75, 200), 30, 30, 2, true, "+");
	button minusHeight = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(25, 200), 30, 30, 2, true, "-");

	void closeEvent();
	void gui();
	void windowLoop();
	
public:

	void start();
	float getHeight();
	float getWidth();
	bool checkQuit();
	starterScreen();
	~starterScreen();
};