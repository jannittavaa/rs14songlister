#pragma once
#include <map>
#include <iterator>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>

struct Song {
	std::string artist;
	std::string songname;
};

class Songlist
{
public:
	Songlist();
	~Songlist();
	void setFilelist(std::vector<std::string> const &files);
	std::map<std::string, std::string> getList() const;
	void printSonglistToFile(std::string const &filename) const;
	void buildSonglist();
private:
	Song parseFilename(std::string const &filename) const;
	void addSong(Song const &song);
	void removeDashes(std::string &str) const;
	bool isDuplicate(std::string songname, 
		std::vector<std::string> songvector);
	void toLowerCase(std::string &str);
	void removeChar(std::string &str, char character=' ');

	std::regex file_rx_;
	std::vector<std::string> filelist_;
	std::map<std::string, std::vector<std::string>> formattedSonglist_;
};

