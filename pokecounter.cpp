/*
* pokecounter.cpp
* AUTHOR: AROHA KIRI 2026
* This file acts as the main program.
* 
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

/* MenuHashCommand(str)
*  for easily converting a string into a MenuCommand enum.
*/
MenuCommand MenuHashCommand(const std::string& str) 
{
	if (str == "help") return MenuCommand::help;
	if (str == "new") return MenuCommand::neww;
	if (str == "hunts" || str == "ls") return MenuCommand::hunts;
	if (str == "start") return MenuCommand::start;
	if (str == "delete") return MenuCommand::deletee;
	if (str == "settings") return MenuCommand::settings;
	if (str == "quit") return MenuCommand::quit;
	return MenuCommand::unknown;
}


/* pokecounter_signature()
*  This is printed often.
*/
void pokecounter_signature()
{
	cout << "+--Pokecounter\n+-$  ";
}


/* print_intro_msg()
*  ran at beginning of program or when user goes back to 
*  the main menu environment.
*/
void print_intro_msg()
{
	cout<<"\n"
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


/* sanitize (string)
* turns a string into a vector of tokens.
*/
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
// The command functions are called by the main loop when the user
// types the corresponding input. All commands are listed at the
// top of this file in the enum class and in the readme.

/* help()
*  the help command.
*/
void help()
{
	cout << "Command List:	\n\
new - create a new hunt.\n\
hunts - list all hunts saved on disk in the format: [<hunt_id>] [<pokemon>#<pokemon_id>] [<encounter_count>]\n\
start <id> - starts a saved shiny hunt from the list of hunts.\n\
delete <id> - deletes a saved shiny hunt from disk.\n\
settings - view settings commands.\n\
quit - exit program.\n" << endl;
}


/* neww()
* Creates a new hunt object and saves it as a file.
* Asks the user questions for needed data.
*/
void neww()
{
	cout<<"Creating a new shiny hunt...\n";

	string pokemon; cout<< "Enter the name of the pokemon to be hunted.\n\n";
	pokecounter_signature();
	cin >> pokemon;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	bool gotID = false;
	int temp = 0;
	unsigned int pokemon_id;
	while (!gotID){
		cout<<"Enter the ID of the pokemon to be hunted.\n\n";
		pokecounter_signature();

		if (cin >> temp){
			if (temp < 0){
				cout<<"Negative numbers are not allowed.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			continue;
		}
	}

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string game; cout<< "Enter the game you are hunting in.\n\n";
	pokecounter_signature();
	getline(cin, game);

	gotID = false;
	int tempodds; 
	unsigned int odds;
	while (!gotID){
		cout<< "Enter the odds you are hunting on. (Enter as a whole integer number: Odds for Gens II -> V is 8192, and odds for Gens VI -> onwards is 4096.)\n\n";
		pokecounter_signature();
		
		if (cin >> tempodds){
			if (tempodds < 0){
				cout<<"Negative numbers are not allowed.\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else{
				if (tempodds > 8192) cout<<"Jesus Christ.\n";
				odds = static_cast<unsigned int>(tempodds);
				gotID = true;
			}
		} else {
			// handle non numerical input
			cout <<"Not a number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	}

	Hunt shinyhunt(static_cast<unsigned char>(allHunts.size()), pokemon, pokemon_id, game);
	shinyhunt.set_odds(odds);
	Files::saveHunt(shinyhunt);
	cout<<"Created.\n\n";

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


/* hunts()
*  prints the vector allHunts.
*/
void hunts()
{
	for (Hunt h: allHunts){
		cout << h.toString() << endl;
	}
	cout << "\n";
}

void start(string pokemon_id)
{
	cout << "Haven't done this part yet. The most useful part...\n\n";
}


bool deletee(string pokemon_id)
{
	Files::loadAllHunts(&allHunts);
	int temp = stoi(pokemon_id);
	bool result;
	if (temp >= 0 && temp <= 255){
		result = Files::deleteHunt(static_cast<unsigned char>(temp));
	} else {
		cerr<<"pokemon_id provided is out of range\n\n";
	}
	Files::loadAllHunts(&allHunts);
	return result;
}


void settings()
{
	cout<<"Settings commands:\n";
}


/* End of commands */


/* main()
* The main loop.
*/
int main()
{
	Files::loadAllHunts(&allHunts);
	print_intro_msg();
	bool running = true;

	// the big loop
	while (running)
	{
		cout <<""<< endl;
		string user_input;
		pokecounter_signature();
		getline(cin, user_input);

		if (user_input.empty()) continue;

		vector<string> args = sanitize(user_input);

		if (args.empty())
			continue;

		// big ass switch statement for commands
		switch(MenuHashCommand(args.at(0))){
			case MenuCommand::help:
				help();
				break;

			case MenuCommand::neww:
				neww();
				Files::loadAllHunts(&allHunts);
				break;
			
			case MenuCommand::hunts:
				hunts();
				break;
			
			case MenuCommand::start:
				start(args.at(1));
				break;
			
			case MenuCommand::deletee:
				if (args.size() == 1){
					cout<<"Not enough arguments provided.\n";
					break;
				}
				deletee(args.at(1));
				break;
			
			case MenuCommand::settings:
				settings();
				break;
				
			case MenuCommand::quit:
				running = false;
				break;
			

			case MenuCommand::unknown:
				break;
			default:
				break;
		}
	}
}


