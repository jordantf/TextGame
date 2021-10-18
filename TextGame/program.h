#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <sstream>
#include "structs.h"
using namespace std;

class Program {
	public:
		Program();
		void run();
		vector<string> commands;
		std::map<std::string, void (Program::*)(vector<string>)> functionMap;
		map<string, bool> variables;
		vector<Object*> playerInventory;

	private:
		void setupCommands();
		void setupFunctionMap();
		void setupVariables();
		void setupWorld();
		void ignoreOutput(vector<string> v, int i);
		void parseCommand(string userInput);
		void move(vector<string> v);
		void look(vector<string> v);
		void look_at(string noun);
		void look_in(string noun);
		void scan(vector<string> v);
		void special(vector<string> v, int i);

		// UTIL FUNCTIONS
		int is_abbrev(string str, string substr);
		string toLower(const string& val);

		Room* m_ptrCurrentRoom;
		bool m_done;
		bool moved;

};