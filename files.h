/*
* files.h
* AUTHOR: AROHA KIRI 2026
* provides methods for writing to and from files.
*/

#include <vector>
#include <filesystem>

class Files
{
public:
	static bool saveHunt(Hunt h);
	static Hunt loadHunt(std::filesystem::directory_entry entry);
	static bool loadAllHunts(std::vector<Hunt>* allHunts);

private:
	static std::vector<std::filesystem::directory_entry> entries;
};