#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>
namespace fs = std::experimental::filesystem;
class FileLocator
{
public:
	FileLocator();
	~FileLocator();
	std::vector<std::string> getFilenames() const;
private:
	void buildFilenames();
	void getPathFromCurrentDir(std::string FileExtension = ".psarc");
	// Avain?
	bool getPathFromReg();
	void resetSS();

	std::string strPath_;
	fs::path path_;
	std::vector<std::string> filenames_;
	std::ostringstream oss_;
};