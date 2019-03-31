#include "link.h"

void link::draw(sf::RenderWindow& window) {

	if (oa->active) {
		line[0] = sf::Vertex(oa->position + posOffset, sf::Color::Red);
		line[1] = sf::Vertex(ia->position + posOffset, sf::Color::Red);
	}
	else {
		line[0] = sf::Vertex(oa->position + posOffset, sf::Color::Black);
		line[1] = sf::Vertex(ia->position + posOffset, sf::Color::Black);
	}

	window.draw(line, 2, sf::Lines);
}

link::link() {
	oa = new outputAttacher();
	ia = new inputAttacher();
	posOffset = sf::Vector2f(oa->hb.widthX / 2, oa->hb.widthY / 2);
}

void link::calc() {
	if (oa->active) {
		ia->active = true;
	}
	else {
		ia->active = false;
	}
}

link::~link() {
	/*delete ia;
	delete oa;*/
}