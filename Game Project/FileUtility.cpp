#include "FileUtility.h"

#include <iostream>
#include <filesystem>
#include <fstream>
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
	ifstream file("./Test.txt");
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
	string logNumber = "0";

	// Check if logs folder exists, if not, create it
	if (IsDirectory(LOG_FOLDER)) {
		// If log files already exist, then create a new one with the appropriate file number
		string filepaths;
		for (string s : GetFilesInDirectory(LOG_FOLDER))
			filepaths += s;
		vector<string> logFileNumbers = Regex::AllOccurances(filepaths, "log (\\d+).txt");
		logNumber = (logFileNumbers.size() > 0) ? to_string(stoi(logFileNumbers[logFileNumbers.size() - 1]) + 1) : logNumber;
	} else {
		CreateDirectory(LOG_FOLDER);
	}

	// Open a new log file
	logFile = ofstream(((string)LOG_FOLDER) + "/log " + logNumber + ".txt");

	// Redirect iostream::clog to the log file
	auto old_rdbuf = std::clog.rdbuf();
	std::clog.rdbuf(logFile.rdbuf());
}
void FileUtility::CloseLogFile() {
	std::clog.rdbuf(oldrdbuf);
	logFile.close();
}