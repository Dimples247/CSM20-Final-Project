#pragma once

#include <vector>
#include "Asset.h"
#include "Item.h"

// NOTE: This abstract class has no function definitions, so it has no .cpp file
class Character : public Asset {
public:
	int health = 0;
	vector<Item> inventory;
};

