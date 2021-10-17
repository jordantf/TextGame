#include "program.h"



Program::Program() {
	m_ptrCurrentRoom = nullptr;
	m_done = false;
	moved = true;
	setupFunctionMap();
	setupVariables();
	setupWorld();
}

string Program::toLower(const string& upper) {
	string lower = "";
	for (unsigned int i = 0; i < upper.size(); i++) {
		lower += tolower(upper[i]);
	}
	return lower;
}


void Program::run() {
	std::cout << "If this is your first time playing, type HELP for a list of commands." << std::endl;
	string userInput;

	while (!m_done) {
	/*
		if (moved) {
			m_ptrCurrentRoom->outputRoomInfo();
			m_ptrCurrentRoom->printObjects();
		}
		if (m_ptrCurrentRoom->DEATH == true) {
			std::cout << "\nGAME OVER" << endl;
			std::cout << "Press any key to try again." << endl;
			std::getchar();
			std::cout << "Space-time rewinds, and you feel yourself pulled back to a familiar place..." << endl;
			break;
		}
		m_ptrCurrentRoom->exitPrompt();
		moved = false;
		std::getline(cin, userInput);
		parseCommand(toLower(userInput));
	*/
	}
}




void Program::setupFunctionMap() {
	functionMap["north"]		= &Program::do_move;
	functionMap["east"]			= &Program::do_move;
	functionMap["south"]		= &Program::do_move;
	functionMap["west"]			= &Program::do_move;
	functionMap["up"]			= &Program::do_move;
	functionMap["down"]			= &Program::do_move;

	/*
	functionMap["help"]			= &Program::help;
	functionMap["look"]			= &Program::look;
	functionMap["scan"]			= &Program::scan;
	functionMap["open"]			= &Program::open;
	functionMap["close"]		= &Program::close;
	functionMap["inventory"]	= &Program::inventory;
	functionMap["take"]			= &Program::get;
	functionMap["get"]			= &Program::get;
	functionMap["drop"]			= &Program::drop;

	functionMap["enter"]		= &Program::enter;
	*/
}

void Program::setupVariables() {
	// Checking variable states will be used to provide 'hints' (akin to game progression)
	variables["trashSearched"] = false;
}

void Program::setupWorld() {

}



void Program::do_move(vector<string> v) {

}


// Check if command is in the command list


// If not in the list, check if command EXACTLY matches a special keyword on an obj/person/room (abbreviations NOT allowed)