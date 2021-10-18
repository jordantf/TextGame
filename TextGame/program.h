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
		int is_abbrev(string str, string substr);
		void parseCommand(string userInput);
		void do_move(vector<string> v);
		void scan(vector<string> v);
		string toLower(const string& val);

		Room* m_ptrCurrentRoom;
		bool m_done;
		bool moved;

};