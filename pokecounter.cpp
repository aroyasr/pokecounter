/*
* pokecounter.cpp
* AUTHOR: AROHA KIRI 2026
* provides definitions for the hunt class.
*/

#define MAX_ARGS 2

#include "hunt.h"
#include "files.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <limits>
#include <cstdint>

using namespace std;


vector<Hunt> allHunts;

enum class MenuCommand {
	help,
	neww,
	hunts,
	start, 
	deletee,
	settings,
	quit,
	unknown
};

MenuCommand MenuHashCommand(const std::string& str) {
	if (str == "help") return MenuCommand::help;
	if (str == "new") return MenuCommand::neww;
	if (str == "hunts") return MenuCommand::hunts;
	if (str == "start") return MenuCommand::start;
	if (str == "delete") return MenuCommand::deletee;
	if (str == "settings") return MenuCommand::settings;
	if (str == "quit") return MenuCommand::quit;
	return MenuCommand::unknown;
}


void pokecounter_signature(){
	cout << "+--Pokecounter\n+-$  ";
}


void print_intro_msg()
{
	cout<<""
"Mew wishes you endless luck. \nuse 'help' for command list.\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠞⢳⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡔⠋⠀⢰⠎⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⢆⣤⡞⠃⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⢠⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⠀⠀⠀⠀⢀⣀⣾⢳⠀⠀⠀⠀⢸⢠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
"⣀⡤⠴⠊⠉⠀⠀⠈⠳⡀⠀⠀⠘⢎⠢⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀\n"
"⠳⣄⠀⠀⡠⡤⡀⠀⠘⣇⡀⠀⠀⠀⠉⠓⠒⠺⠭⢵⣦⡀⠀⠀⠀\n"
"⠀⢹⡆⠀⢷⡇⠁⠀⠀⣸⠇⠀⠀⠀⠀⠀⢠⢤⠀⠀⠘⢷⣆⡀⠀\n"
"⠀⠀⠘⠒⢤⡄⠖⢾⣭⣤⣄⠀⡔⢢⠀⡀⠎⣸⠀⠀⠀⠀⠹⣿⡀\n"
"⠀⠀⢀⡤⠜⠃⠀⠀⠘⠛⣿⢸⠀⡼⢠⠃⣤⡟⠀⠀⠀⠀⠀⣿⡇\n"
"⠀⠀⠸⠶⠖⢏⠀⠀⢀⡤⠤⠇⣴⠏⡾⢱⡏⠁⠀⠀⠀⠀⢠⣿⠃\n"
"⠀⠀⠀⠀⠀⠈⣇⡀⠿⠀⠀⠀⡽⣰⢶⡼⠇⠀⠀⠀⠀⣠⣿⠟⠀\n"
"⠀⠀⠀⠀⠀⠀⠈⠳⢤⣀⡶⠤⣷⣅⡀⠀⠀⠀⣀⡠⢔⠕⠁⠀⠀\n"
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠫⠿⠿⠿⠛⠋⠁⠀⠀⠀⠀\n";
}


vector<string> sanitize(string input)
{
	vector<string> args;
	istringstream iss(input);
	string arg;

	while(getline(iss, arg, ' ')) {
		if (!arg.empty()) {
			transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
			args.push_back(arg);
		}
	}

	if (args.size() > MAX_ARGS){
		args.resize(MAX_ARGS);
	}

	return args;
}

/** COMMANDS */

void help(){
	cout << "\n\
Command List:	\n\
new - create a new hunt.\n\
hunts - list all hunts saved on disk in the format: [<hunt_id>] [<pokemon>#<pokemon_id>] [<reset_count>]\n\
start <hunt_id> - starts a saved shiny hunt from the list of hunts.\n\
delete <hunt_id> - deletes a saved shiny hunt from disk.\n\
settings - view settings commands.\n\
quit - exit program.\n" << endl;
}

void neww(){
	cout<<"\n\
	Creating a new shiny hunt...\n";

	string pokemon; cout<< "Enter the name of the pokemon to be hunted.\n";
	pokecounter_signature();
	cin >> pokemon;


	bool gotID = false;
	int temp = 0;
	unsigned int pokemon_id;
	while (!gotID){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Enter the ID of the pokemon to be hunted.\n";
		pokecounter_signature();
		if (cin >> temp){
			if (temp < 0){
				cout<<"Negative numbers are not allowed.\n";
			}
			else if (temp > 5000){
				cout<<"I'd like to know what year it is that there are that many pokemon.\n";
			}
			else{
				pokemon_id = static_cast<unsigned int>(temp);
				gotID = true;
			}
		} else {
			// handle non numerical input
			cout <<"Not a number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	string game; cout<< "Enter the game you are hunting in.\n";
	pokecounter_signature();
	cin >> game;


	gotID = false;
	int tempodds; 
	unsigned int odds;
	while (!gotID){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<< "Enter the odds you are resetting under. (Enter as a whole integer number: Odds for Gens II -> V is 8192, and odds for Gens VI -> onwards is 4096.)\n";
		pokecounter_signature();
		if (cin >> tempodds){
			if (tempodds < 0){
				cout<<"Negative numbers are not allowed.\n";
			}
			else if (tempodds > 8192){
				cout<<"Jesus Christ.\n";
				odds = static_cast<unsigned int>(tempodds);
				gotID = true;
			}
			else{
				odds = static_cast<unsigned int>(tempodds);
				gotID = true;
			}
		} else {
			// handle non numerical input
			cout <<"Not a number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	Hunt shinyhunt(static_cast<unsigned char>(allHunts.size()), pokemon, pokemon_id, game);
	shinyhunt.set_odds(odds);
	cout<< "Shiny hunt: \n" << shinyhunt.toString() << endl;
}

/* End of commands */


int main()
{
	print_intro_msg();
	bool running = true;
	while (running)
	{
		pokecounter_signature();
		string user_input;
		cin >> user_input;
		vector<string> args = sanitize(user_input);

		switch(MenuHashCommand(args.at(0))){
			case MenuCommand::help:
				help();
				break;

			case MenuCommand::neww:
				neww();
				break;
			/*
			case MenuCommand::hunts:
				hunts();
				break;
			
			case MenuCommand::start:
				start(args.at(1));
				break;
			
			case MenuCommand::deletee
				deletee(args.at(1));
				break;
			
			case MenuCommand::settings
				settings();
				break;
				*/
			
			case MenuCommand::quit:
				running = false;
				break;
			
			case MenuCommand::unknown:
				cout <<""<< endl;
				break;
			
			default:
				cout <<""<< endl;
				break;
		}
	}
}


