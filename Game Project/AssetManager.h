#pragma once

#include <unordered_map>
#include <vector>
#include "Asset.h"
#include "Armor.h"
#include "Consumable.h"
#include "Item.h"
#include "Location.h"
#include "NPC.h"
#include "Player.h"
#include "Weapon.h"

using namespace std;

#define ASSETS_FOLDER "./Assets"

static class AssetManager {
private:
	static unordered_map<string, Asset*> allAssets;
	/*vector<Armor*> armor;
	vector<Consumable*> consumable;
	vector<Item*> item;
	vector<Location*> location;
	vector<NPC*> npc;
	vector<Player*> player;
	vector<Weapon*> weapon;*/

public:
	static void ImportAssets();
};

