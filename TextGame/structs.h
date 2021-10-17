#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <sstream>
using namespace std;


struct Exit;
struct Object;
struct Person;

struct Description {
	string name;				// To be used to print what the character looks at
	vector<string> nouns;
	string description;
};

struct RoomData {
	bool isDeathTrap;
	bool isDark;
	int lights;
};

struct Room {
	string name;
	string desc;
	RoomData* roomData;			// Light values, DEATH
	Exit* normalExits[6];		// NESWUD
	vector<Exit*> extraExits;	// for things like 'enter opening'
	vector<Object*> objects;	// list of objects in the room
	vector<Person*> people;		// list of people in the room
	vector<Description*> descs;
	map<string, int> specs;		// Special keywords (int is the special to fire)
};

struct Exit {
	string desc;
	bool isDoor;
	bool isClosed;
	bool isLocked;
	int key_id;					// id of the key used to open this exit (if exit is a locked door)
	vector<string> nouns;		// Keywords with which to refer to this exit (if it is a door)
	Room* to_room;				// The room to which this exit leads
};

struct ObjectData {
	bool isHidden;				// Whether the object is hidden (in the room)
	bool canTake;				// Whether the object can be picked up or not
};

struct Object {
	string name;				// e.g. A steel strongbox
	string shortDesc;			// e.g. A beaten-up steel strongbox is lying here.
	string longDesc;			// Desc when looking at the object
	string useDesc;				// Desc when using the object, e.g. a key to unlock a door
	ObjectData* objectData;		// hidden object, can be picked up, etc.
	Object* in_obj;				// The object this object is inside of (container). NULL if none
	vector<Object*> contains;	// Objects inside of this object (container), empty if none
	vector<string> nouns;		// e.g. strongbox steel box strong beaten up beaten-up
	vector<Description*> descs; // other features of the object, e.g. the teeth of a key
	map<string, int> specs;		// Special keywords (int is the special to fire)
};

struct PersonData {
	bool isHidden;
};

struct Person {
	string name;				// e.g. Kylantha, the grizzled forelady
	string shortDesc;			// e.g. A muscular forelady stands here, overseeing the construction work.
	string longDesc;			// Desc when looking at the person
	PersonData* personData;		// is hidden, etc.
	vector<Description*> descs;	// other features of the person, e.g. a cloak they are wearing
	map<string, int> specs;		// Special keywords (int is the special to fire)
};