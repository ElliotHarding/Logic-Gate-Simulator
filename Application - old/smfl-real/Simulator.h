#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~includes:~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <SFML/Graphics.hpp>
#include "gate.h"
#include "link.h"
#include "box.h"
#include "allGateButtons.h"
#include "button.h"
#include "allGates.h"
#include "IOgates.h"
#include "starterScreen.h"
#include "memory.h"
#include "Instructions.h"
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;


class simulator {

private:
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~Time:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	sf::Clock simClock;
	float framePerSecond = 30;






	//~~~~~~~~~~~~~~~~~~~~~~~~~~Mouse clicks~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	bool leftMouseDown = false;
	bool rightMouseDown = false;



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~positions & sizes:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//sizes:
	const float pageButtonHeight = 20;
	const float pageButtonWidth = 50;
	const float sideBoxWidth = 90;
	const float sideBoxHeight = 400;
	const float topBarHeight = 100;
	const float sideBarAreaWidth = 110;
	float gameWidth = 700;
	float gameHeight = 700;
	const float gateFieldBoarder = 2;
	
	//positions
	const float buttonStartX = 15;
	const float buttonStartY = 600;
	const float sideBarBoxX = 10;
	const float sideBarBoxY = 30;
	const sf::Color backgroundColor = sf::Color::White;

	
	
	


	


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~gate buttons:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//std::vector<gateButton*> allGateButtons;
	notGateButton sideBarNGB = notGateButton(sf::Vector2f(40, 70));
	andGateButton sideBarAGB = andGateButton(sf::Vector2f(30, 160));
	orGateButton sideBarOGB = orGateButton(sf::Vector2f(30, 280));
	xOrGateButton sideBarXOGB = xOrGateButton(sf::Vector2f(30, 350));

	inputGateButton sideBarIGB = inputGateButton(sf::Vector2f(45, 70));
	outputGateButton sideBarOPGB = outputGateButton(sf::Vector2f(45, 170));
	pulseEmitterGateButton sideBarPEGB = pulseEmitterGateButton(sf::Vector2f(45, 270));
	splitterGateButton sideBarSGB = splitterGateButton(sf::Vector2f(20,370));

	fourBitMemoryGateButton sideBarFBMGB = fourBitMemoryGateButton(sf::Vector2f(30, 100));
	boolReaderGateButton sideBarBRGB = boolReaderGateButton(sf::Vector2f(30, 300));




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~pages:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int pageNumber = 1;
	int numberOfPages = 3;
	box pageButtonBox = box(pageButtonWidth, pageButtonHeight, 1, sf::Vector2f(110, gameHeight - 20), sf::Color(0, 0, 0, 0));
	button newPageButton = button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(gameWidth - 20, gameHeight - 20), 20, 20, 0, false, "+", 10);



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~link config:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	int linkStage = 3; 
	//link stage 0 --> search for new source attacher
	//link stage 1 --> search for new end attacher
	//link stage 2 --> toggle linking off



	


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~gate button, option buttons:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	button leftButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(20, 15), 30, 30, 2, true, "<-",15);
	button rightButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(60, 15), 30, 30, 2, true, "->",15);
	int sideBarMode = 0;
	// 0 --> all normal gates
	// 1 --> all memory
	// 2 --> input/output gates



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~vectors:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::vector<gate*> allGates;
	std::vector<link> allLinks;
	std::vector<box> guiBoxes;
	std::vector<button*> mainButtons; // <-- vector in which all page buttons are stored
	std::vector<button*> pageButtons; // <-- vector in which all page buttons are stored





	//~~~~~~~~~~~~~~~~~~~~~~~~~~~functions:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	void loop();
	void init(starterScreen& screen);
	void events(sf::RenderWindow& window, sf::View& view);

	//buttons/creation/pages stuff
	void createGate(gate* newGate);
	void gateButtons(sf::RenderWindow& window);
	void buttons(sf::RenderWindow& window);
	void newPage(sf::RenderWindow& window);
	void GUI(sf::RenderWindow& window);

	//gates stuff
	void drawGates(sf::RenderWindow& window);
	void calcGates(sf::RenderWindow& window);
	void checkDeleteGates(int x);

	//Link stuff
	void links(sf::RenderWindow& window);
	void createLink(sf::RenderWindow& window);
	void checkForClickedAttacher(attacher*& attacher, sf::RenderWindow& window);
	
	//loading/saving stuff:
	void load();
	void save();
	int askIfWantToSave();
public:
	void start();
	simulator() {};
};