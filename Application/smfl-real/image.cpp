#include "image.h"

void image::loadTexture(std::string filelocation) {
	if (!texture.loadFromFile(filelocation))
	{
		cout << "Error! Failed to load: " << filelocation << ".... Ignoring" << endl;
	}
	sprite.setTexture(texture);
}