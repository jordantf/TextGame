#include "structs.h"

Room::Room() {
	setup();
}

Room::Room(string name, string desc, RoomData* roomData, Exit* normalExits[], vector<Exit*> extraExits, vector<Object*> objects, vector<Person*> people, vector<Description*> descs, map<string, int> specs) {
	setup(name, desc, roomData, normalExits, extraExits, objects, people, descs, specs);
}

void Room::setup(string name, string desc, RoomData* roomData, Exit* normalExits[], vector<Exit*> extraExits, vector<Object*> objects, vector<Person*> people, vector<Description*> descs, map<string, int> specs) {
	this->name = name;
	this->desc = desc;
	this->roomData = roomData;
	for (int i = 0; i < 6; i++) {
		this->normalExits[i] = normalExits[i];
	}
	this->extraExits = extraExits;
	this->objects = objects;
	this->people = people;
	this->descs = descs;
	this->specs = specs;
}

RoomData::RoomData() {
	setup();
}

RoomData::RoomData(bool isDeathTrap, bool isDark, int lights) {
	setup(isDeathTrap, isDark, lights);
}

void RoomData::setup(bool isDeathTrap, bool isDark, int lights) {
	this->isDeathTrap = isDeathTrap;
	this->isDark = isDark;
	this->lights = lights;
}

void Room::color(int color = 0x07) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Room::outputRoomInfo() {
	color(0x03);
	std::cout << "\n" << this->name << std::endl;
	color();
	std::cout << this->desc << std::endl;
}

void Room::printObjects() {
	for (int i = 0; i < objects.size(); i++) {
		color(0x0e);
		if ((objects[i]->objectData->isHidden == false) && objects[i]->shortDesc != "") {
			std::cout << objects[i]->shortDesc << endl;
		}
		color();
	}
	for (int i = 0; i < people.size(); i++) {
		color(0x0c);
		if ((people[i]->personData->isHidden == false) && people[i]->shortDesc != "") {
			std::cout << people[i]->shortDesc << endl;
		}
		color();
	}
}

void Room::exitPrompt() {
	std::cout << "\nExits:";
	if (this->normalExits[NORTH]->to_room != nullptr && this->normalExits[NORTH]->isHidden == false) { std::cout << "N"; }
	if (this->normalExits[EAST]->to_room != nullptr && this->normalExits[EAST]->isHidden == false) { std::cout << "E"; }
	if (this->normalExits[SOUTH]->to_room != nullptr && this->normalExits[SOUTH]->isHidden == false) { std::cout << "S"; }
	if (this->normalExits[WEST]->to_room != nullptr && this->normalExits[WEST]->isHidden == false) { std::cout << "W"; }
	if (this->normalExits[UP]->to_room != nullptr && this->normalExits[UP]->isHidden == false) { std::cout << "U"; }
	if (this->normalExits[DOWN]->to_room != nullptr && this->normalExits[DOWN]->isHidden == false) { std::cout << "D"; }
	std::cout << "> ";
}

int Room::canGo(Direction d) {
	// 0 = can go that way
	// 1 = no exit that way
	// 2 = visible door is blocking
	// 3 = invisible door is blocking
	if (this->normalExits[d]->to_room != nullptr) {
		if (this->normalExits[d]->isDoor == 1) {
			if (this->normalExits[d]->isClosed == 1) {
				if (this->normalExits[d]->isHidden == 1) {
					// cout << "\nAlas, you cannot go that way..." << endl;
					return 3;
				} else {
					// cout << "\nThe " << this->normalExits[d]->nouns[0] << " seems to be closed.";
					return 2;
				}
			}
			else {
				// cout << "\nYes, you can go that way." << endl;
				return 0;
			}
		} else {
			// cout << "\nYes, you can go that way." << endl;
			return 0;
		}
	} else {
		return 1;
	}
}

void Room::showScanDesc(Direction d) {
	std::cout << "Looking ";
	switch (d) {
		case NORTH: {
			std::cout << "north:" << std::endl;
			break;
		} 
		case EAST: {
			std::cout << "east:" << std::endl;
			break;
		}
		case SOUTH: {
			std::cout << "south:" << std::endl;
			break;
		}
		case WEST: {
			std::cout << "west:" << std::endl;
			break;
		}
		case UP: {
			std::cout << "up:" << std::endl;
			break;
		}
		case DOWN: {
			std::cout << "down:" << std::endl;
			break;
		}
	}
	cout << this->normalExits[d]->desc << endl;
	if (this->normalExits[d]->to_room != nullptr) {
		for (int i = 0; i < this->normalExits[d]->to_room->people.size(); i++) {
			if ((this->normalExits[d]->to_room->people[i]->personData->isHidden == false) && (this->normalExits[d]->to_room->people[i]->shortDesc != "")) {
				color(0x0c);
				std::cout << this->normalExits[d]->to_room->people[i]->shortDesc << std::endl;
				color();
			}
		}
	}
}

void Room::addDesc(Description* desc) {
	this->descs.push_back(desc);
}

void Room::removeDesc(Description* desc) {
	std::vector<Description*>::iterator it = find(this->descs.begin(), this->descs.end(), desc);
	if (it != this->descs.end()) {
		this->descs.erase(it);
	}
}

void Room::addPerson(Person* person) {
	this->people.push_back(person);
}

void Room::removePerson(Person* person) {
	std::vector<Person*>::iterator it = find(this->people.begin(), this->people.end(), person);
	if (it != this->people.end()) {
		this->people.erase(it);
	}
}

void Room::addObject(Object* object) {
	this->objects.push_back(object);
}

void Room::removeObject(Object* object) {
	std::vector<Object*>::iterator it = find(this->objects.begin(), this->objects.end(), object);
	if (it != this->objects.end()) {
		this->objects.erase(it);
		return;
	}
}

void Room::addExtraExit(Exit* exit) {
	this->extraExits.push_back(exit);
}


Exit::Exit() {
	setup();
}

Exit::Exit(string desc, string moveDesc, bool isHidden, bool isDoor, bool isClosed, bool isLocked, int key_id, vector<string> nouns, Room* to_room) {
	setup(desc, moveDesc, isHidden, isDoor, isClosed, isLocked, key_id, nouns, to_room);
}

void Exit::setup(string desc, string moveDesc, bool isHidden, bool isDoor, bool isClosed, bool isLocked, int key_id, vector<string> nouns, Room* to_room) {
	this->desc = desc;
	this->moveDesc = moveDesc;
	this->isHidden = isHidden;
	this->isDoor = isDoor;
	this->isClosed = isClosed;
	this->isLocked = isLocked;
	this->key_id = key_id;
	this->nouns = nouns;
	this->to_room = to_room;
}

void Exit::setDest(Room* room) {
	this->to_room = room;
}


Description::Description() {
	setup();
}

Description::Description(string name, vector<string> nouns, string description) {
	setup(name, nouns, description);
}

void Description::setup(string name, vector<string> nouns, string description) {
	this->name = name;
	this->nouns = nouns;
	this->description = description;
}



ObjectData::ObjectData() {
	setup();
}

ObjectData::ObjectData(bool isHidden, bool canTake, bool canSee) {
	setup(isHidden, canTake, canSee);
}

void ObjectData::setup(bool isHidden, bool canTake, bool canSee) {
	this->isHidden = isHidden;
	this->canTake = canTake;
	this->canSee = canSee;
}

Object::Object() {
	setup();
}

Object::Object(string name, string shortDesc, string longDesc, string useDesc, ObjectData* objectData, Object* in_obj, vector<Object*> contains, vector<string> nouns, vector<Description*> descs, map<string, int> specs) {
	setup(name, shortDesc, longDesc, useDesc, objectData, in_obj, contains, nouns, descs, specs);
}

void Object::setup(string name, string shortDesc, string longDesc, string useDesc, ObjectData* objectData, Object* in_obj, vector<Object*> contains, vector<string> nouns, vector<Description*> descs, map<string, int> specs) {
	this->name = name;
	this->shortDesc = shortDesc;
	this->longDesc = longDesc;
	this->useDesc = useDesc;
	this->objectData = objectData;
	this->in_obj = in_obj;
	this->contains = contains;
	this->nouns = nouns;
	this->descs = descs;
	this->specs = specs;
}

void Object::addDesc(Description* desc) {
	this->descs.push_back(desc);
}

Person::Person() {
	setup();
}

Person::Person(string name, vector<string> nouns, string shortDesc, string longDesc, PersonData* personData, vector<Description*> descs, map<string, int> specs) {
	setup(name, nouns, shortDesc, longDesc, personData, descs, specs);
}

void Person::setup(string name, vector<string> nouns, string shortDesc, string longDesc, PersonData* personData, vector<Description*> descs, map<string, int> specs) {
	this->name = name;
	this->nouns = nouns;
	this->shortDesc = shortDesc;
	this->longDesc = longDesc;
	this->personData = personData;
	this->descs = descs;
	this->specs = specs;
}

void Person::addDesc(Description* desc) {
	this->descs.push_back(desc);
}

PersonData::PersonData() {
	setup();
}

PersonData::PersonData(bool isHidden) {
	setup(isHidden);
}

void PersonData::setup(bool isHidden) {
	this->isHidden = isHidden;
}