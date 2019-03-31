#include "IOgates.h"

void IOgate::init() {
	
}

IOgate::IOgate() {
	hb.widthX = 20;
	hb.widthY = 20;
}

void IOgate::draw(sf::RenderWindow& window) {
	checkRotation(window);
	drag(window);
	dBox.position = position; //dBox position
	dBox.color = setColor; 	//dbox color
	dBox.draw(window);

	//draw attachers:
	for (size_t x = 0; x < Attachers.size(); x++) {
		Attachers[x]->position = position + AttacherPos[x]; //set position of attacher in realation to gate
		Attachers[x]->draw(window,sf::Transform());
	}
}


void inputGate::calc() {
	if (Attachers[0]->active) {
		setColor = sf::Color::Red;
	}
	else {
		setColor = sf::Color::Black;
	}
}

inputGate::inputGate() {
	//inputAttacher* attacher;
	AttacherPos.push_back(sf::Vector2f(0, 20));
	inputAttacher* newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);
	gateName = "Input-Gate: ";
}






void outputGate::calc(sf::RenderWindow& window) {
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouseDown = false;
	}

	if (!mouseDown) {
		if (isClicked(window)) {
			mouseDown = true;
			if (active) {
				setColor = sf::Color::Black;
				Attachers[0]->active = false;
				active = false;
			}
			else {
				setColor = sf::Color::Red;
				Attachers[0]->active = true;
				active = true;
			}
		}
	}
}

outputGate::outputGate() {
	//outputAttacher* attacher = new outputAttacher;
	AttacherPos.push_back(sf::Vector2f(20, 20));
	outputAttacher* newInputAttacher = new outputAttacher;
	Attachers.push_back(newInputAttacher);
	gateName = "Output-Gate: ";
}






void pulseEmitter::calc() {
	//check clock
	const sf::Time time = clock.getElapsedTime();

	if (time.asSeconds() > timeBetweenSwitch) {//if enough time has passed
		
		//restart clock
		clock.restart();

		//switch activeness and color
		if (active) {
			setColor = sf::Color::Black;
			Attachers[0]->active = false;
			active = false;
		}
		else {
			setColor = sf::Color::Red;
			Attachers[0]->active = true;
			active = true;
		}
	}
}

pulseEmitter::pulseEmitter() {
	AttacherPos.push_back(sf::Vector2f(20, 0));
	outputAttacher* newInputAttacher = new outputAttacher;
	Attachers.push_back(newInputAttacher);
	gateName = "Pulse-Emitter: ";
}