#include "allGates.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//										And-Gate																	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void andGate::calc() {
	if (Attachers[0]->active && Attachers[1]->active) {
		Attachers[2]->active = true;
	}
	else {
		Attachers[2]->active = false;
	}
}

andGate::~andGate() {
	
}
andGate::andGate() {
	gateName = "And-Gate: ";
	filelocation = "gate-and.png";
	scale = sf::Vector2f(0.1f, 0.1f);

	//hitbox setup
	hb.widthX = 40;
	hb.widthY = 40;

	//setup attachers
	inputAttacher* newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 0
	newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 1

	outputAttacher* newOutputAttacher = new outputAttacher;
	Attachers.push_back(newOutputAttacher);//output

	//set attacher positions in relation to gate
	AttacherPos.push_back(sf::Vector2f(-5, 21));
	AttacherPos.push_back(sf::Vector2f(-5, 5));
	AttacherPos.push_back(sf::Vector2f(55, 12));
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//										not-Gate																	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void notGate::calc() {
	if (Attachers[0]->active) {
		Attachers[1]->active = false;
	}
	else {
		Attachers[1]->active = true;
	}
}

notGate::~notGate() {
	
}
notGate::notGate() {
	gateName = "Not-Gate: ";
	filelocation = "gate-not.png";
	scale = sf::Vector2f(0.13f, 0.13f);

	//hitbox setup
	hb.widthX = 20;
	hb.widthY = 30;

	//setup attachers
	inputAttacher* newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 0

	outputAttacher* newOutputAttacher = new outputAttacher;
	Attachers.push_back(newOutputAttacher);//output 0

										   //set attacher positions in relation to gate
	AttacherPos.push_back(sf::Vector2f(-7, 6));
	AttacherPos.push_back(sf::Vector2f(35, 6));

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//										Or-Gate																	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void orGate::calc() {

	if (Attachers[0]->active || Attachers[1]->active) {
		Attachers[2]->active = true;
	}
	else {
		Attachers[2]->active = false;
	}
}

orGate::~orGate() {
	
}
orGate::orGate() {
	gateName = "Or-Gate: ";
	filelocation = "gate-or.png";
	scale = sf::Vector2f(0.1f, 0.1f);

	//hitbox setup
	hb.widthX = 40;
	hb.widthY = 40;

	//setup attachers
	inputAttacher* newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 0
	newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 1

	outputAttacher* newOutputAttacher = new outputAttacher;
	Attachers.push_back(newOutputAttacher);//output

										   //set attacher positions in relation to gate
	AttacherPos.push_back(sf::Vector2f(-5, 19));
	AttacherPos.push_back(sf::Vector2f(-5, 3));
	AttacherPos.push_back(sf::Vector2f(55, 11));

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//										X-Or-Gate																	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void xOrGate::calc() {
	if ((Attachers[0]->active || Attachers[1]->active) && !(Attachers[0]->active && Attachers[1]->active)) {
		Attachers[2]->active = true;
	}
	else {
		Attachers[2]->active = false;
	}
}


xOrGate::~xOrGate() {
	
}
xOrGate::xOrGate() {
	gateName = "Xor-Gate: ";
	filelocation = "gate-xOr.png";
	scale = sf::Vector2f(0.1f, 0.15f);

	//hitbox setup
	hb.widthX = 40;
	hb.widthY = 30;

	//setup attachers
	inputAttacher* newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 0
	newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 1

	outputAttacher* newOutputAttacher = new outputAttacher;
	Attachers.push_back(newOutputAttacher);//output

										   //set attacher positions in relation to gate
	AttacherPos.push_back(sf::Vector2f(-5, 19));
	AttacherPos.push_back(sf::Vector2f(-5, 3));
	AttacherPos.push_back(sf::Vector2f(55, 11));

}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//										Splitter-Gate																	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void splitterGate::calc() {
	if (Attachers[0]->active) {
		Attachers[1]->active = true;
		Attachers[2]->active = true;
	}
	else {
		Attachers[1]->active = false;
		Attachers[2]->active = false;
	}
}
splitterGate::splitterGate() {
	gateName = "Splitter-Gate: ";
	filelocation = "Splitter-gate.png";
	scale = sf::Vector2f(0.12f, 0.12f);

	//hitbox setups
	hb.widthX = 65;
	hb.widthY = 40;

	//setup attachers
	inputAttacher* newInputAttacher = new inputAttacher;
	Attachers.push_back(newInputAttacher);//input 0

	outputAttacher* newOutputAttacher = new outputAttacher;
	Attachers.push_back(newOutputAttacher);//output 1 
	outputAttacher* newOutputAttacher1 = new outputAttacher;
	Attachers.push_back(newOutputAttacher1);//output 2

										   //set attacher positions in relation to gate
	AttacherPos.push_back(sf::Vector2f(-5, 16));
	AttacherPos.push_back(sf::Vector2f(60, 8));
	AttacherPos.push_back(sf::Vector2f(60, 28));
}
splitterGate::~splitterGate() {

}