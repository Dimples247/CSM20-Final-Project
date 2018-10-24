#pragma once

#include <vector>
#include "NPC.h"
#include "Item.h"

using namespace std;

class Location {
public:
	vector<NPC> npcs;
	vector<Item> loot;
};

