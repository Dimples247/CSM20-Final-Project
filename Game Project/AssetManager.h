#pragma once

#include <unordered_map>
#include <vector>
#include "Asset.h"
#include "Armor.h"
#include "Consumable.h"
#include "Enemy.h"
#include "Item.h"
#include "Location.h"
#include "NPC.h"
#include "Player.h"
#include "Weapon.h"

using namespace std;

#define ASSETS_FOLDER "./Assets"

static class AssetManager {
private:
	static unordered_map<string, int> assetID;

	static unordered_map<string, Asset*> allAssets;

	static unordered_map<string, Armor*> armorAssets;
	static unordered_map<string, Consumable*> consumableAssets;
	static unordered_map<string, Enemy*> enemyAssets;
	static unordered_map<string, Item*> itemAssets;
	static unordered_map<string, Location*> locationAssets;
	static unordered_map<string, NPC*> npcAssets;
	static unordered_map<string, Player*> playerAssets;
	static unordered_map<string, Weapon*> weaponAssets;

	static unordered_map<Asset*,vector<string>> ParseAssets();
	static void LinkAssets(unordered_map<Asset*, vector<string>> _unlinkedAssets);
	static void LogLoadedAssets();

	static vector<Asset*> ReadSubItems(vector<string> _subItems);

public:
	static void ImportAssets();

	static vector<Asset*> GetAllAssets();

	static int GetAssetID(string _name);
};

