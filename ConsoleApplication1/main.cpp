// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileLocator.h"
#include "Songlist.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
	std::cout << "Rocksmith 2014 songlist generator 0.1" << std::endl;
	std::string dummy;
	FileLocator folder;
	Songlist songs;
	songs.setFilelist(folder.getFilenames());
	songs.buildSonglist();
	songs.printSonglistToFile("songs");
	std::getline(std::cin, dummy);
}