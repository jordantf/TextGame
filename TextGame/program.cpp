#include "program.h"
#include "structs.h"

Program::Program() {
	m_ptrCurrentRoom = nullptr;
	m_done = false;
	moved = true;
	setupCommands();
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
		if (moved) {
			m_ptrCurrentRoom->outputRoomInfo();
			// m_ptrCurrentRoom->printObjects();
		}
		if (m_ptrCurrentRoom->roomData->isDeathTrap == true) {
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
	}
}

void Program::setupCommands() {
	commands = { "north", "east", "south", "west", "up", "down", "scan" };
}


void Program::setupFunctionMap() {
	functionMap["north"]		= &Program::do_move;
	functionMap["east"]			= &Program::do_move;
	functionMap["south"]		= &Program::do_move;
	functionMap["west"]			= &Program::do_move;
	functionMap["up"]			= &Program::do_move;
	functionMap["down"]			= &Program::do_move;
	functionMap["scan"]			= &Program::scan;
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


	// SCAN DESCRIPTIONS
	#pragma region

	string ns = "You see nothing special.";

	string scanDesc0N =
		"Dilapidated buildings line the street, some of which have been fenced off.";

	string scanDesc0E =
		"The street continues.";

	string scanDesc0S =
		"Boarded windows and doors mark the entrances to more decaying buildings.";

	string scanDesc0W =
		"You just came from there - wouldn't be much point in going back.";

	string scanDesc0U =
		"The sky is a brilliant blue - looks like great weather today.";

	string scanDesc0D =
		"The crumbling pavement is scarred and cracked from years of abuse.";

	string scanDesc1N =
		"A fallen building lies collapsed in a dusty heap of rubble and debris.";

	string scanDesc1E =
		"The street, and its inhabitants, grow shadier in this direction.";

	string scanDesc1S =
		"More boarded buildings.";

	string scanDesc1W =
		"Sirens come and go like the flapping of a butterfly's wings on the breeze.";

	string scanDesc1U =
		"Nary a cloud complicates the sky.";

	string scanDesc2E =
		"The street looks like it gets a lot better, and busier, that way.";

	string scanDesc2S =
		"Several junkies seem to have made this area of the street their home.";

	string scanDesc2W =
		"Some sort of construction site has been erected in this direction.";

	string scanDesc3E =
		"Going that way would be a bad idea considering the traffic.";

#pragma endregion

	string rdesc0 =
		"    Having fallen into disrepair over many years, Hastings Street has\n"
		"certainly become quite the sight to behold. Many of the buildings around\n"
		"you teeter on the brink of total collapse, and while you aren't entirely\n"
		"sure that standing here is completely safe, they all appear to be holding\n"
		"steady for the moment. The street continues on, towards the east.";

	string rdesc1 =
		"    Construction crews scramble about this area of the street, tending to\n"
		"what appears to be a recently demolished building. The shrill grind of a\n"
		"jackhammer rings through the air, disrupting your focus, though it doesn't\n"
		"seem to bother those around you all that much. The street continues on\n"
		"towards the east, while back to the west you hear the blaring of\n"
		"approaching sirens, giving chase to vagrants unknown.";


	// EXIT CREATION
	Exit* default_exit = new Exit();
	Exit* e0n = new Exit(scanDesc0N, "", false, false, false, false, -1, {}, nullptr);
	Exit* e0e = new Exit(scanDesc0E, "You continue down the street.", false, false, false, false, -1, {}, nullptr);
	Exit* e0s = new Exit(scanDesc0S, "", false, false, false, false, -1, {}, nullptr);
	Exit* e0w = new Exit(scanDesc0W, "", false, false, false, false, -1, {}, nullptr);
	Exit* e0u = new Exit(scanDesc0U, "", false, false, false, false, -1, {}, nullptr);
	Exit* e0d = new Exit(scanDesc0D, "", false, false, false, false, -1, {}, nullptr);

	Exit* e1n = new Exit(scanDesc1N, "", false, false, false, false, -1, {}, nullptr);
	Exit* e1e = new Exit(scanDesc1E, "", false, false, false, false, -1, {}, nullptr);
	Exit* e1s = new Exit(scanDesc1S, "", false, false, false, false, -1, {}, nullptr);
	Exit* e1w = new Exit(scanDesc1W, "You head back down the street.", false, false, false, false, -1, {}, nullptr);
	Exit* e1u = new Exit(scanDesc1U, "", false, false, false, false, -1, {}, nullptr);
	Exit* e1d = new Exit(scanDesc0D, "", false, false, false, false, -1, {}, nullptr);

	// EXIT ARRAY CREATION
	Exit* e0[6] = { e0n, e0e, e0s, e0w, e0u, e0d };
	Exit* e1[6] = { e1n, e1e, e1s, e1w, e1u, e1d };

	// ROOM CREATION
	RoomData* default_room_data = new RoomData(false, false, 1);
	Room* r0 = new Room("Hastings1", rdesc0, default_room_data, e0, {}, {}, {}, {}, {});
	Room* r1 = new Room("Hastings2", rdesc1, default_room_data, e1, {}, {}, {}, {}, {});

	// SET DESTINATIONS OF EXITS
	e0e->setDest(r1);
	e1w->setDest(r0);

	// STARTING ROOM
	m_ptrCurrentRoom = r0;
}

int Program::is_abbrev(string str, string substr) {
	return !(strncmp(str.c_str(), substr.c_str(), strlen(substr.c_str())));
}

void Program::parseCommand(string userInput) {
	vector<string> v = {};
	string temp = "";
	for (int i = 0; i < userInput.length(); i++) {
		if (userInput[i] == ' ') {
			v.push_back(temp);
			temp = "";
		}
		else {
			temp.push_back(userInput[i]);
		}
	}
	v.push_back(temp);

	if (v.size() == 0) {
		// DO NOTHING AND PRINT A NEW PROMPT
	}
	else {
		for (int i = 0; i < commands.size(); i++) {
			if (is_abbrev(commands[i], v[0])) {
				// EXECUTE COMMAND
				((*this).*(functionMap.find(commands[i]))->second)(v);
				return;
			}
		}
	}
}

void Program::do_move(vector<string> v) {
	if (v.size() > 1) {
		cout << "\nWarning: Your input '";
		for (int i = 1; i < v.size() - 1; i++) {
			cout << v[i] << " ";
		}
		cout << v[v.size() - 1] << "' was ignored." << endl;
	}
	char c = v[0].at(0);
	int dir = -1;
	int val = -1;
	switch (c) {
		case 'n': {
			val = m_ptrCurrentRoom->canGo(NORTH);
			dir = NORTH;
			break;
		} 
		case 'e': {
			val = m_ptrCurrentRoom->canGo(EAST);
			dir = EAST;
			break;
		}
		case 's': {
			val = m_ptrCurrentRoom->canGo(SOUTH);
			dir = SOUTH;
			break;
		}
		case 'w': {
			val = m_ptrCurrentRoom->canGo(WEST);
			dir = WEST;
			break;
		}
		case 'u': {
			val = m_ptrCurrentRoom->canGo(UP);
			dir = UP;
			break;
		}
		case 'd': {
			val = m_ptrCurrentRoom->canGo(DOWN);
			dir = DOWN;
			break;
		}
		default: {
			cout << "Error: Program::do_move(vector<string> v) ... v[0] is an invalid direction" << endl;
		}
	}
	// 0 = can go that way
	// 1 = no exit that way
	// 2 = visible door is blocking
	// 3 = invisible door is blocking
	switch (val) {
		case 0: {
			if (m_ptrCurrentRoom->normalExits[dir]->moveDesc != "") {
				cout << "\n" << m_ptrCurrentRoom->normalExits[dir]->moveDesc << endl;
			}
			m_ptrCurrentRoom = m_ptrCurrentRoom->normalExits[dir]->to_room;
			moved = true;
			break;
		}
		case 1: {
			cout << "\nAlas, you cannot go that way..." << endl;
			break;
		}
		case 2: {
			cout << "\nThe " << m_ptrCurrentRoom->normalExits[dir]->nouns[0] << " seems to be closed.";
			break;
		}
		case 3: {
			cout << "\nAlas, you cannot go that way..." << endl;
			break;
		}
		default: {
			cout << "Error: Invalid return value of Room::canGo(Direction direction)";
		}
	}
}

void Program::scan(vector<string> v) {
	if (v.size() > 1) {
		cout << "\nWarning: Your input '";
		for (int i = 1; i < v.size() - 1; i++) {
			cout << v[i] << " ";
		}
		cout << v[v.size() - 1] << "' was ignored." << endl;
	}
	std::cout << std::endl;
	m_ptrCurrentRoom->showScanDesc(NORTH);
	m_ptrCurrentRoom->showScanDesc(EAST);
	m_ptrCurrentRoom->showScanDesc(SOUTH);
	m_ptrCurrentRoom->showScanDesc(WEST);
	m_ptrCurrentRoom->showScanDesc(UP);
	m_ptrCurrentRoom->showScanDesc(DOWN);
}


// Check if command is in the command list


// If not in the list, check if command EXACTLY matches a special keyword on an obj/person/room (abbreviations NOT allowed)