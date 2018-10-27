#pragma once

#include <string>

using namespace std;

// NOTE: This abstract class has no function definitions, so it has no .cpp file
class Asset {
public:
	string name = "";
	string description = "";

	virtual string GetAssetType() = 0;
};

