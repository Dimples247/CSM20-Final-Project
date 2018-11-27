#pragma once

#include <vector>
#include "Asset.h"
#include "NPC.h"
#include "Item.h"

using namespace std;

class Location : public Asset {
public:
	vector<NPC> npcs;
	vector<Enemy> enemies;
	vector<Item> loot;

	string GetAssetType();
};

