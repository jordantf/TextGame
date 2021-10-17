#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <sstream>
#include "structs.h"
using namespace std;

enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3, UP = 4, DOWN = 5 };


class Program {
	public:
		Program();
		void run();
		vector<string> commands;
		std::map<std::string, void (Program::*)(vector<string>)> functionMap;
		map<string, bool> variables;
		vector<Object*> playerInventory;

	private:
		void setupFunctionMap();
		void setupVariables();
		void setupWorld();
		void do_move(vector<string> v);
		string toLower(const string& val);

		Room* m_ptrCurrentRoom;
		bool m_done;
		bool moved;

};