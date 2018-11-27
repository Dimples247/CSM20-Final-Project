#include "FileUtility.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <time.h>
#include "Regex.h"

using namespace std::experimental;

streambuf* FileUtility::oldrdbuf = std::clog.rdbuf();
ofstream FileUtility::logFile;

bool FileUtility::IsFile(string _filepath) {
	filesystem::path p = _filepath;
	return filesystem::exists(p) && filesystem::is_directory(p);
}
bool FileUtility::IsDirectory(string _filepath) {
	filesystem::path p = _filepath;
	return filesystem::is_directory(p);
}
bool FileUtility::IsEmpty(string _filepath) {
	filesystem::path p = _filepath;
	return filesystem::is_empty(p);
}

string FileUtility::GetFileAsString(string _filepath) {
	string s;
	ifstream file(_filepath);
	while (file.peek() != -1) {
		string line;
		getline(file, line);
		s += line + "\n";
	}
	file.close();
	return s;
}
vector<string> FileUtility::GetFilesInDirectory(string _filepath) {
	vector<string> filepaths;
	for (auto& p : filesystem::directory_iterator(_filepath))
		filepaths.push_back(p.path().string());
	return filepaths;
}


void FileUtility::CreateDirectory(string _filepath) {
	if (!IsDirectory(_filepath))
		filesystem::create_directory(_filepath);
}
void FileUtility::CreateNewLogFile() {
	// Check if logs folder exists, if not, create it
	if (!IsDirectory(LOG_FOLDER)) {
		CreateDirectory(LOG_FOLDER);
	}

	// Get date as char*
	std::time_t rawtime;
	std::tm timeinfo;
	char buffer[80];
	std::time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	std::strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", &timeinfo);

	// Open a new log file
	logFile = ofstream(((string)LOG_FOLDER) + "/log " + buffer + ".txt");

	// Redirect iostream::clog to the log file
	auto old_rdbuf = std::clog.rdbuf();
	std::clog.rdbuf(logFile.rdbuf());
}
void FileUtility::CloseLogFile() {
	std::clog.rdbuf(oldrdbuf);
	logFile.close();
}