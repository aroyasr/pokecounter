/*
* huntinterface.cpp
* AUTHOR: AROHA KIRI 2026
* provides implementations of the huntinterface class.
*
*/

#define MAX_ARGS 10

#include "hunt.h"
#include "files.h"
#include "huntinterface.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cstdlib>


using namespace std;

enum class HuntCommand{
	increment,
	deincrement,
	stop,
	save,
	set,
	help,
	unknown
};

enum class Setting{
	hunt_id,
	name,
	dex_num,
	game,
	encounters,
	odds,
	devices,
	unknown
};


HuntCommand HuntHashCommand(string str)
{
	if (str == "" || str[0] == 'i') return HuntCommand::increment;
	if (str[0] == 'd') return HuntCommand::deincrement;
	if (str == "stop" || str == "quit" || str == "exit") return HuntCommand::stop;
	if (str == "save" || str == "sav") return HuntCommand::save;
	if (str == "set") return HuntCommand::set;
	if (str == "help") return HuntCommand::help;
	return HuntCommand::unknown;
}

Setting SettingHashCommand(string str)
{
	if (str == "hunt_id") return Setting::hunt_id;
	if (str == "name") return Setting::name;
	if (str == "dex_num" || str == "num") return Setting::dex_num;
	if (str == "game") return Setting::game;
	if (str == "encounters") return Setting::encounters;
	if (str == "odds") return Setting::odds;
	if (str == "devices" || str == "increment") return Setting::devices;
	return Setting::unknown;
}

/* pokecounter_signature()
*  This is printed often.
*/
void HuntInterface::pokecounter_signature()
{
	cout << "+--Pokecounter\n+-$  ";
}

/* clear()
* clear the screen
*/
void HuntInterface::clear()
{
	cout << "\033[2J\033[1;1h";
}


/* str_to_uchar(string)
 * converts a string to an unsigned char. used to get hunt_id.
 */
unsigned char HuntInterface::str_to_uchar(string s){
	try{
		int temp = stoi(s);
		if (temp >= 0 && temp <= 255){
			unsigned char result = static_cast<unsigned char>(temp);
			return result;
		} else {
			//cerr<<"pokemon_id provided is out of range\n\n";
			return 255;
		}} catch(const exception&){
			return 255;
		}
}

/* str to int
* must return an int > 0 if successful
* -1 if unsuccessful
*/
int str_to_int(string input)
{
	try{
		int i = stoi(input);
		if (i >= 0){
			return i;
		} else{
			return -1;
		}
	} catch(const exception&){
		return -1;
	}
}


/* sanitize (string)
* turns a string into a vector of tokens.
*/
vector<string> HuntInterface::sanitize(string input)
{
	vector<string> args;
	istringstream iss(input);
	string arg;
	int i = 0;

	while(getline(iss, arg, ' ')) {
		if (!arg.empty()) {
			i++;
			if (i < 2)
				transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
			args.push_back(arg);
		}
	}

	if (args.size() > MAX_ARGS){
		args.resize(MAX_ARGS);
	}

	return args;
}


vector<string> randomMessages = {"Surely this is the one...",
"pls shine", "lets go gambling!", "Pokecounter", "Mew wishes you endless luck.",
"Also try Minecraft!", "NWEN241", "C++ is awesome.", "Sleep is usually better than paralysis for catching Pokemon.",
"Be sure to save your progress!", "If you exit with ctrl + c, your progress won't be saved.",
"A good omen.", "Believe!"};


/* stats (Hunt)
*
*/
void stats(Hunt* h)
{
	int idx = std::rand() & randomMessages.size() -1;
	string message = randomMessages.at(idx);
		cout<<"\n"
"use 'help' for command list.\n"
"						  \n"
+ message + "\n" + 
"⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀	\n"
"⠀⠀⠀⠀⠀⣀⣀⣀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣀⣀⣀⡀⠀⠀⠀⠀	\n"
"⠀⠀⢀⣀⣀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⣀⣀⠀⠀	\n"
"⠀⠀⢸⣿⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀	\n"
"⢀⣀⣸⣿⣿⣿⣿⣀⣀⠀⢀⣀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣀⣀	\n"
"⢸⣿⣿⣿⣿⣿⣿⣿⣿⣀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿	Hunting: " + h->name() + "\n"
"⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿	Playing: " + h->get_game() + "\n"
"⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿	Shiny odds: 1/" + to_string(h->get_odds()) + "\n"
"⢸⣿⣿⣀⣀⣿⣿⣿⣿⣿⣇⣀⣀⣀⣸⣿⣿⣿⣿⣿⣇⣀⣸⣿⣿	Encounters: " + to_string(h->get_reset_count()) +"\n"
"⠀⠀⢸⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⣿⣿⠀⠀⠀⠀⠀⣿⣿⣿⠀⠀		\n"
"⠀⠀⠸⠿⢿⣃⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡿⠿⠿⠀⠀		\n"
"⠀⠀⠀⠀⠀⣿⣿⣿⣿⣀⣀⣀⣀⣀⣀⣀⣸⣿⣿⣿⡇⠀⠀⠀⠀		\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀	\n\n";
}


/* COMMANDS */

void HuntInterface::increment(Hunt* h)
{
	h->increment();
}
void HuntInterface::increment(Hunt* h, int i)
{
	h->increment(i);
}

void HuntInterface::deincrement(Hunt* h)
{
	h->deincrement();
}
void HuntInterface::deincrement(Hunt* h, int i)
{
	h->deincrement(i);
}


void HuntInterface::stop(Hunt* h)
{
	cout << "Would you like to save your progress to disk? (y/n)\n";
	//get input and save or not
}

void HuntInterface::save(Hunt* h)
{
	Files::saveHunt(*h);
}

string HuntInterface::set(Hunt* h, vector<string>* args)
{
	switch (SettingHashCommand(args->at(1))){
		case Setting::hunt_id: {
			unsigned char hunt_id = str_to_uchar(args->at(2));
			if (hunt_id == 255){
				return "Invalid hunt_id!\n";
			}
			h->set_hunt_id(hunt_id);
			break;
		}
		case Setting::name: {
			string name = "";
			for (int i = 2; i < args->size(); i++)
				{ name = name + args->at(i) + " "; }
			h->set_pokemon(name);
			break;
		}
		case Setting::dex_num: {
			int dex_num = str_to_int(args->at(2));
			h->set_pokemon_id(dex_num);
			break;
		}
		case Setting::game: {
			string game = "";
			for (int i = 2; i < args->size(); i++)
				{ game = game + args->at(i) + " ";}
			h->set_game(game);
			break;
		}
		case Setting::encounters: {
			int encounters = str_to_int(args->at(2));
			h->set_reset_count(encounters);
			break;
		}
		case Setting::odds: {
			int odds = str_to_int(args->at(2));
			h->set_odds(odds);
			break;
		}
		case Setting::devices: {
			int devices = str_to_int(args->at(2));
			h->set_increment_num(devices);
			break;
		}
		case Setting::unknown: {
			return "No parameter associated with " + args->at(2);
		}
	}
	return "Set.\n";
}

string HuntInterface::help()
{
		return "Hunt Command List:	\n\
i, increment - Increment the counter by 1.\n\
d, deincrement - Deincrement the counter by 1. \n\
Note: You can add a number argument to i or d. \n\
Note: You can increment without entering anything. \n\
\n\
stop, quit - Stop hunt and return to the main menu. You will be prompted to save first.\n\
save - Save hunt to disk without exiting.\n\
\n\
set <parameter> - set the value of the specified parameter. Must provide a third argument, the value you want to set <parameter> to.\n\
\n\
Parameter list:\n\
<hunt_id> : Number from 0 - 254\n\
<pokemon> : Name of the pokemon\n\
<pokemon_id> : Pokemon dex number\n\
<game> : Name of the game this hunt is in\n\
<encounters> : Number of encounters\n\
<odds> : The odds being reset under. Enter as a whole integer number: Odds for Gens II -> V is 8192, and odds for Gens VI -> onwards is 4096.)\n\
<devices> : The number of devices being used to encounter pokemon. The encounters variable will be increased by <devices> when increment command is ran. Set to 1 by default\n\
";
}

/* END OF COMMANDS */


/* This function is the entry point for the hunt interface.
*  All other functions should be called from here, and this file 
*  should exit from here.
*/
void HuntInterface::start(Hunt* currhunt)
{
	string message;
	clear(); //DEBUG: re add this
	bool isRunning = true;
	while (isRunning){
		string user_input;
		stats(currhunt);
		pokecounter_signature();
		getline(cin, user_input);
		vector<string> args;
		args.clear();
		if (user_input.empty()) {
			args.push_back("i");
		}else{
			args = sanitize(user_input);
		}
		if (args.empty())
			continue;

		message = "nomsg";

		// big ass switch statement for commands
		switch(HuntHashCommand(args.at(0))){
			case HuntCommand::increment:
				if (args.size() > 1){
					int increment_num = str_to_int(args.at(1));
					if (increment_num != -1){
						increment(currhunt, increment_num);
					} else{
						message = "Invalid number\n";
					}
				} else{
					increment(currhunt);
				}
				break;

			case HuntCommand::deincrement:
				if (args.size() > 1){
					int increment_num = str_to_int(args.at(1));
					if (increment_num != -1){
						deincrement(currhunt, increment_num);
					} else{
						message = "Invalid number\n";
					}
				} else{
					deincrement(currhunt);
				}
				break;

			case HuntCommand::stop:
				stop(currhunt);
				isRunning = false;
				break;

			case HuntCommand::save:
				save(currhunt);
				message = "Saved.\n";
				break;

			case HuntCommand::set:
				if (args.size() > 2){
					message = set(currhunt, &args);
					break;
				}
				message = "Not enough arguments provided.\n";
				break;

			case HuntCommand::help:
				message = help();

			case HuntCommand::unknown:
				break;
			default:
				break;
		}
	clear(); 
	if (message != "nomsg")
		cout << message << "";
	}
}
