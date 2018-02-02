#include "stdafx.h"
#include "FileLocator.h"


FileLocator::FileLocator(): 
	path_(fs::current_path()), 
	strPath_("")
{
	if (this->getPathFromReg()) {
		std::cout << "Game found in registry!" << std::endl;
	} else {
		std::cout << "Game not found in registry!" << std::endl;
		std::cout << "Please enter the path of custom songs." << std::endl;
		std::cout << "Leave empty to use executable's current folder." << std::endl;
		std::cout << "Enter path: " << std::endl;
		std::getline(std::cin, strPath_);
		if (strPath_.size() == 0) {
			oss_ << path_;
			strPath_ = oss_.str();
			this->resetSS();
			getPathFromCurrentDir();
		}
	}
}

FileLocator::~FileLocator()
{
}

std::vector<std::string> FileLocator::getFilenames() const
{
	return filenames_;
}

void FileLocator::buildFilenames()
{
	std::cout << "Looking for files in path: " << std::endl;
	std::cout << strPath_ << std::endl;
	std::cout << "Files read:" << std::endl;
	std::string filename;
	std::string psarc_extension;
	for(auto p : fs::directory_iterator(path_)) {
		oss_ << p;
		filename = oss_.str();
		this->resetSS();
		psarc_extension = filename.substr(filename.size() - 6, filename.size());
		std::transform(psarc_extension.begin(), psarc_extension.end(), psarc_extension.begin(), ::tolower);
		if (psarc_extension == ".psarc") {
			filename.erase(0, strPath_.size() + 1);
			std::cout << filename << std::endl;
			filenames_.emplace_back(filename);
		}	
	}
}

void FileLocator::getPathFromCurrentDir(std::string FileExtension)
{
	this->buildFilenames();
}

bool FileLocator::getPathFromReg()
{
	return false;
}

void FileLocator::resetSS()
{
	oss_.str("");
	oss_.clear();
}
