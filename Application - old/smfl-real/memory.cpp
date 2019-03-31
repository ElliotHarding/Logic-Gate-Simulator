#include "memory.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//			read device												   //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
void readDevice::memoryPointerCalc() {
	if (!IncSignalSwitch) {
		if (incMemoryPointerAtacher->active) {
			memoryPointerPosition++;
			IncSignalSwitch = true;
		}
	}
	else if (incMemoryPointerAtacher->active == false) {
		IncSignalSwitch = false;
	}
};
void readDevice::resetPointerCalc() {
	if (resetPointer->active) {
		memoryPointerPosition = 0;
	}
}
void readDevice::checkOpen(sf::RenderWindow& window) {
	if (openButton.isClicked(window)) {
		open = true;
	}
	else {
		open = false;
	}
}


//memoryWindow:

void readDevice::drawBoxes() {
	button drawBox = button(sf::Color::Transparent, sf::Color(200, 200, 200, 255), sf::Color::Transparent, sf::Vector2f(0, 0), 20, 40, 1, true, "x", 0);

	for (int x = 0; x < 8; x++) {//float instead of int so no conversion warning when converting from int -> vector position
		for (int y = 0; y < 8; y++) {
			drawBox.position = sf::Vector2f(float(x) * 40 + 2, float(y) * 20 + 2);
			drawBox.draw(*memoryWindow);
			if (drawBox.isClicked(*memoryWindow)) {
				numToEdit = (y * 8) + x;
				str = "";
			}
		}
	}
}
void readDevice::checkButtonPresses() {
	if (quitButton.isClicked(*memoryWindow)) memoryWindow->close();;
}
void readDevice::events(size_t maxMemorySize) {
	sf::Event event;
	while (memoryWindow->pollEvent(event)) {

		if (event.type == sf::Event::Closed)
			memoryWindow->close();
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode < 128)
			{
				if (str.size() < maxMemorySize && static_cast<char>(event.text.unicode) == '1' || static_cast<char>(event.text.unicode) == '0') {
					str += static_cast<char>(event.text.unicode);
					textArray[numToEdit].setString(str);
				}
			}
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//				bool reader											   //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

boolReader::boolReader() {
	for (int x = 0; x < 64; x++) {
		memoryArray[x] = 0;
	}
	hb.widthX = width;
	hb.widthY = width;

	gateName = "Boolean-Reader: ";

	memoryWindow = new sf::RenderWindow(sf::VideoMode(unsigned int(windowWidth), unsigned int(windowHeight)), "Memory");
	memoryWindow->close();

	if (!textFont.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font --> arial.ttf" << endl;
	}

	for (int x = 0; x < 64; x++) {
		textArray[x].setCharacterSize(10);
		textArray[x].setStyle(sf::Text::Regular);
		textArray[x].setFillColor(sf::Color::Black);
		textArray[x].setOutlineColor(sf::Color::Black);
		textArray[x].setFont(textFont);
		textArray[x].setString("0");
	}	

	//set up reader:
	Attachers.push_back(new outputAttacher());

}
void boolReader::readerCalc() {
	if (memoryArray[memoryPointerPosition]) {
		Attachers[0]->active = true;
	}
	else {
		Attachers[0]->active = false;
	}
};
void boolReader::calc(sf::RenderWindow& window) {//public
	memoryPointerCalc();
	resetPointerCalc();
	readerCalc();
	checkOpen(window);
}  //does this get called?
void boolReader::drawItem(sf::RenderWindow& window) {
	shape.position = position;
	shape.draw(window);
	openButton.position = position + sf::Vector2f(width - openButtonWidth, height - openButtonHeight);
	openButton.draw(window);

	//check drag:
	checkRotation(window);
	drag(window);

	//rotate attacher
	sf::Transform transform;
	transform.rotate(rotationAmount, sf::Vector2f(position.x + hb.widthX / 2, position.y + hb.widthY / 2));

	//set attacher positions & draw
	Attachers[0]->position = position + sf::Vector2f(width + 2, 20);
	Attachers[0]->draw(window,transform);
	incMemoryPointerAtacher->position = position + sf::Vector2f(-7, 20);
	incMemoryPointerAtacher->draw(window,transform);
	resetPointer->position = position + sf::Vector2f(-7, 10);
	resetPointer->draw(window,transform);

	//text
}
void boolReader::draw(sf::RenderWindow& window) {//public
	if (open) {
		if (!memoryWindow->isOpen()) {
			memoryWindow = new sf::RenderWindow(sf::VideoMode(unsigned int(windowWidth), unsigned int(windowHeight)), "Memory");
		}
		drawItem(window);
		/*std::thread first(drawMemoryWindow(), this);
		sf::Thread f(&boolReader::drawMemoryWindow,this);
		f.launch();*/

		drawMemoryWindow();
	}
	else {
		drawItem(window);
	}
};
void boolReader::drawMemoryWindow() {
	while (memoryWindow->isOpen()) {
		memoryWindow->clear(sf::Color::White);

		events(1);
		drawBoxes();
		drawText();
		loadFromFileButton.draw(*memoryWindow);
		quitButton.draw(*memoryWindow);
		saveButton.draw(*memoryWindow);

		for (int x = 0; x < 64; x++) {
			//convert: 
			// sf::string -> std::string -> int -> bool
			string value = textArray[x].getString();
			memoryArray[x] = bool(atoi(value.c_str()));
		}

		if (saveButton.isClicked(*memoryWindow)) save();
		if (loadFromFileButton.isClicked(*memoryWindow)) {
			load();
			for (int x = 0; x < 64; x++) {
				textArray[x].setString(to_string(((int)memoryArray[x])));
			}
		}

		checkButtonPresses();
		memoryWindow->display();
	}
}
void boolReader::drawText() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			textArray[(int(y) * 8) + int(x)].setPosition(sf::Vector2f(float(x) * 40 + 21, float(y) * 20 + 7));
		}
	}
	for (int x = 0; x < 64; x++) {
		memoryWindow->draw(textArray[x]);
	}
}
void boolReader::save(){
	out_file.open("1bitReader.txt");
	for (int x = 1; x < 65; x++) {
		out_file << memoryArray[x-1] << " ";
		if (x % 8 == 0) {
			out_file << endl;
		}
	}
	out_file.close();
}
void boolReader::load() {
	string bit;

	in_file.open("1bitReader.txt");
	for (int x = 0; x < 64; x++) {
		in_file >> bit;
		memoryArray[x] = (bool)atoi(bit.c_str());
	}
	in_file.close();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//					4 bit Memory												//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
fourBitMemory::fourBitMemory() {

	//init memoryArray
	for (int x = 0; x < 64; x++) {
		memoryArray[x] = "0000";
	}

	//init 4 readers
	for (int x = 0; x < 4; x++) {
		Attachers.push_back(new outputAttacher());
	}

	hb.widthX = width;
	hb.widthY = width;

	gateName = "Four-Bit-Memory: ";

	memoryWindow = new sf::RenderWindow(sf::VideoMode(unsigned int(windowWidth), unsigned int(windowHeight)), "4-bit-Memory");
	memoryWindow->close();

	if (!textFont.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font" << endl;
	}

	for (int x = 0; x < 64; x++) {
		textArray[x].setCharacterSize(10);
		textArray[x].setStyle(sf::Text::Regular);
		textArray[x].setFillColor(sf::Color::Black);
		textArray[x].setOutlineColor(sf::Color::Black);
		textArray[x].setFont(textFont);
		textArray[x].setString("0000");
	}
}
void fourBitMemory::readersCalc() {
	

	if (memoryArray[memoryPointerPosition].length() == 4) {
		for (size_t x = 0; x < Attachers.size();x++) {

			if (memoryArray[memoryPointerPosition][x] == '1') {
				Attachers[x]->active = true;
			}
			else {
				Attachers[x]->active = false;
			}
		}
	}
	else {
		cout << "Length of four-bit memory array position " << memoryPointerPosition << " != 4 bits" << endl;

		const int len = memoryArray[memoryPointerPosition].length();
		for (int x = len; x < 4; x++) {
			memoryArray[memoryPointerPosition] += "0";;
		}
	}
	
}
void fourBitMemory::calc(sf::RenderWindow& window) {
	memoryPointerCalc();
	resetPointerCalc();
	readersCalc();
	checkOpen(window);
}
void fourBitMemory::drawItem(sf::RenderWindow& window) {
	//check rotation:
	checkRotation(window);
	sf::Transform transform;
	transform.rotate(rotationAmount, sf::Vector2f(position.x + hb.widthX / 2, position.y + hb.widthY / 2));

	//draw shape
	shape.position = position;
	shape.draw(window);
	openButton.position = position + sf::Vector2f(width - openButtonWidth, height - openButtonHeight);
	openButton.draw(window);

	//check drag
	drag(window);

	//set attacher positions & draw attachers:
	for (size_t x = 0; x < Attachers.size(); x++) {
		Attachers[x]->position = position + sf::Vector2f(width, 10 * float(x));
		Attachers[x]->draw(window,transform);
	}
	incMemoryPointerAtacher->position = position + sf::Vector2f(0, height / 2);
	incMemoryPointerAtacher->draw(window,transform);
	resetPointer->position = position + sf::Vector2f(0, height / 1.5f);
	resetPointer->draw(window,transform);
}
void fourBitMemory::draw(sf::RenderWindow& window) {
	if (open){
		if (!memoryWindow->isOpen()) {
			memoryWindow = new sf::RenderWindow(sf::VideoMode(unsigned int(windowWidth), unsigned int(windowHeight)), "4-Bit-Memory");
			//thread for draw memory window would go here
		}
		drawItem(window);
		drawMemoryWindow();
	}
	else {
		drawItem(window);
	}
}
void fourBitMemory::drawMemoryWindow() {
	while (memoryWindow->isOpen()) {
		memoryWindow->clear(sf::Color::White);

		events(4);
		drawBoxes();
		drawText();
		loadFromFileButton.draw(*memoryWindow);
		quitButton.draw(*memoryWindow);
		saveButton.draw(*memoryWindow);
		
		for (int x = 0; x < 64; x++) {
			//convert: 
			memoryArray[x] = textArray[x].getString();
		}

		if (saveButton.isClicked(*memoryWindow)) save();
		if (loadFromFileButton.isClicked(*memoryWindow)) {
			load();
			for (int x = 0; x < 64; x++) {
				textArray[x].setString(memoryArray[x]);
			}
		}

		checkButtonPresses();

		memoryWindow->display();
	}
}
void fourBitMemory::drawText() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			textArray[(y * 8) + x].setPosition(sf::Vector2f(float(x) * 40 + 17, float(y) * 20 + 7));
		}
	}
	for (int x = 0; x < 64; x++) {
		memoryWindow->draw(textArray[x]);
	}
}
void fourBitMemory::save() {
	out_file.open("4bitReader.txt");
	for (int x = 1; x < 65; x++) {
		out_file << memoryArray[x-1] << " ";
		if (x % 8 == 0) {
			out_file << endl;
		}
	}
	out_file.close();
}
void fourBitMemory::load() {
	char bit;
	std::string fourBits = "";

	in_file.open("4bitReader.txt");
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 4; y++) {
			in_file >> bit;
			fourBits += bit;
		}
		memoryArray[x] = fourBits;
		fourBits = "";
	}
	in_file.close();
}