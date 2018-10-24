#pragma once

#include <vector>
#include "Item.h"

using namespace std;

class Player {
public:
	int health;

	vector<Item> inventory;
};

