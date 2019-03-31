#pragma once
#include <SFML/Graphics.hpp>
#include "gateButton.h"
#include "box.h"
#include "gate.h"
#include "allGates.h"
#include "memory.h"
#include "IOgates.h"

class andGateButton : public gateButton {
private:
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	andGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new andGate;
	~andGateButton();
};
class orGateButton : public gateButton {
private:
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	orGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new orGate;
	~orGateButton();
};
class notGateButton : public gateButton {
private:
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	notGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new notGate;
	~notGateButton();
};
class xOrGateButton : public gateButton {
private:
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	xOrGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new xOrGate;
	~xOrGateButton();
};
class splitterGateButton : public gateButton{
private:
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	splitterGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new splitterGate;
	~splitterGateButton();
};


class inputGateButton : public gateButton {

private:
	const float dimension = 20;
	box shape = box(dimension, dimension, 2);
	sf::CircleShape circle;
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	void draw(sf::RenderWindow& window); //Overriding void
	inputGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new inputGate;
	~inputGateButton();
};

class outputGateButton : public gateButton {
private:
	const float dimension = 20;
	box shape = box(dimension, dimension, 2);
	sf::CircleShape circle;
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	outputGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new outputGate;
	~outputGateButton();
	void draw(sf::RenderWindow& window);//Overriding void
};


class pulseEmitterGateButton : public gateButton {
private:
	const float dimension = 20;
	box shape1 = box(dimension / 2, dimension, 2);
	box shape2 = box(dimension / 2, dimension, 2);
	sf::CircleShape circle;
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	pulseEmitterGateButton(sf::Vector2f position_);
	~pulseEmitterGateButton();
	gate* gateToSpawn = new pulseEmitter;
	void draw(sf::RenderWindow& window);//Overriding void
};



class fourBitMemoryGateButton :public gateButton {
private:
	const float dimensionX = 20;
	const float dimensionY = 40;
	box shape = box(dimensionX, dimensionY, 2);
	std::vector<sf::CircleShape> circles;
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	fourBitMemoryGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new fourBitMemory;
	void draw(sf::RenderWindow& window);//overriding void
};

class boolReaderGateButton :public gateButton {
private:
	const float dimensionX = 20;
	const float dimensionY = 40;
	box shape = box(dimensionX, dimensionY, 2);
	sf::CircleShape circle;
	using::gateButton::description;
	using::gateButton::descriptionBox;
	using::gateButton::drawDescription;
	using::gateButton::initDesciptionBox;

public:
	boolReaderGateButton(sf::Vector2f position_);
	gate* gateToSpawn = new boolReader;
	void draw(sf::RenderWindow& window);//overriding void
};