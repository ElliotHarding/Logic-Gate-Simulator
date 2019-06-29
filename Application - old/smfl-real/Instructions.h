#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include <fstream>
#include <iostream>
using namespace std;

class instructionWindow {
private:
	//instruction pages:
	static const int linesPerPage = 15;
	static const int lineLength = 350;
	int currentPageNumber = 1;
	std::string instructionsPage1[linesPerPage];
	std::string instructionsPage2[linesPerPage];
	std::string instructionsPage3[linesPerPage];
	ifstream in_file;

	//text stuff:
	sf::Font font;
	sf::Text text;

	//dimensions, positions & sizes:
	const float boarderX = 20;
	const float boarderY = 20;
	const float buttonsHeight = 30;
	const float windowX = lineLength + boarderX * 2;
	const float windowY = linesPerPage * 10 + boarderY * 2 + buttonsHeight + 2;
	const float buttonsWidth = windowX/2;

	//buttons:
	button previousPage = button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129),sf::Vector2f(0,windowY - buttonsHeight ),buttonsHeight,buttonsWidth,1,true,"<--");
	button nextPage = button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(windowX/2 + 2, windowY - buttonsHeight), buttonsHeight, buttonsWidth, 1, true, "         -->");

	//window:
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(unsigned int(windowX), unsigned int(windowY)),"Instructions", sf::Style::Titlebar | sf::Style::Close);

	void drawText();
	void loop();
public:
	void start();
	instructionWindow();
};