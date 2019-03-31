#pragma once
#include "identifiers.h"
#include "gameObjectFunctions.h"
class attacher : public clickable {
private:
	const float radius = 5;
	const sf::Color color = sf::Color::Black;

public:
	bool active = false;
	bool linked = false;

	virtual void draw(sf::RenderWindow& window, sf::Transform t);
	attacher();
	~attacher();
};
class inputAttacher : public attacher {
public:
	~inputAttacher();
};
class outputAttacher : public attacher {
public:
	~outputAttacher();
};