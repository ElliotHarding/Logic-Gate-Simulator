#include "main.h"

int main() {

	simulator sim;

	try
	{
		sim.start();
	}
	catch (const std::exception& e)
	{
		cout << endl << endl << "Warning, error! " << endl << "Details of error: " << e.what() << endl;
	}
	catch (...) {
		cout << endl << endl << "An unknown error has occourd" << endl;
	}

	cout << endl << endl << "type 'y' to restart, otherwise enter any key" << endl;
	string answer;
	cin >> answer;
	if (answer == "y") {
		main();
	}
}

/*

Steps to adding new gate type :
	--> create class "Example gate"
		--> create exampleGate::calc()
		--> create exampleGate::exampleGate() 
			--> create attachers, and set positions
			--> set sprite file location
			--> setup hitbox of gate
			--> set gateName
	--> create instance in simulator.h
	--> add to simulator::load() list



Steps to adding new gate-button type :
	--> create class "exampleGateButton"
		--> create exampleGateButton::exampleGateButton
			--> set description
			--> set hitbox
			--> call init(sprite location, scale)
			--> asign position
	--> create instance in simulator.h
	--> draw & check clicked in simulator::gatebuttons()

*/