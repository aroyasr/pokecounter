/*
* hunt.cpp
* AUTHOR: AROHA KIRI 2026
* provides implementations for methods declared in hunt.h.
*/

#define DEFAULT_ODDS 8192
#define DEFAULT_INCREMENT_NUM 1
#define DEFAULT_RESET_COUNT 0
#define FILE_EXT ".lucky"

#include "hunt.h"
#include <string>


// tostring method.
std::string Hunt::toString()
{
	if (increment_num > 1){
		return "[id: " + std::to_string(static_cast<int>(hunt_id)) + "] [" + name() + ", Game: " + game + ", Resets: " + std::to_string(reset_count) + ", Odds: 1/" + std::to_string(odds) + ", Devies: " + std::to_string(increment_num) + "]";
	}
	else{
		return "[id: " + std::to_string(static_cast<int>(hunt_id)) + "] [" + name() + ", Game: " + game + ", Resets: " + std::to_string(reset_count) + ", Odds: 1/" + std::to_string(odds) + "]";
	}
}


//concatenate pokemon and pokemon_id in format: <pokemon>#<pokemon_id> ex: lugia#249
std::string Hunt::name()
{
	return pokemon + "#" + std::to_string(pokemon_id);
}


//+increment_num to counter
void Hunt::increment()
{
	increment(increment_num);
}


//+int to counter		
void Hunt::increment(unsigned int x)
{
	reset_count += x;
}


//-increment_num to counter
void Hunt::deincrement()
{
	deincrement(increment_num);
}


//-int to counter
void Hunt::deincrement(unsigned int x)
{
	if (reset_count - x < 0) { 
		reset_count = 0;
		return;
	}
	reset_count -= x;
}

std::string Hunt::fileString()
{
	return std::to_string(hunt_id) + "\n" +
	pokemon + "\n" + std::to_string(pokemon_id) + "\n" +
	game + "\n" + std::to_string(reset_count) + "\n" +
	std::to_string(odds) + "\n" + std::to_string(increment_num);
}

void Hunt::set_filename()
{
	filename = std::to_string(hunt_id) + FILE_EXT;
}


/* contructors */
Hunt::Hunt (unsigned char hunt_id, std::string pokemon, unsigned int pokemon_id, 
	std::string game)
{
	this->hunt_id = hunt_id; this->pokemon = pokemon; this->pokemon_id = pokemon_id; this->game = game;
	this->reset_count = DEFAULT_RESET_COUNT;
	this->odds = DEFAULT_ODDS;
	this->increment_num = DEFAULT_INCREMENT_NUM;
	set_filename();
}


Hunt::Hunt (unsigned char hunt_id, std::string pokemon, unsigned int pokemon_id, 
	std::string game, unsigned int reset_count, unsigned int odds, unsigned int increment_num)
{
	this->hunt_id = hunt_id; 
	this->pokemon = pokemon; 
	this->pokemon_id = pokemon_id; 
	this->game = game; 
	this->reset_count = reset_count; 
	this->odds = odds; 
	this->increment_num = increment_num;
	set_filename();
}