#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class image {
public:
	sf::Texture texture;
	sf::Sprite sprite;

	void loadTexture(std::string filelocation);
};