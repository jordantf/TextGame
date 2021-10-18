#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <sstream>
#include <windows.h>
using namespace std;

enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3, UP = 4, DOWN = 5 };

struct Exit;
struct Object;
struct Person;

struct Description {
	string name;				// To be used to print what the character looks at
	vector<string> nouns;
	string description;

	Description();
	Description(string name, vector<string> nouns, string description);
	void setup(string name = "", vector<string> nouns = {}, string description = "");
};

struct RoomData {
	bool isDeathTrap;
	bool isDark;
	int lights;

	RoomData();
	RoomData(bool isDeathTrap, bool isDark, int lights);
	void setup(bool isDeathTrap = false, bool isDark = false, int lights = 1);
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

	Room();
	Room(string name, string desc, RoomData* roomData, Exit* normalExits[], vector<Exit*> extraExits, vector<Object*> objects, vector<Person*> people, vector<Description*> descs, map<string, int> specs);
	void setup(string name = "", string desc = "", RoomData* roomData = nullptr, Exit* normalExits[] = { nullptr }, vector<Exit*> extraExits = {}, vector<Object*> objects = {}, vector<Person*> people = {}, vector<Description*> descs = {}, map<string, int> specs = {});
	void color(int color);
	void outputRoomInfo();
	void exitPrompt();
	void showScanDesc(Direction d);
	int canGo(Direction d);
};

struct Exit {
	string desc;				// Message to display when scanning/looking this way
	string moveDesc;			// A message to display when moving this way
	bool isHidden;
	bool isDoor;
	bool isClosed;
	bool isLocked;
	int key_id;					// id of the key used to open this exit (if exit is a locked door)
	vector<string> nouns;		// Keywords with which to refer to this exit (if it is a door)
	Room* to_room;				// The room to which this exit leads

	Exit();
	Exit(string desc, string moveDesc, bool isHidden, bool isDoor, bool isClosed, bool isLocked, int key_id, vector<string> nouns, Room* to_room);
	void setup(string desc = "", string moveDesc = "", bool isHidden = false, bool isDoor = false, bool isClosed = false, bool isLocked = false, int key_id = -1, vector<string> nouns = {}, Room* to_room = nullptr);
	void setDest(Room* room);
};

struct ObjectData {
	bool isHidden;				// Whether the object is hidden (in the room)
	bool canTake;				// Whether the object can be picked up or not

	ObjectData();
	ObjectData(bool isHidden, bool canTake);
	void setup(bool isHidden = false, bool canTake = false);
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

	Object();
	Object(string name, string shortDesc, string longDesc, string useDesc, ObjectData* objectData, Object* in_obj, vector<Object*> contains, vector<string> nouns, vector<Description*> descs, map<string, int> specs);
	void setup(string name = "", string shortDesc = "", string longDesc = "", string useDesc = "", ObjectData* objectData = nullptr, Object* in_obj = nullptr, vector<Object*> contains = {}, vector<string> nouns = {}, vector <Description*> descs = {}, map<string, int> specs = {});
};

struct PersonData {
	bool isHidden;

	PersonData();
	PersonData(bool isHidden);
	void setup(bool isHidden = false);
};

struct Person {
	string name;				// e.g. Kylantha, the grizzled forelady
	string shortDesc;			// e.g. A muscular forelady stands here, overseeing the construction work.
	string longDesc;			// Desc when looking at the person
	PersonData* personData;		// is hidden, etc.
	vector<Description*> descs;	// other features of the person, e.g. a cloak they are wearing
	map<string, int> specs;		// Special keywords (int is the special to fire)

	Person();
	Person(string name, string shortDesc, string longDesc, PersonData* personData, vector<Description*> descs, map<string, int> specs);
	void setup(string name = "", string shortDesc = "", string longDesc = "", PersonData* personData = nullptr, vector<Description*> descs = {}, map<string, int> specs = {});
};