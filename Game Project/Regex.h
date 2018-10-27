#pragma once

#include <vector>
#include <string>

using namespace std;

static class Regex {
public:
	static string FirstOccurance(string _string, const string& _regex);
	static vector<string> AllOccurances(string _string, const string& _regex);
};

