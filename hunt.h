/*
* hunt.h
* AUTHOR: AROHA KIRI 2026
* provides definitions for the hunt class.
* The hunt class contains fields for all information related to a specific shiny hunt.
*/

#include <string>

class Hunt
{
public:
	/* getters */
	inline unsigned char get_hunt_id() 			{ return hunt_id; }
	inline std::string get_pokemon() 			{ return pokemon; }
	inline unsigned int get_pokemon_id() 		{ return pokemon_id; }
	inline std::string get_game() 				{ return game; }
	inline unsigned int  get_reset_count() 		{ return reset_count; }
	inline unsigned int get_odds() 				{ return odds; }
	inline std::string get_filename()			{ return filename; }


	/* setters */
	bool set_hunt_id(unsigned char c);
	inline void set_pokemon(std::string s)				{pokemon = s;}
	inline void set_pokemon_id(unsigned int x)			{pokemon_id = x;}
	inline void set_game(std::string s)					{game = s;}
	inline void set_reset_count(unsigned int x)			{reset_count = x;}
	inline void set_odds(unsigned int x)				{odds = x;}
	inline void set_increment_num(unsigned int x)		{increment_num = x;}

	/* methods */
	std::string name();			//concatenate pokemon and pokemon_id in format: <pokemon>#<pokemon_id> ex: lugia#249
	void increment(); 		//+increment_num to counter
	void increment(unsigned int); 	//+int to counter
	void deincrement(); 	//-increment_num to counter
	void deincrement(unsigned int);	//-int to counter
	std::string fileString(); //for writing to files
	std::string toString();	  //used by 'hunts' command

	/* contructor */
	Hunt (unsigned char hunt_id, std::string pokemon, unsigned int pokemon_id, std::string game);
	Hunt (unsigned char hunt_id, std::string pokemon, unsigned int pokemon_id, std::string game, unsigned int reset_count, unsigned int odds, unsigned int increment_num);

private:
	unsigned char hunt_id; // you shouldnt have more than 255 hunts anyway
	std::string pokemon; 
	unsigned int pokemon_id;
	std::string game;
	unsigned int reset_count;
	unsigned int odds;
	unsigned int increment_num; // for those with like 5 gameboy advances [ im jealous :( ]

	/*no setters only getters for filename. updated if hunt_id changes, 
	in which case the old file will be delted and a new file will be created.
	The user should never have to mess with filenames.*/
	void set_filename();
	std::string filename; 
};
