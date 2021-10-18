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
}


Exit::Exit() {
	setup();
}

Exit::Exit(string desc, string moveDesc, bool isHidden, bool isDoor, bool isClosed, bool isLocked, int key_id, vector<string> nouns, Room* to_room) {
	setup(desc, moveDesc, isHidden, isDoor, isClosed, isLocked, key_id, nouns, to_room);
}

void Exit::setup(string desc, string moveDesc, bool isHidden, bool isDoor, bool isClosed, bool isLocked, int key_id, vector<string> nouns, Room* to_room) {
	this->desc = desc;
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