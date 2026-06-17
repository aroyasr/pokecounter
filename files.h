/*
* files.h
* AUTHOR: AROHA KIRI 2026
* provides declarations for functions that write to and from files.
*/

#include <vector>
#include <filesystem>

class Files
{
public:
	static bool saveHunt(Hunt h);
	static Hunt loadHunt(std::filesystem::directory_entry entry);
	static bool loadAllHunts(std::vector<Hunt>* allHunts);
	static bool deleteHunt(unsigned char pokemon_id);

private:
	static std::vector<std::filesystem::directory_entry> entries;
};