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
	std::regex file_rx_;
	void addSong(Song const &song);
	Song parseFilename(std::string const &filename) const;
	void removeDashes(std::string &str) const;
	std::vector<std::string> filelist_;
	std::map<std::string, std::vector<std::string>> formattedSonglist_;
};

