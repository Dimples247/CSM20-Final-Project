#include "Regex.h"

#include <regex>

string Regex::FirstOccurance(string _string, const string& _regex) {
	int parenthesis = (bool)(_regex.find('(') != string::npos);
	regex re(_regex);
	smatch sm;
	regex_search(_string, sm, re);
	return sm.str(parenthesis);
}
vector<string> Regex::AllOccurances(string _string, const string& _regex) {
	int parenthesis = (bool)(_regex.find('(') != string::npos);
	vector<string> matches;
	regex re(_regex);
	smatch sm;
	while (regex_search(_string, sm, re)) {
		matches.push_back(sm.str(parenthesis));
		_string = sm.suffix();
	}
	return matches;
}