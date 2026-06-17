#include "hunt.h"
#include "files.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

std::vector<fs::directory_entry> Files::entries = {};


bool Files::saveHunt(Hunt h){
  std::ofstream fsOut;
  fsOut.open(h.get_filename(), std::ios::out);
  if (!fsOut.is_open()){
  	std::cerr<<"Failed to save to file";
  	return false;
  }
  if (fsOut){
  	fsOut << h.fileString(); // write object to file
  }
  fsOut.close();
  return true;
}

Hunt Files::loadHunt(std::filesystem::directory_entry entry){

	std::ifstream fsIn;
	fsIn.open(entry.path(), std::ios::in);
	if (!fsIn.is_open()){
		std::cerr<<"Failed to open file";
	}
	
	std::string line;
	try{
		unsigned char hunt_id;
		std::string pokemon;
		unsigned int pokemon_id;
		std::string game;
		unsigned int reset_count;
		unsigned int odds;
		unsigned int increment_num;
		// hunt_id
		if (std::getline(fsIn, line)) {
			int tempint = std::stoi(line);

			if (tempint < 0 || tempint > 255){
				throw std::out_of_range("hunt_id value read from file is out of bounds.");
			}

			hunt_id = static_cast<unsigned char>(tempint);
		}
		//pokemon
		if (std::getline(fsIn, line)) {
			pokemon = line;
		}
		//pokemon_id
		if (std::getline(fsIn, line)) {
			pokemon_id = std::stoi(line);
		}
		//game
		if (std::getline(fsIn, line)) {
			game = line;
		}
		//reset_count
		if (std::getline(fsIn, line)) {
			reset_count = std::stoi(line);
		}
		//odds
		if (std::getline(fsIn, line)) {
			odds = std::stoi(line);
		}
		//increment_num
		if (std::getline(fsIn, line)) {
			increment_num = std::stoi(line);
		}
		fsIn.close();
		return Hunt(hunt_id, pokemon, pokemon_id, game, 
					reset_count, odds, increment_num);
	} catch (const std::invalid_argument& e) {
		std::cerr << "Data conversion error. Invalid argument found in file.";
	} catch (const std::out_of_range& e){
		std::cerr << "Data conversion error. hunt_id value read from file is invalid.";
	}
	fsIn.close();
	std::cerr << "You shouldn't see this error... one of your files is fucked pretty bad.";
}


bool Files::loadAllHunts(std::vector<Hunt>* allHunts){
	entries.clear();
	std::string path = fs::current_path();
	for (fs::directory_entry entry : fs::directory_iterator(path)){
		if (entry.is_regular_file()){
			if (entry.path().extension() == ".lucky"){
				entries.push_back(entry);
				std::cout << entry.path() << std::endl;
			}
		}
	}

	for (fs::directory_entry entry : entries){
		try{
			allHunts->push_back(loadHunt(entry));
		} catch(const std::exception& e){
			std::cerr << "exception in file: "<< entry.path() << e.what()<< std::endl;
		}
	}

	return true;
}