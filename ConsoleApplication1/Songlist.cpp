#include "stdafx.h"
#include "Songlist.h"


Songlist::Songlist(): 
	filelist_(), 
	formattedSonglist_(),
	file_rx_("^([\\s\\S]+?)_([\\s\\S]+?)_([\\s\\S]+.psarc)$")
{
	buildSonglist();
}


Songlist::~Songlist()
{
}

void Songlist::setFilelist(std::vector<std::string> const &files)
{
	filelist_ = files;
}

std::map<std::string, std::string> Songlist::getList() const
{
	return std::map<std::string, std::string>();
}

void Songlist::printSonglistToFile(std::string const &filename) const
{
	std::ofstream file(std::string(filename + ".txt"));
	// Map loop
	for (auto it = formattedSonglist_.begin(); it != formattedSonglist_.end(); it++) {
		// Vector loop
		for (auto &i : it->second) {
			file << it->first + " - " + i << std::endl;
		}
	}
	file.close();
}

void Songlist::buildSonglist()
{
	Song song;
	for (auto &i : filelist_) {
		song=this->parseFilename(i);
		if (song.artist != "" && song.songname != "") {
			this->addSong(song);
		}
	}
}


void Songlist::addSong(Song const &song)
{
	auto iter = formattedSonglist_.find(song.artist);
	if (iter != formattedSonglist_.end()) {
		// Artist in map
		iter->second.emplace_back(song.songname);
	} else {
		// Artist not in map
		formattedSonglist_[song.artist].emplace_back(song.songname);
	}
}

Song Songlist::parseFilename(std::string const &filename) const
{
	std::smatch match;
	Song return_value;
	if (regex_match(filename, match, file_rx_)) {
		return_value.artist = match.str(1);
		removeDashes(return_value.artist);
		return_value.songname = match.str(2);
		removeDashes(return_value.songname);
	}
	return return_value;
}

void Songlist::removeDashes(std::string &str) const
{
	// Removes dashes in bandnames even if not wanted eg. Blink-182.
	replace(str.begin(), str.end(), '-', ' ');
}

bool Songlist::isDuplicate(std::string songname, std::vector<std::string> songvector)
{
	std::string songFromVector;
	removeChar(songname);
	toLowerCase(songname);
	for (auto song : songvector) {
		songFromVector = song;
		removeChar(songFromVector);
		toLowerCase(songFromVector);
		if (songname == songFromVector) {
			return true;
		} else {
			continue;
		}	
	}
	return false;
}

void Songlist::toLowerCase(std::string & str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void Songlist::removeChar(std::string & str, char character)
{
	str.erase(std::remove(str.begin(), str.end(), character), str.end());
}
