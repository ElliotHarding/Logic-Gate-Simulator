#include "Simulator.h"

//main loop for simulator
void simulator::loop() {

	//open stater screen
	starterScreen screen;
	screen.start();

	if (!screen.checkQuit()) {

		//initialize properties
		init(screen);
		sf::RenderWindow window(sf::VideoMode(unsigned int(gameWidth), unsigned int(gameHeight)), "Logic Gate Simulator", sf::Style::Titlebar | sf::Style::Close);
		sf::View gateFieldView(sf::Vector2f(gameWidth / 2, gameHeight / 2), sf::Vector2f(gameWidth, gameHeight));
		sf::View GUIview(sf::Vector2f(gameWidth / 2, gameHeight / 2), sf::Vector2f(gameWidth, gameHeight));
		window.setView(gateFieldView);


		//gameloop
		while (window.isOpen()) {
			window.clear(backgroundColor);

			//check for events
			events(window, gateFieldView);
			
			//draw gui
			window.setView(GUIview);
			GUI(window);

			//check if new link needs creating
			createLink(window);
			
			//draw & calc gates & links
			window.setView(gateFieldView);
			calcGates(window);
			drawGates(window);

			window.display();
		}
	}
}

//starts the simulator
void simulator::start() {

	// the reason this has it's own function is because i was going to use threadding within this function to call loop();
	loop();
}

//used to initalize the simulators properties
void simulator::init(starterScreen& screen) {

	//when allLinks.push_back is called the last items pointers become invallidated
	//threfore allLinks.reserve must be used
	allLinks.reserve(255);


	//get & set screen simeensions
	gameWidth = screen.getWidth();
	gameHeight = screen.getHeight();


	const float gateFieldWidth = gameWidth - sideBarAreaWidth - gateFieldBoarder * 2;
	const float gateFieldHeight = gameHeight - pageButtonHeight - gateFieldBoarder * 2;
	const float gateFieldX = sideBarAreaWidth + gateFieldBoarder;
	const float gateFieldY = gateFieldBoarder;


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~GUI boxes:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	guiBoxes.push_back(box(sideBarAreaWidth, gameHeight, 0, sf::Vector2f(0, 0), sf::Color(200, 200, 200)));
	guiBoxes.push_back(box(sideBoxWidth, sideBoxHeight, 2, sf::Vector2f(sideBarBoxX, sideBarBoxY), sf::Color::Transparent));
	guiBoxes.push_back(box(gateFieldWidth, gateFieldHeight, 2, sf::Vector2f(gateFieldX, gateFieldY), sf::Color::Transparent));


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~buttons:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	mainButtons.push_back(new button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(buttonStartX, buttonStartY), 40, 80, 2, true, "Quit", 17));
	mainButtons.push_back(new button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(buttonStartX, buttonStartY - 50), 40, 80, 2, true, "Save", 17));
	mainButtons.push_back(new button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(buttonStartX, buttonStartY - 100), 40, 80, 2, true, "Load", 17));
	mainButtons.push_back(new button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(buttonStartX, buttonStartY - 150), 40, 80, 2, true, "Link", 17));
	mainButtons.push_back(new button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(buttonStartX, buttonStartY + 50), 40, 80, 2, true, "New", 17));
	mainButtons.push_back(new button(sf::Color(250, 250, 250), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(sideBarAreaWidth + 2, 2), 25, 60, 1, true, "Help", 15));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~pages:~~~~~~~~~~~~~~~~~~~~~~~~~~~
	pageButtons.push_back(new button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(110, gameHeight - 20), pageButtonHeight, pageButtonWidth, 0, false, "Page 1", 10));
	pageButtons.push_back(new button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(160, gameHeight - 20), pageButtonHeight, pageButtonWidth, 0, false, "Page 2", 10));
	pageButtons.push_back(new button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(210, gameHeight - 20), pageButtonHeight, pageButtonWidth, 0, false, "Page 3", 10));
}

//handles events which within simulator.cpp game loop
void simulator::events(sf::RenderWindow& window, sf::View& view) {


	//check if left/right mouse button is released
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		leftMouseDown = false;
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		rightMouseDown = false;
	}


	sf::Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {

			// check if user whishes to save before quitting
			int result = askIfWantToSave();

			switch (result)
			{
			case 0:
				save();
				cout << "saved" << endl;
				window.close();
				break;
			case 1:
				window.close();
			case 2:
				break;
			}
		}
			
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code)
			{
			case sf::Keyboard::Z:

				// change gate field view to zoom in, not gui view
				if (view.getSize().x > gameWidth) {
					view.zoom(0.9f);
					window.setView(view);
				}
				break;
			case sf::Keyboard::X:

				//change gate field view to zoom out, not gui view
				view.zoom(1.1f);
				window.setView(view);
				break;
			default:
				break;
			}
		}
	}
}




//===============================================================================
//				buttons/creation/pages stuff
//===============================================================================


// assigns pageNumber, sprite, position to newly created gate
void simulator::createGate(gate* newGate) {
	leftMouseDown = true;

	newGate->pageNumber = pageNumber;

	newGate->init(); //initalize gate sprite, needed to do later instead of in the gate constructor

	newGate->position = sf::Vector2f(gameWidth / 2, gameHeight / 2);
	allGates.push_back(newGate);
}

//draw all of the sidebar gate buttons (buttons which spawn new gates into the gate field)
void simulator::gateButtons(sf::RenderWindow& window) {

	leftButton.draw(window);
	rightButton.draw(window);

	//configure sideBar page number
	
	if (!leftMouseDown) {
		if (leftButton.isClicked(window)) {
			sideBarMode--;
			leftMouseDown = true;
		}
		if (rightButton.isClicked(window)) {
			sideBarMode++;
			leftMouseDown = true;
		}
		if (sideBarMode > 2 || sideBarMode < 0) {
			sideBarMode = 0;
		}
	}


	//SIDE BAR PAGE NUMBERS:
	// 0 --> all normal gates
	// 1 --> all memory
	// 2 --> input/output gates
	
	
	//0 --> all normal gates
	//draw gate buttons & check if gate buttons are clicked
	if (sideBarMode == 0) {
		sideBarNGB.draw(window);
		sideBarAGB.draw(window);
		sideBarOGB.draw(window);
		sideBarXOGB.draw(window);

		if (!leftMouseDown) {
			if (sideBarNGB.isClicked(window)) {
				cout << "new not gate" << endl;
				createGate(new notGate);
			}
			if (sideBarAGB.isClicked(window)) {
				cout << "new and gate" << endl;
				createGate(new andGate);
			}
			if (sideBarOGB.isClicked(window)) {
				cout << "new or gate" << endl;
				createGate(new orGate);
			}
			if (sideBarXOGB.isClicked(window)) {
				cout << "new xOr gate" << endl;
				createGate(new xOrGate);
			}
		}
	}


	//1 --> all memory gates
	//draw gate buttons & check if gate buttons are clicked
	else if (sideBarMode == 1) {
		sideBarFBMGB.draw(window);
		sideBarBRGB.draw(window);
		if (!leftMouseDown) {
			if (sideBarBRGB.isClicked(window)) {
				cout << "new bool reader" << endl;
				createGate(new boolReader);
			}
			if (sideBarFBMGB.isClicked(window)) {
				cout << "new 4 bit memory reader" << endl;
				createGate(new fourBitMemory);
			}
		}
	}



	// 2 --> input/output gates
	//draw gate buttons & check if gate buttons are clicked
	else if (sideBarMode == 2) {

		sideBarIGB.draw(window);
		sideBarOPGB.draw(window);
		sideBarPEGB.draw(window);
		sideBarSGB.draw(window);

		if (!leftMouseDown) {
			if (sideBarIGB.isClicked(window)) {
				cout << "new input gate" << endl;
				createGate(new inputGate);
			}
			if (sideBarOPGB.isClicked(window)) {
				cout << "new output gate" << endl;
				createGate(new outputGate);
			}
			if (sideBarPEGB.isClicked(window)) {
				cout << "new pulse gate" << endl;
				createGate(new pulseEmitter);
			}
			if (sideBarSGB.isClicked(window)) {
				cout << "new splitter gate" << endl;
				createGate(new splitterGate);
			}
		}
	}
}

//draws all the normal buttons, as well as checks if they are clicked on
void simulator::buttons(sf::RenderWindow& window) {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~PAGE BUTTONS:~~~~~~~~~~~~~~~~~~~~~~~~~

	//draw & check if clicked
	for (size_t x = 0; x < pageButtons.size(); x++) {
		pageButtons[x]->draw(window);
		if (pageButtons[x]->isClicked(window)) {
			pageNumber = x + 1;
			break;
		}
	}
	pageButtonBox.position = pageButtons[pageNumber - 1]->position;
	pageButtonBox.draw(window);


	//~~~~~~~~~~~~~~~~~~~~~~~~~~NORMAL BUTTONS:~~~~~~~~~~~~~~~~~~~~~~~~~

	//draw all buttons
	for (size_t x = 0; x < mainButtons.size(); x++) {
		mainButtons[x]->draw(window);
	}

	// 0 --> quitButton
	// 1 --> saveButton
	// 2 --> loadButton
	// 3 --> linkButton
	// 4 --> newButton
	// 5 --> helpButton

	//check if buttons are clicked
	if (!leftMouseDown) {


		if (mainButtons[0]->isClicked(window)) {

			//check if user whishes to save before quitting
			if (askIfWantToSave()) {
				save();
				cout << "saved" << endl;
				window.close();
			}
			else {
				window.close();
			}
		}
		else if (mainButtons[1]->isClicked(window)) {
			cout << "Save button pressed" << endl;
			leftMouseDown = true;
			save();
		}
		else if (mainButtons[2]->isClicked(window)) {
			cout << "Load button pressed" << endl;
			leftMouseDown = true;
			load();
		}
		else if (mainButtons[3]->isClicked(window)) {
			cout << "Link button pressed" << endl;

			linkStage = 0;

			leftMouseDown = true;
		}
		else if (mainButtons[4]->isClicked(window)) {
			cout << "New button pressed" << endl;
			//reset vectors
			allGates.clear(); 	allLinks.clear();

			//reset links config
			linkStage = 0;

			//reset page config
			pageNumber = 1; pageButtonBox.position = pageButtons[0]->position;

			//sidebar config
			sideBarMode = 0;

			//restart clock
			leftMouseDown = true;
		}
		else if (mainButtons[5]->isClicked(window)) {

			instructionWindow iw;
			iw.start();

			/*thread instructionsThread(&instructionWindow::start,instructionWindow());
			instructionsThread.detach();*/

			leftMouseDown = true;
		}
	}
}

//checks to see if a new page needs creating, and creates one if needed.
void simulator::newPage(sf::RenderWindow& window) {
	newPageButton.draw(window);

	if (newPageButton.isClicked(window) && !leftMouseDown && numberOfPages < 9) {
		numberOfPages++;
		button* newPageB = new button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(sideBarAreaWidth + (pageButtonWidth * (float)numberOfPages - 3), (float)gameHeight - pageButtonHeight), 20.f, 50.f, 0.f, false, "Page " + to_string(numberOfPages), 10);
		pageButtons.push_back(newPageB);
		leftMouseDown = true;
	}
}

//draw GUI to screen
void simulator::GUI(sf::RenderWindow& window) {
	
	for (size_t x = 0; x < guiBoxes.size(); x++) {
		guiBoxes[x].draw(window);
	}


	buttons(window);
	gateButtons(window);
	newPage(window);
}







//===============================================================================
//				gates stuff
//===============================================================================

//calls all gate caculations
void simulator::calcGates(sf::RenderWindow& window) {
	
	for (size_t x = 0; x < allGates.size(); ++x) {

		//seperate dynamic_casts needed here since some calc() functions require a sf::RenderWindow& parameter

		if (dynamic_cast <outputGate*>(allGates[x])) {
			(dynamic_cast <outputGate*> (allGates[x]))->calc(window);
		}
		else if (dynamic_cast <readDevice*>(allGates[x])) { // --> bool reader & 4-bit reader
			(dynamic_cast <readDevice*> (allGates[x]))->calc(window);
		}
		else if (dynamic_cast <pulseEmitter*>(allGates[x])) {
			(dynamic_cast <gate*> (allGates[x]))->calc();
		}

		for (int y = 0; y < 2; y++) {
			links(window);
			(dynamic_cast<gate*>(allGates[x]))->calc();
		}

		
	};
}

void simulator::checkDeleteGates(int x) {



	bool done = false;
	for (size_t z = 0; z < allLinks.size(); z++){
	for (size_t link = 0; link < allLinks.size(); link++) {//loops through all links
		for (size_t att = 0; att < allGates[x]->Attachers.size(); att++) {//loops through all attachers of selected gate
			if (allLinks[link].ia == dynamic_cast<attacher*>(allGates[x]->Attachers[att])) {

				allLinks[link].oa->linked = false;
				delete allLinks[link].ia;
				allGates[x]->Attachers[att] = new inputAttacher();

				//delete link
				allLinks.erase(allLinks.begin() + link);
				z--;
				done = true; break;
			}
			else {

				//set attachers as no longer linked
				allLinks[link].ia->linked = false;
				delete allLinks[link].oa;
				allGates[x]->Attachers[att] = new outputAttacher();

				//delete link
				allLinks.erase(allLinks.begin() + link);
				z--;
				done = true; break;
			}
			if (done) { break; }
		}
		if (done) { break; }
	}
	}
	//remove gate from vector
	allGates.erase(allGates.begin() + x);

}


//draws all gates, as well as checks if they need deleting
void simulator::drawGates(sf::RenderWindow& window) {

	//calc & draw & check delete
	for (size_t x = 0; x < allGates.size(); ++x) {

		//check delete and draw gates
		if (allGates[x]->pageNumber == pageNumber) {

			//check if gate needs deleting
			if (allGates[x]->checkDelete(window)) {
				checkDeleteGates(x);
			}
			else if (dynamic_cast <gate*>(allGates[x])) {
				(dynamic_cast <gate*>(allGates[x]))->draw(window); //draw gate
			}
		}
	}
}




//===============================================================================
//				Link stuff
//===============================================================================

//draws links on selected page & calls calc() on all links
void simulator::links(sf::RenderWindow& window) {
	for (size_t x = 0; x < allLinks.size(); x++) {

		allLinks[x].calc();

		if (allLinks[x].pageNumber == pageNumber) {
			allLinks[x].draw(window);
		}
	}
}

//loops through all gates and returns an attacher which has been clicked on
void simulator::checkForClickedAttacher(attacher*& attacherClicked, sf::RenderWindow& window) {
	for (size_t x = 0; x < allGates.size(); x++) {


		for (size_t y = 0; y < allGates[x]->Attachers.size(); y++) {
			if (allGates[x]->Attachers[y]->isClicked(window)) {
				attacherClicked = allGates[x]->Attachers[y];
				return;
			}

			//read devices (including 4-bit memory and bool readers) have other attachers (including incMemoryPointerAttacher & resetPointer)
			//and need to be checked:

			if (dynamic_cast <readDevice*>(allGates[x])) {
				if ((dynamic_cast <readDevice*>(allGates[x]))->incMemoryPointerAtacher->isClicked(window)) {
					attacherClicked = (dynamic_cast <readDevice*>(allGates[x]))->incMemoryPointerAtacher;
					return;
				}
				else if ((dynamic_cast <readDevice*>(allGates[x]))->resetPointer->isClicked(window)) {
					attacherClicked = (dynamic_cast <readDevice*>(allGates[x]))->resetPointer;
					return;
				}
			}
		}
	}
}

//function in charge of creating links
void simulator::createLink(sf::RenderWindow& window) {

	
	if (leftMouseDown) {
		return;
	}

	if (linkStage == 0)
	{
		attacher* clickedAttacher = NULL;

		checkForClickedAttacher(clickedAttacher, window);
		
		if (clickedAttacher != NULL) {
			leftMouseDown = true;
			if (clickedAttacher->linked == false) {
				if (dynamic_cast <outputAttacher*>(clickedAttacher)) {
					link newLink;

					 
// when push_back is called previous position pointers become invalidated
//to solve this problem allLink.reserve within init has been called

					allLinks.push_back(newLink);

					allLinks[allLinks.size()-1].oa = dynamic_cast <outputAttacher*>(clickedAttacher);
					allLinks[allLinks.size() - 1].oa->linked = true;
					linkStage = 1;
					cout << "First attacher found" << endl;
				}
				else {
					cout << "Not output attacher" << endl;
				}
			}
			else {
				cout << "Already linked" << endl;
			}
		}
	}


	else if (linkStage == 1)
	{
		attacher* clickedAttacher = NULL;

		checkForClickedAttacher(clickedAttacher, window);
		
		if (clickedAttacher != NULL) {
			leftMouseDown = true;
			if (clickedAttacher->linked == false) {
				if (dynamic_cast <inputAttacher*>(clickedAttacher)) {
					allLinks[allLinks.size() - 1].ia = dynamic_cast <inputAttacher*>(clickedAttacher);
					allLinks[allLinks.size() - 1].ia->linked = true;
					allLinks[allLinks.size() - 1].pageNumber = pageNumber; //what happens if there a link between pages?
					linkStage = 0;
					cout << "second attacher found" << endl << "Link made" << endl;
				}
				else {
					cout << "Not input attacher" << endl;
				}
			}
			else {
				cout << "Already linked" << endl;
			}
		}
	}
}



//===============================================================================
//				loading/saving stuff
//===============================================================================

//loads gates into allGates vector from text file of previously saved gates
void simulator::load() {
	allGates.clear();
	allLinks.clear();
	ifstream in_file;
	in_file.open("Gates infomation.txt");

	string gateType, positionString, pageNum;


	while (in_file >> gateType >> positionString >> pageNum) {
		gate* newGate;


		if (gateType == "And-Gate:") {
			newGate = new andGate;
		}
		else if (gateType == "Not-Gate:") {
			newGate = new notGate;
		}
		else if (gateType == "Or-Gate:") {
			newGate = new orGate;
		}
		else if (gateType == "Xor-Gate:") {
			newGate = new xOrGate;
		}
		else if (gateType == "Splitter-Gate:") {
			newGate = new splitterGate;
		}
		else if (gateType == "Input-Gate:") {
			newGate = new inputGate;
		}
		else if (gateType == "Output-Gate:") {
			newGate = new outputGate;
		}
		else if (gateType == "Boolean-Reader:") {
			newGate = new boolReader;
		}
		else if (gateType == "Four-Bit-Memory:") {
			newGate = new fourBitMemory;
		}
		else if (gateType == "Pulse-Emitter:") {
			newGate = new pulseEmitter;
		}
		else {
			newGate = new andGate;
		}

		bool onX = true;
		string xPos, yPos;

		//get positions from file string-->int
		for (int x = 0; x < (int)positionString.length(); x++) {
			if (positionString[x] == ',') {
				onX = false;
			}
			else {
				if (onX) {
					xPos += positionString[x];
				}
				else {
					yPos += positionString[x];
				}
			}
		}

		newGate->position = sf::Vector2f((float)stoi(xPos), (float)stoi(yPos));
		newGate->pageNumber = atoi(pageNum.c_str());
		newGate->init();
		allGates.push_back(newGate);
	}

	in_file.close();
}

//saves all gates to a text file
void simulator::save() {
	if (allGates.size() == 0) {
		return;
	}
	
	ofstream out_file;
	out_file.open("Gates infomation.txt");

	for (size_t x = 0; x < allGates.size(); x++) {
		allGates[x]->save(out_file);
	}

	out_file.close();
}

//when quit action is preforemed this checks if user whishes to save before quitting
int simulator::askIfWantToSave() {
	sf::RenderWindow saveWindow(sf::VideoMode(unsigned int(300), unsigned int(90)), "Logic Gate Simulator", sf::Style::Close);

	sf::Font font;
	sf::Text text;
	string txt = "Do you want to save before quitting?";
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "failed to load font" << endl;
	}

	text.setFont(font);
	text.setStyle(sf::Text::Regular);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(5, 10));
	text.setString(txt);
	text.setCharacterSize(15);


	button yes = button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(5, 60),20,45,1,true,"Save", 12);
	button no = button(sf::Color(200, 200, 200), sf::Color(200, 200, 200), sf::Color(129, 129, 129), sf::Vector2f(60,60), 20, 45, 1, true, "No", 12);

	int save = 0;

	while (saveWindow.isOpen())
	{
		sf::Event event;
		while (saveWindow.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				save = 2;
				saveWindow.close();
			} 
		}

		saveWindow.clear(backgroundColor);

		no.draw(saveWindow);
		yes.draw(saveWindow);
		saveWindow.draw(text);

		if (no.isClicked(saveWindow)) {
			save = 0;
			saveWindow.close();
		}
		if (yes.isClicked(saveWindow)) {
			save = 1;
			saveWindow.close();
		}

		saveWindow.display();

	}

	return save;
}
