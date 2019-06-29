#pragma once
#include "location.h"
#include "image.h"
#include "gameObjectFunctions.h"
#include "attachers.h"
#include "identifiers.h"
#include <fstream>

class gate : public image, public rotation /*, public gateName*/ {
private:
	sf::Vector2f rotateAttachers(sf::Vector2f initialPosition, sf::Vector2f originPos , float rotationAmmount);
	using::clickable::isHover;
	ofstream out_file;
public:
	std::string filelocation;
	sf::Vector2f scale;

	string gateName; //string used when gate is save to file to determine the gate type when loaded

	int pageNumber;

	std::vector<attacher*> Attachers; //all attachers
	std::vector<sf::Vector2f> AttacherPos; //attacher positions in relation to gate

	virtual void draw(sf::RenderWindow& window);
	virtual void init();
	virtual bool checkDelete(sf::RenderWindow& window);
	virtual void calc();
	void save(ofstream& out_file);
	gate();
	gate(int pageNumber_);
	virtual ~gate();
};