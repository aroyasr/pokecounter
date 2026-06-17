/*
* hunt.h
* AUTHOR: AROHA KIRI 2026
* provides definitions for the hunt class.
*
*/

#include <string>

class Hunt
{
public:
	/* getters */
	inline unsigned char hunt_id() 			{ return hunt_id; }
	inline string pokemon() 				{ return pokemon; }
	inline unsigned int pokemon_id() 		{ return pokemon_id; }
	inline string game() 					{ return game; }
	inline unsigned int  reset_count() 		{ return reset_count; }
	inline unsigned int odds() 				{ return odds; }
	inline string filename()				{ return filename; }


	/* setters */
	inline void hunt_id(unsigned char c)  			{hunt_id = c;}
	inline void pokemon(string s)					{pokemon = s;}
	inline void pokemon_id(unsigned int x)			{pokemon_id = x;}
	inline void game(string s)						{game = s;}
	inline void reset_count(unsigned int x)			{reset_count = x;}
	inline void odds(unsigned int x)				{odds = x;}
	inline void increment_num(unsigned int x)		{increment_num = x;}

	/* methods */
	string name();			//concatenate pokemon and pokemon_id in format: <pokemon>#<pokemon_id> ex: lugia#249
	void increment(); 		//+increment_num to counter
	void increment(unsigned int); 	//+int to counter
	void deincrement(); 	//-increment_num to counter
	void deincrement(unsigned int);	//-int to counter

	/* contructor */
	Hunt (string pokemon, unsigned int pokemon_id, string game);
	Hunt (string pokemon, unsigned int pokemon_id, string game, unsigned int reset_count, unsigned int odds, unsigned int increment_num);

private:
	unsigned char hunt_id; // you shouldnt have more than 255 hunts, you greedy bitch!
	string pokemon; 
	unsigned int pokemon_id;
	string game;
	unsigned int reset_count;
	unsigned int odds;
	unsigned int increment_num; // for those greedy fuckers with like 5 gameboy advances [ im jealous :( ]

	/*no setters only getters for filename. updated if hunt_id changes, 
	in which case the old file will be delted and a new file will be created.
	The user should never have to mess with filenames.*/
	string filename; 
}