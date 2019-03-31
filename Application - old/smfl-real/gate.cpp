#include "gate.h"

void gate::draw(sf::RenderWindow& window) {
	//change sprite pos if nesseary
	drag(window);
	sprite.setPosition(position);

	//rotate and draw sprite:
	checkRotation(window);
	sf::Transform transform;
	transform.rotate(rotationAmount, sf::Vector2f(position.x + hb.widthX / 2, position.y + hb.widthY / 2));
	window.draw(sprite,transform); //draw sprite

	//rotate & draw attachers:
	for (size_t x = 0; x < Attachers.size(); x++) {
		Attachers[x]->position = position + AttacherPos[x]; //set position of attacher in realation to gate

		if (Attachers[x]) {
			Attachers[x]->draw(window,transform);
		}
	}
}

void gate::calc() {} //overrided function

void gate::save(ofstream& out_file)
{
	out_file << gateName << position.x << "," << position.y << " " << to_string(pageNumber) << endl;
}

bool gate::checkDelete(sf::RenderWindow& window) {
	if (isHover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		return true;
	}
	return false;
}

sf::Vector2f gate::rotateAttachers(sf::Vector2f initialPosition, sf::Vector2f originPos, float rotationAmmount) {
	float s = sin(2 * 3.14f * (rotationAmmount / 360));
	float c = cos(2 * 3.14f * (rotationAmmount / 360));

	initialPosition -= originPos;

	float xNew = initialPosition.x * c - initialPosition.y * s + originPos.x;
	float yNew = initialPosition.x * s - initialPosition.y * c + originPos.y;

	//return sf::Vector2f(xNew, yNew);
	return initialPosition;
}

void gate::init() {

	//set image and scale
	if (filelocation != "") {
		loadTexture(filelocation);
		sprite.setScale(scale);
	}
}

gate::gate(int pageNumber_) {
	pageNumber = pageNumber_;
}
gate::gate() {

}

gate::~gate() {
	for (size_t x = 0; x < Attachers.size(); x++) {
		delete Attachers[x];
	}
}