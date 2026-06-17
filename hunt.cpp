/*
* hunt.cpp
* AUTHOR: AROHA KIRI 2026
* provides implementations for methods declared in hunt.h.
*
*/

#include <string>

//concatenate pokemon and pokemon_id in format: <pokemon>#<pokemon_id> ex: lugia#249
string Hunt::name()
{
	return pokemon + "#" + pokemon_id;
}

//+increment_num to counter
void Hunt::increment()
{
	increment(increment_num)
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



/* contructors */
Hunt (string pokemon, unsigned int pokemon_id, string game)
{
	pokemon(pokemon); pokemon_id(pokemon_id); game(game);
	reset_count = 0;
	odds = 8192;
	increment_num = 1;
}


Hunt (string pokemon, unsigned int pokemon_id, string game, unsigned int reset_count, unsigned int odds, unsigned int increment_num)
{
	pokemon(pokemon); pokemon_id(pokemon_id); game(game); reset_count(reset_count); odds(odds); increment_num(increment_num);
}