/*
* huntinterface.h
* AUTHOR: AROHA KIRI 2026
* provides definitions for the huntinterface class.
* 
*/

#include <vector>
#include <string>

class HuntInterface{
public:
	static void pokecounter_signature(); //prints the pokecounter sig
	static void start(Hunt* h); //starts a hunt- essentially the main of huntinterface
	static std::vector<std::string> sanitize(std::string input); //string->vector seperated by space
	static void clear(); //clear the screen
	static unsigned char str_to_uchar(std::string s);

private:
	static void increment(Hunt* h);
	static void increment(Hunt* h, int i);
	static void deincrement(Hunt* h);
	static void deincrement(Hunt* h, int i);
	static void stop(Hunt* h);
	static void save(Hunt* h);
	static std::string set(Hunt* h, std::vector<std::string>* args);
	static std::string help();
};
