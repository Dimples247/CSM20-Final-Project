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
	static unordered_map<string, int> assetID;

	static unordered_map<Asset*,vector<string>> ParseAssets();
	static void LinkAssets(unordered_map<Asset*, vector<string>> _unlinkedAssets);

	static vector<Asset*> ReadSubItems(vector<string> _subItems);

public:
	static void ImportAssets();

	static vector<Asset*> GetAllAssets();

	static int GetAssetID(string _name);
};

