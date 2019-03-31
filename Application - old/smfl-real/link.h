#pragma once
#include "attachers.h"
#include <SFML/Graphics.hpp>

class link {
private:
	sf::Vertex line[2];
	sf::Vector2f posOffset;

public:
	outputAttacher* oa;
	inputAttacher* ia;

	int pageNumber;

	void draw(sf::RenderWindow& window);
	void calc();
	link();
	~link();
};