#include "Instructions.h"

void instructionWindow::drawText()
{

	switch (currentPageNumber)
	{
	case 1: 
		for (int x = 0; x < linesPerPage; x++) {
			text.setPosition(sf::Vector2f(boarderX, (float)(x+1) * 10 /*+ boarderY*/));
			text.setString(instructionsPage1[x]);
			window->draw(text);
		}
		break;
	case 2:
		for (int x = 0; x < linesPerPage; x++) {
			text.setPosition(sf::Vector2f(boarderX, (float)(x+1) * 10 /*+ boarderY*/));
			text.setString(instructionsPage2[x]);
			window->draw(text);
		}
		break;
	case 3:
		for (int x = 0; x < linesPerPage; x++) {
			text.setPosition(sf::Vector2f(boarderX, (float)(x+1) * 10 /*+ boarderY*/));
			text.setString(instructionsPage3[x]);
			window->draw(text);
		}
		break;
	}
}

void instructionWindow::loop()
{
	while (window->isOpen()) {

		//check for close event
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		//clear screen
		window->clear(sf::Color::White);

		//draw text
		drawText();

		//draw & use buttons
		nextPage.draw(*window);
		previousPage.draw(*window);
		if (nextPage.isClicked(*window)) {
			if (currentPageNumber < 3) {
				currentPageNumber++;
			}
			else {
				currentPageNumber = 1;
			}
			sf::sleep(sf::milliseconds(100));
		}
		else if (previousPage.isClicked(*window)) {
			if (currentPageNumber > 1) {
				currentPageNumber--;
			}
			sf::sleep(sf::milliseconds(100));
		}

		//render
		window->display();
	}
	
}

void instructionWindow::start()
{
	loop();
}

instructionWindow::instructionWindow()
{
	string line;
	int counter = 0;

	in_file.open("instructions.txt");

	while (std::getline(in_file, line)) {
		
		if (line == "---------------") { //'---' shows new page in txt document
			break;
		}
		instructionsPage1[counter] = line;
		counter++;
	}

	counter = 0;

	while (std::getline(in_file, line)) {
		if (line == "---------------") { //'---' shows new page in txt document
			break;
		}
		instructionsPage2[counter] = line;
		counter++;
	}

	counter = 0;

	while (std::getline(in_file, line)) {
		if (line == "---------------") {//'---' shows new page in txt document
			break;
		}
		instructionsPage3[counter] = line;
		counter++;
	}

	in_file.close();

	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font" << endl;
	}

	text.setStyle(sf::Text::Regular);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(12);
	text.setFont(font);
}

