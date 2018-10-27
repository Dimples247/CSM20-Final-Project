#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define LOG_FOLDER "./Logs"

static class FileUtility {
private:
	static streambuf* oldrdbuf;
	static ofstream logFile;

public:
	static bool IsFile(string _filepath);
	static bool IsDirectory(string _filepath);
	static bool IsEmpty(string _filepath);

	static string GetFileAsString(string _filepath);
	static vector<string> GetFilesInDirectory(string _filepath);

	static void CreateDirectory(string _filepath);
	static void CreateNewLogFile();
	static void CloseLogFile();
};

