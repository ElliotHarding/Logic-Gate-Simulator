#pragma once
#include "box.h"
#include "attachers.h"
#include <string>
#include "gate.h"
#include "button.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <fstream>
using namespace std;

class readDevice : public gate {
public:
	//dimensions & properties
	const float width = 40;
	const float height = 55;
	const float openButtonWidth = 15;
	const float openButtonHeight = 15;

	//button stuff:
	bool open = false;
	button openButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(0, 0), openButtonWidth, openButtonHeight, 2, true, "");

	//other
	box shape = box(width, height, 2);
	int memoryPointerPosition = 0;
	bool IncSignalSwitch = false;

	//functions
	readDevice() {};
	void memoryPointerCalc();
	void resetPointerCalc();
	void checkOpen(sf::RenderWindow& window);
	virtual void calc(sf::RenderWindow& window){}//overriden function used when inherited, but not used by readDevice

	//attachers
	inputAttacher* incMemoryPointerAtacher = new inputAttacher();
	inputAttacher* resetPointer = new inputAttacher();


	//___________________ Other window ___________________:

	//dimensions
	float windowWidth = 325;
	float windowHeight = 250;

	//other
	sf::RenderWindow* memoryWindow;
	int numToEdit = -1;

	//buttons:
	button saveButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129),
		sf::Vector2f(120, 200), 40, 80, 2, true, "Save");
	button quitButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129),
		sf::Vector2f(20, 200), 40, 80, 2, true, "Quit");
	button loadFromFileButton = button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129),
		sf::Vector2f(220, 200), 40, 80, 2, true, "Load");

	//text stuff:
	sf::Font textFont;
	sf::Text textToEdit;
	sf::Text textArray[64];
	string str;

	//functions
	void checkButtonPresses();
	void drawBoxes();
	void events(size_t maxMemorySize);
};

class boolReader: public readDevice {
private:
	//memory stuff
	bool memoryArray[64];

	//save & loading
	ofstream out_file;
	ifstream in_file;

	//private functions
	void readerCalc();
	void drawMemoryWindow();
	void drawItem(sf::RenderWindow& window);
	void drawText();
	void save();
	void load();

	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;

public:
	using::readDevice::incMemoryPointerAtacher;
	using::readDevice::resetPointer;
	void calc(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	boolReader();
};

class fourBitMemory: public readDevice {
private:
	//4 bit memory array
	string memoryArray[64];

	//private functions
	void drawMemoryWindow();
	void readersCalc();
	void drawItem(sf::RenderWindow& window);
	void drawText();
	void save();
	void load();

	//save & loading
	ofstream out_file;
	ifstream in_file;

	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;

public:
	void calc(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	fourBitMemory();
	using::readDevice::incMemoryPointerAtacher;
	using::readDevice::resetPointer;
};