#pragma once
#include <SFML/Graphics.hpp>
#include "gate.h"
#include "box.h"

class IOgate : public gate {
private:
	box dBox = box(20, 20, 2);

public:
	IOgate();
	sf::Color setColor = sf::Color::Black;
	void init();//overriding void
	void draw(sf::RenderWindow& window);//overiding void
};

//displays color
class inputGate : public IOgate {
private:
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

	void calc();
	inputGate();
};

//inputs 0 or 1
class outputGate : public IOgate {
private:
	bool active = false;
	bool mouseDown = false;

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
	outputGate();
};

class pulseEmitter : public IOgate {
private:
	bool active = false;
	sf::Clock clock;

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
	float timeBetweenSwitch = 1;
	void calc();
	pulseEmitter();
};