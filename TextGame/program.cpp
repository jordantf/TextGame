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
			m_ptrCurrentRoom->printObjects();
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
	commands = { "north", "east", "south", "west", "up", "down", "look", "scan" };
}


void Program::setupFunctionMap() {
	functionMap["north"]		= &Program::move;
	functionMap["east"]			= &Program::move;
	functionMap["south"]		= &Program::move;
	functionMap["west"]			= &Program::move;
	functionMap["up"]			= &Program::move;
	functionMap["down"]			= &Program::move;
	functionMap["look"]			= &Program::look;
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


	/// <ROOM DESCRIPTIONS>
#pragma region

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

	string rdesc2 =
		"    A chill runs down your spine as you pass out of the working area of\n"
		"the street into the quieter, darker, and poorer area of the city. Junkies\n"
		"speak into the wind as if attempting to converse with something, someone,\n"
		"no one. And by the look of things, sleeping on discarded rags and bags\n"
		"seems to have become the norm for them around here. A lone street lamp,\n"
		"plastered with shredded posters, stands sentinel here, the only thing that\n"
		"seems to have survived the harsh conditions, if only barely.";

	string rdesc3 =
		"    The street grows louder here again as you return to the more orderly\n"
		"parts of the road. Hustle and bustle is evident at this intersection, where\n"
		"buses, cars and pedestrians appear to be crossing in droves at each change\n"
		"of the signal. The traffic is currently moving in a north-south direction,\n"
		"and in the crowds you manage to pick out countless people from all walks of\n"
		"life - a sad contrast to the conditions present just a few streets back,\n"
		"down the boulevard.";

	string rdesc4 =
		"    Against better judgment, you fearlessly step into the painted white\n"
		"rectangles of the crosswalk. You consider playing the old game of 'don't\n"
		"step on the unpainted pavement' as you move, but your thoughts are short-\n"
		"lived as a bus slams into you from the south, killing you instantly.";

	string rdesc5 =
		"    You have entered the alleyway, following the shady figures you saw\n"
		"heading this way. You're not quite sure why you decided to come here, but\n"
		"at least it isn't too late to turn around. Trash overflows from a nearby\n"
		"dumpster that looks like it hasn't been emptied in ages, and you can see\n"
		"little else around you besides the immense brick walls of the surrounding\n"
		"buildings. The only way out of here appears to be back to the north.";

	string rdesc6 =
		"This hallway is very dark, which doesn't surprise you given the age of the\n"
		"building and the positioning of the entryway back out to the alley. Gaps in\n"
		"the walls let in cold drafts of air, producing faint whistling noises that\n"
		"make you slightly uneasy. The hallway curves slightly up ahead, leading to\n"
		"a set of stairs which ascend into an even darker blackness.";

#pragma endregion

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

	// OBJECT DESCRIPTIONS
#pragma region

	string buildingDesc0 =
		"These buildings look like they're about to fall over.";

	string skyDesc0 =
		"The sky is cloudless, and the sun is shining brightly.";

	string streetDesc0 =
		"The once-smooth asphalt has been worn down in places, taking on an almost\n"
		"gravel-like consistency. You wonder how long it might have been since it\n"
		"was first laid down, and how long it might be until it's resurfaced.";

	string doorDesc0 =
		"These buildings have been securely shut to prevent access. Even if there\n"
		"were an easier way into them, you doubt there would be anything in there\n"
		"for you anyways, so you decide that it's best to move on.";

	string lampDesc2 =
		"This flickering lamp seems to be in a state of perpetual illumination,\n"
		"ceaselessly fighting against the brightness of the midday sun. A couple of\n"
		"shredded posters and other assorted advertisements are wrapped around the\n"
		"bottom half of the post, but the writing has faded too much to make out\n"
		"whatever they might have once said.";

	string junkiesDesc2 =
		"Several of the poorly dressed figures scamper away down an alley as they\n"
		"see you start to glance in their direction.";

	string alleyDesc2 =
		"A small, narrow alley that had escaped your notice lies tucked away here\n"
		"between two buildings. It seems safe enough to enter, though you don't\n"
		"think it'd be particularly nice in there.";

	string dumpsterDesc5 =
		"A dumpster, filled to the brim, sits here baking between the hot bricks\n"
		"of the nearby buildings. The stench emanating from it is overwhelming,\n"
		"and much of the trash seems to have been blown out by the wind, as\n"
		"the many torn plastic bags and other small pieces floating around\n"
		"aimlessly would indicate.";

	string trashDesc5 =
		"Trash floats and falls all around the dumpster that has been pushed up\n"
		"against the graffitied wall of one of the nearby buildings. It wouldn't\n"
		"be prudent to take a whiff of the trash, but if one were prepared to\n"
		"hold their breath, it could certainly be searched.";

	string wallDesc5 =
		"The brick wall of the nearby building has been covered in graffiti by\n"
		"some enterprising street artist. The graffiti appears to spell out the\n"
		"artist's name. Upon closer inspection, one of the letters in the name\n"
		"looks slightly discolored.";

	string letterDesc5 =
		"The final letter of the graffiti has been painted directly on top of\n"
		"a side door into the building, almost camouflaging it.";

	string doorDesc5 =
		"This door looks like it may lead into the building. While you don't\n"
		"know if it can be opened, it may still be worth a try.";

#pragma endregion

	// PEOPLE DESCRIPTIONS
#pragma region

	string kylanthaSDesc =
		"A muscular lady with a bright yellow hat stands here, overseeing the construction.";

	string kylanthaLDesc =
		"Kylantha is a burly woman, currently busying herself with supervising the\n"
		"many workers on site and ensuring all workplace safety measures are\n"
		"followed to the letter. While she is evidently comfortable getting down and\n"
		"dirty with it when necessary, she seems rather reserved today and appears\n"
		"content watching her team work from a distance.";

	string vagrantLDesc5 =
		"This man certainly looks like he has seen better days. Flies buzz\n"
		"around his unkempt hair as he ambles slowly through the alley, looking\n"
		"for what, you do not know. Keeping to himself, you decide it best not\n"
		"to bother him.";

#pragma endregion

	// ENTRIY AND DOOR DESCRIPTIONS
#pragma region

	string alleyMsg2 =
		"You cautiously step into the alley, unsure of what you will find.";

	string doorOpenMsg5 =
		"The door creaks loudly as you open it.";

	string doorCloseMsg5 =
		"The door screeches loudly as you close it.";

#pragma endregion


	// EXIT CREATION
	Exit* default_exit = new Exit();
	Exit* exit0n = new Exit(scanDesc0N, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit0e = new Exit(scanDesc0E, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit0s = new Exit(scanDesc0S, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit0w = new Exit(scanDesc0W, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit0u = new Exit(scanDesc0U, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit0d = new Exit(scanDesc0D, "", false, false, false, false, -1, {}, nullptr);

	Exit* exit1n = new Exit(scanDesc1N, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit1e = new Exit(scanDesc1E, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit1s = new Exit(scanDesc1S, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit1w = new Exit(scanDesc1W, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit1u = new Exit(scanDesc1U, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit1d = new Exit(scanDesc0D, "", false, false, false, false, -1, {}, nullptr);

	Exit* exit2n = new Exit(scanDesc1S, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit2e = new Exit(scanDesc2E, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit2s = new Exit(scanDesc2S, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit2w = new Exit(scanDesc2W, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit2u = new Exit(scanDesc1U, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit2d = new Exit(scanDesc0D, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit2a = new Exit("", "You cautiously enter the alleyway, unsure of what you will find.", true, false, false, false, -1, { "alley", "alleyway", "lane" }, nullptr);

	Exit* exit3n = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit3e = new Exit(scanDesc3E, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit3s = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit3w = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit3u = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit3d = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);

	Exit* exit5n = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit5e = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit5s = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit5w = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit5u = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);
	Exit* exit5d = new Exit(ns, "", false, false, false, false, -1, {}, nullptr);

	// EXIT ARRAY CREATION
	Exit* exitArray0[6] = { exit0n, exit0e, exit0s, exit0w, exit0u, exit0d };
	Exit* exitArray1[6] = { exit1n, exit1e, exit1s, exit1w, exit1u, exit1d };
	Exit* exitArray2[6] = { exit2n, exit2e, exit2s, exit2w, exit2u, exit2d };
	Exit* exitArray3[6] = { exit3n, exit3e, exit3s, exit3w, exit3u, exit3d };
	Exit* exitArray5[6] = { exit5n, exit5e, exit5s, exit5w, exit5u, exit5d };

	// ROOM CREATION
	RoomData* default_room_data = new RoomData(false, false, 1);
	Room* room0 = new Room("Hastings1", rdesc0, default_room_data, exitArray0, {}, {}, {}, {}, {});
	Room* room1 = new Room("Hastings2", rdesc1, default_room_data, exitArray1, {}, {}, {}, {}, {});
	Room* room2 = new Room("East Hastings", rdesc2, default_room_data, exitArray2, {}, {}, {}, {}, {});
	Room* room3 = new Room("Main and Hastings", rdesc3, default_room_data, exitArray3, {}, {}, {}, {}, {});
	Room* room5 = new Room("A Dark Alleyway", rdesc5, default_room_data, exitArray5, {}, {}, {}, {}, {});

	// SET DESTINATIONS OF EXITS
	exit0e->setDest(room1);
	exit1e->setDest(room2);
	exit1w->setDest(room0);
	exit2e->setDest(room3);
	exit2w->setDest(room1);
	exit3w->setDest(room2);
	exit5n->setDest(room2);

	exit2a->setDest(room5); // alley

	// ROOM DESC ADDITIONS
	Description* desc0 = new Description("some dilapidated buildings", { "building", "dilapidated", "buildings" }, buildingDesc0);
	Description* desc1 = new Description("the sky", { "sky" }, skyDesc0);
	Description* desc2 = new Description("Hastings Street", { "hastings", "street", "pavement", "road", "sidewalk", "asphalt" }, streetDesc0);
	Description* desc3 = new Description("some boarded up buildings", { "door", "doors", "board", "boarded", "boards", "window", "windows", "fence", "fencing", "fences" }, buildingDesc0);
	Description* desc4 = new Description("the recently demolished building", { "building", "dilapidated", "buildings", "collapsed", "rubble", "demolished" }, "Rubble is all that remains of the building that once stood here.");
	Description* desc5 = new Description("some street junkies", { "junkies" }, junkiesDesc2);
	Description* desc6 = new Description("the shredded posters and advertisements", { "writing", "words", "poster", "posters", "shredded", "torn", "ads", "ad", "advertisements", "advertisement" }, "The words on the shredded pages are no longer legible.");
	Description* desc7 = new Description("a narrow alleyway", { "alley", "alleyway", "lane" }, alleyDesc2);

	room0->addDesc(desc0);
	room0->addDesc(desc1);
	room0->addDesc(desc2);
	room0->addDesc(desc3);
	room1->addDesc(desc1);
	room1->addDesc(desc2);
	room1->addDesc(desc3);
	room1->addDesc(desc4);
	room2->addDesc(desc1);
	room2->addDesc(desc2);
	room2->addDesc(desc3);
	room2->addDesc(desc5);
	room2->addDesc(desc6);
	room2->addDesc(desc7);

	// OBJECT CREATION
	ObjectData* default_object_data = new ObjectData(false, false, true);
	Object* obj0 = new Object("a flickering street lamp", "A barely functional street lamp flickers in the sunlight.", lampDesc2, "", default_object_data, nullptr, {}, { "lamp", "flickering", "light" }, { desc5 }, {});

	room2->addObject(obj0);

	// NPC CREATION
	PersonData* default_person_data = new PersonData(false);
	Person* person0 = new Person("Kylantha, the grizzled forelady", { "kylantha", "woman", "lady", "forelady", "forewoman", "foreman", "muscular", "grizzled" }, kylanthaSDesc, kylanthaLDesc, default_person_data, {}, {});

	room1->addPerson(person0);

	// EXTRA EXIT CREATION
	room2->addExtraExit(exit2a);
	/*
	string desc;				// Message to display when scanning/looking this way
	string moveDesc;			// A message to display when moving this way
	bool isHidden;
	bool isDoor;
	bool isClosed;
	bool isLocked;
	int key_id;					// id of the key used to open this exit (if exit is a locked door)
	vector<string> nouns;		// Keywords with which to refer to this exit (if it is a door)
	Room* to_room;				// The room to which this exit leads
	*/

	// SPEC CREATION
	room2->specs["enter"]	= 1;
	room1->specs["say"] = 0;

	// STARTING ROOM
	m_ptrCurrentRoom = room0;
}

void Program::ignoreOutput(vector<string> v, int i) {
	cout << "\nWarning: Your input '";
	for (int a = i; a < v.size() - 1; a++) {
		cout << v[a] << " ";
	}
	cout << v[v.size() - 1] << "' was ignored." << endl;
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
		// Check if command EXACTLY matches a special keyword on an obj/person/room (abbreviations NOT allowed)
		// Inventory objects
		for (int i = 0; i < playerInventory.size(); i++) {
			if (playerInventory[i]->specs.find(v[0]) != playerInventory[i]->specs.end()) {
				special(v, playerInventory[i]->specs.find(v[0])->second);
				return;
			}
		}

		// Room objects
		for (int i = 0; i < m_ptrCurrentRoom->objects.size(); i++) {
			if (m_ptrCurrentRoom->objects[i]->specs.find(v[0]) != m_ptrCurrentRoom->objects[i]->specs.end()) {
				special(v, m_ptrCurrentRoom->objects[i]->specs.find(v[0])->second);
				return;
			}
		}

		// Person
		for (int i = 0; i < m_ptrCurrentRoom->people.size(); i++) {
			if (m_ptrCurrentRoom->people[i]->specs.find(v[0]) != m_ptrCurrentRoom->people[i]->specs.end()) {
				special(v, m_ptrCurrentRoom->people[i]->specs.find(v[0])->second);
				return;
			}
		}

		// Room itself
		if (m_ptrCurrentRoom->specs.find(v[0]) != m_ptrCurrentRoom->specs.end()) {
			special(v, m_ptrCurrentRoom->specs.find(v[0])->second);
			return;
		}

		// Check if command is in the command list; if it is, execute it
		for (int i = 0; i < commands.size(); i++) {
			if (is_abbrev(commands[i], v[0])) {
				// EXECUTE COMMAND
				((*this).*(functionMap.find(commands[i]))->second)(v);
				return;
			}
		}

		// Command not found
		// TODO: Print HUH or some other message saying command is unrecognized

	}
}

void Program::move(vector<string> v) {
	if (v.size() > 1) {
		ignoreOutput(v, 1);
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

void Program::look(vector<string> v) {
	int size = v.size();
	if (size == 1) {
		moved = true;
		return;
	}
	if (size == 2) {
		if (is_abbrev("inside", v[1])) {
			look_in(v[1]);
			return;
		} else {
			look_at(v[1]);
			return;
		}
	}
	if (size == 3) {
		if ((v[1] == "at") || (v[1] == "the")) {
			look_at(v[2]);
			return;
		} else if (is_abbrev("inside", v[1])) {
			look_in(v[2]);
			return;
		} else {
			ignoreOutput(v, 2);
			look_at(v[1]);
			return;
		}
	}
	if (size >= 4) {
		if (v[1] == "at") {
			if (v[2] == "the") {
				if (size > 4) {
					ignoreOutput(v, 4);
				}
				look_at(v[3]);
				return;
			} else {
				ignoreOutput(v, 3);
				look_at(v[2]);
				return;
			}
		} else if (is_abbrev("inside", v[1])) {
			if (v[2] == "the") {
				if (size > 4) {
					ignoreOutput(v, 4);
				}
				look_in(v[3]);
				return;
			}
			else {
				ignoreOutput(v, 3);
				look_in(v[2]);
				return;
			}
		} else {
			// not looking "at" or "in" something
			ignoreOutput(v, 2);
			look_at(v[1]);
			return;
		}
	}
}

void Program::look_at(string noun) {
	if ((noun == "at") || (noun == "the")) {
		std::cout << "\nLook at what?" << endl;
		return;
	}

	// Inventory objects
	for (int i = 0; i < playerInventory.size(); i++) {
		for (int j = 0; j < playerInventory[i]->nouns.size(); j++) {
			if (playerInventory[i]->nouns[j] == noun) {
				std::cout << "\nYou look at " << playerInventory[i]->name << "." << endl;
				std::cout << playerInventory[i]->longDesc << endl;
				return;
			}
		}
	}

	// Inventory extra descs
	for (int i = 0; i < playerInventory.size(); i++) {
		for (int j = 0; j < playerInventory[i]->descs.size(); j++) {
			for (int k = 0; k < playerInventory[i]->descs[j]->nouns.size(); k++) {
				if (playerInventory[i]->descs[j]->nouns[k] == noun) {
					std::cout << "\nYou look at " << playerInventory[i]->descs[j]->name << "." << endl;
					std::cout << playerInventory[i]->descs[j]->description << endl;
					return;
				}
			}
		}
	}


	// Room objects
	for (int i = 0; i < m_ptrCurrentRoom->objects.size(); i++) {
		for (int j = 0; j < m_ptrCurrentRoom->objects[i]->nouns.size(); j++) {
			if (m_ptrCurrentRoom->objects[i]->nouns[j] == noun) {
				if (m_ptrCurrentRoom->objects[i]->objectData->canSee != false) {
					std::cout << "\nYou look at " << m_ptrCurrentRoom->objects[i]->name << "." << endl;
					std::cout << m_ptrCurrentRoom->objects[i]->longDesc << endl;
					return;
				} else {
					std::cout << "\nYou do not see that here." << endl;
					return;
				}
			}
		}
	}

	// Room object extra descs
	for (int i = 0; i < m_ptrCurrentRoom->objects.size(); i++) {
		for (int j = 0; j < m_ptrCurrentRoom->objects[i]->descs.size(); j++) {
			for (int k = 0; k < m_ptrCurrentRoom->objects[i]->descs[j]->nouns.size(); k++) {
				if (m_ptrCurrentRoom->objects[i]->descs[j]->nouns[k] == noun) {
					if (m_ptrCurrentRoom->objects[i]->objectData->canSee != false) {
						std::cout << "\nYou look at " << m_ptrCurrentRoom->objects[i]->descs[j]->name << "." << endl;
						std::cout << m_ptrCurrentRoom->objects[i]->descs[j]->description << endl;
						return;
					} else {
						std::cout << "\nYou do not see that here." << endl;
					}
				}
			}
		}
	}

	// Person
	for (int i = 0; i < m_ptrCurrentRoom->people.size(); i++) {
		for (int j = 0; j < m_ptrCurrentRoom->people[i]->nouns.size(); j++) {
			if (m_ptrCurrentRoom->people[i]->nouns[j] == noun) {
				std::cout << "\nYou look at " << m_ptrCurrentRoom->people[i]->name << "." << endl;
				std::cout << m_ptrCurrentRoom->people[i]->longDesc << endl;
				return;
			}
		}
	}
	
	// Person extra descs
	for (int i = 0; i < m_ptrCurrentRoom->people.size(); i++) {
		for (int j = 0; j < m_ptrCurrentRoom->people[i]->descs.size(); j++) {
			for (int k = 0; k < m_ptrCurrentRoom->people[i]->descs[j]->nouns.size(); k++) {
				if (m_ptrCurrentRoom->people[i]->descs[j]->nouns[k] == noun) {
					std::cout << "\nYou look at " << m_ptrCurrentRoom->people[i]->descs[j]->name << "." << endl;
					std::cout << m_ptrCurrentRoom->people[i]->descs[j]->description << endl;
					return;
				}
			}
		}
	}

	// Directionals
	vector<string> dirs = { "north", "east", "south", "west", "up", "down" };
	for (int i = 0; i < dirs.size(); i++) {
		if (is_abbrev(dirs[i], noun)) {
			std::cout << std::endl;
			m_ptrCurrentRoom->showScanDesc((Direction) i);
			return;
		}
	}

	// Room extra descs itself
	for (int i = 0; i < m_ptrCurrentRoom->descs.size(); i++) {
		for (int j = 0; j < m_ptrCurrentRoom->descs[i]->nouns.size(); j++) {
			if (m_ptrCurrentRoom->descs[i]->nouns[j] == noun) {
				std::cout << "\nYou look at " << m_ptrCurrentRoom->descs[i]->name << "." << endl;
				std::cout << m_ptrCurrentRoom->descs[i]->description << endl;
				return;
			}
		}
	}

	// Object could not be found
	std::cout << "\nYou do not see that here." << endl;
}

void Program::look_in(string noun) {
	if ((noun == "the") || (is_abbrev("inside", noun))) {
		std::cout << "\nLook in what?" << endl;
		return;
	}

	// Inventory objects
	for (int i = 0; i < playerInventory.size(); i++) {
		for (int j = 0; j < playerInventory[i]->nouns.size(); j++) {
			if (playerInventory[i]->nouns[j] == noun) {
				std::cout << "\nYou look inside " << playerInventory[i]->name << "." << endl;
				for (int k = 0; k < playerInventory[i]->contains.size(); k++) {
					std::cout << playerInventory[i]->contains[k]->name << endl;
				}
				return;
			}
		}
	}

	// Room objects
	for (int i = 0; i < m_ptrCurrentRoom->objects.size(); i++) {
		for (int j = 0; j < m_ptrCurrentRoom->objects[i]->nouns.size(); j++) {
			if (m_ptrCurrentRoom->objects[i]->nouns[j] == noun) {
				std::cout << "\nYou look inside " << m_ptrCurrentRoom->objects[i]->name << "." << endl;
				for (int k = 0; k < m_ptrCurrentRoom->objects[i]->contains.size(); k++) {
					std::cout << m_ptrCurrentRoom->objects[i]->contains[k]->name << endl;
				}
				return;
			}
		}
	}

	// Object not found
	std::cout << "\nYou do not see that here." << endl;
}

void Program::scan(vector<string> v) {
	if (v.size() > 1) {
		if (v.size() > 2) {
			ignoreOutput(v, 2);
			vector<string> dirs = { "north", "east", "south", "west", "up", "down" };
			for (int i = 0; i < dirs.size(); i++) {
				if (is_abbrev(dirs[i], v[1])) {
					std::cout << std::endl;
					m_ptrCurrentRoom->showScanDesc((Direction) i);
					return;
				}
			}
		}
		else { // size is exactly 2
			vector<string> dirs = { "north", "east", "south", "west", "up", "down" };
			for (int i = 0; i < dirs.size(); i++) {
				if (is_abbrev(dirs[i], v[1])) {
					std::cout << std::endl;
					m_ptrCurrentRoom->showScanDesc((Direction)i);
					return;
				}
			}
			ignoreOutput(v, 1);
		}
	}
	std::cout << std::endl;
	m_ptrCurrentRoom->showScanDesc(NORTH);
	m_ptrCurrentRoom->showScanDesc(EAST);
	m_ptrCurrentRoom->showScanDesc(SOUTH);
	m_ptrCurrentRoom->showScanDesc(WEST);
	m_ptrCurrentRoom->showScanDesc(UP);
	m_ptrCurrentRoom->showScanDesc(DOWN);
}

void Program::special(vector<string> v, int i) {
	switch (i) {
		case 0: {
			if (v.size() == 2) {
				if (v[1] == "hello") {
					std::cout << "\nKylantha looks you over and begins to speak," << std::endl;
					std::cout << "\n" << "        Hello there, and watch your step! My team and I are quite busy\n"
						"    cleaning up the debris from that building o'er there that just fell\n"
						"    over. It'll probably be a few days until we're done, so I wouldn't\n"
						"    stick around too long if I were you. Well, I've got to get back to\n"
						"    work. Take care now!" << std::endl;
					std::cout << "\nKylantha turns away, and resumes her observations." << endl;
				}
			} else {
				std::cout << "Say what?" << endl;
				return;
			}
		break;
		}
		case 1: {
			if (v.size() == 2) {
				std::vector<string>::iterator it = find(m_ptrCurrentRoom->extraExits[0]->nouns.begin(), m_ptrCurrentRoom->extraExits[0]->nouns.end(), v[1]);
				if (it != m_ptrCurrentRoom->extraExits[0]->nouns.end()) {
					std::cout << "\n" << m_ptrCurrentRoom->extraExits[0]->moveDesc << endl;
					m_ptrCurrentRoom = m_ptrCurrentRoom->extraExits[0]->to_room;
					moved = true;
					return;
				} else {
					std::cout << "Huh?!" << endl;
					return;
				}
			} else {
				std::cout << "Huh?!" << endl;
				return;
			}
		}
	}
}

