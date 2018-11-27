#include "AssetManager.h"

#include <iostream>
#include <chrono>
#include <random>
#include "FileUtility.h"
#include "Regex.h"

unordered_map<string, Asset*> AssetManager::allAssets;
unordered_map<string, int> AssetManager::assetID;

unordered_map<string, Armor*> AssetManager::armorAssets;
unordered_map<string, Consumable*> AssetManager::consumableAssets;
unordered_map<string, Enemy*> AssetManager::enemyAssets;
unordered_map<string, Item*> AssetManager::itemAssets;
unordered_map<string, Location*> AssetManager::locationAssets;
unordered_map<string, NPC*> AssetManager::npcAssets;
unordered_map<string, Player*> AssetManager::playerAssets;
unordered_map<string, Weapon*> AssetManager::weaponAssets;

unordered_map<Asset*, vector<string>> AssetManager::ParseAssets() {
	// Store unliked assets
	unordered_map<Asset*, vector<string>> unlinkedAssets;

	// Check whether the assets folder exists or has files in it
	clog << "MNGR: Begininning asset parsing...\n";
	if (!FileUtility::IsDirectory(ASSETS_FOLDER) || FileUtility::IsEmpty(ASSETS_FOLDER)) {
		clog << "MNGR: The assets folder at '" << ASSETS_FOLDER << "' is empty or does not exist";
		return unlinkedAssets;
	}

	// Loop through each file in the directory
	int id = 0;
	for (string& file : FileUtility::GetFilesInDirectory(ASSETS_FOLDER)) {
		string contents;

		contents = FileUtility::GetFileAsString(file);

		// Check if file is empty
		if (contents == "") {
			clog << "LOAD: The file at '" << file << "' was empty\n";
			continue;
		}

		// Loop through each element in the file
		clog << "LOAD: Parsing file '" << file << "'\n";
		for (string& asset : Regex::AllOccurances(contents, "(<(?:.*?)>(.*\n)*?)<(?:.*?)/>")) {

			vector<string> linkStrings;

			// Get the tag type of the element and convert it to lower case
			string type = Regex::FirstOccurance(asset, "<(.+)>");
			for (char& c : type)
				c = tolower(c);
			clog << "    : Parsing asset of type '" << type << "'\n";

			// Use the tag type to create an object of the correct type
			int typeNum = -1;
			Asset* newAsset = nullptr;
			if (type == "armor") {
				typeNum = 0; // Armor
				newAsset = new Armor();
				((Armor*)newAsset)->amount = stoi(Regex::FirstOccurance(asset, "(?:[aA][mM][oO][uU][nN][tT])(?: )*=(?: )*(\\d*)"));
			} else if (type == "consumable") {
				typeNum = 1; // Consumable
				newAsset = new Consumable();
				((Consumable*)newAsset)->amount = stoi(Regex::FirstOccurance(asset, "(?:[aA][mM][oO][uU][nN][tT])(?: )*=(?: )*(\\d*)"));
			}
			else if (type == "enemy") {
				typeNum = 2; // Enemy
				newAsset = new Enemy();
				((Enemy*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])(?: )*=(?: )*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])(?: )*=(?: )*(.*)\n") + "\n";
				linkStrings.push_back(inventoryAttribute);
				unlinkedAssets[newAsset] = linkStrings;
			} else if (type == "item") {
				typeNum = 3; // Item
				newAsset = new Item();
			} else if (type == "location") {
				typeNum = 4; // Location
				newAsset = new Location();
				string npcsAttribute = Regex::FirstOccurance(asset, "(?:[nN][pP][cC][sS])(?: )*=(?: )*(.*)\n") + "\n";
				linkStrings.push_back(npcsAttribute);
				string enemiesAttribute = Regex::FirstOccurance(asset, "(?:[eE][nN][eE][mM][iI][eE][sS])(?: )*=(?: )*(.*)\n") + "\n";
				linkStrings.push_back(enemiesAttribute);
				string itemsAttribute = Regex::FirstOccurance(asset, "(?:[iI][tT][eE][mM][sS])(?: )*=(?: )*(.*)\n") + "\n";
				linkStrings.push_back(itemsAttribute);
				unlinkedAssets[newAsset] = linkStrings;
			} else if (type == "npc") {
				typeNum = 5; // NPC
				newAsset = new NPC();
				((NPC*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])(?: )*=(?: )*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])(?: )*=(?: )*(.*)\n") + "\n";
				linkStrings.push_back(inventoryAttribute);
				unlinkedAssets[newAsset] = linkStrings;
			} else if (type == "player") {
				typeNum = 6; // Player
				newAsset = new Player();
				((Player*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])(?: )*=(?: )*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])(?: )*=(?: )*(.*)\n") + "\n";
				linkStrings.push_back(inventoryAttribute);
				unlinkedAssets[newAsset] = linkStrings;
			} else if (type == "weapon") {
				typeNum = 7; // Weapon
				newAsset = new Weapon();
				((Weapon*)newAsset)->damage = stoi(Regex::FirstOccurance(asset, "(?:[dD][aA][mM][aA][gG][eE])(?: )*=(?: )*(\\d*)"));
			} else {
				// Unrecognized (just skips the element and moves on)
				clog << "    : Asset was of an unrecognized type. Asset parsing aborted.\n";
				continue;
			}

			// Get the name and description and insert into the asset map

			newAsset->description = Regex::FirstOccurance(asset, "(?:[dD][eE][sS][cC][rR][iI][pP][tT][iI][oO][nN])(?: )*=(?: )*(.*)");
			newAsset->name = Regex::FirstOccurance(asset, "(?:[nN][aA][mM][eE])(?: )*=(?: )*(.*)");
			allAssets[newAsset->name] = newAsset;
			assetID[newAsset->name] = id++;

			switch (typeNum) {
			case 0: // Armor
				armorAssets[newAsset->name] = (Armor*)newAsset;
				break;
			case 1: // Consumable
				consumableAssets[newAsset->name] = (Consumable*)newAsset;
				break;
			case 2: // Enemy
				enemyAssets[newAsset->name] = (Enemy*)newAsset;
				break;
			case 3: // Item
				itemAssets[newAsset->name] = (Item*)newAsset;
				break;
			case 4: // Location
				locationAssets[newAsset->name] = (Location*)newAsset;
				break;
			case 5: // NPC
				npcAssets[newAsset->name] = (NPC*)newAsset;
				break;
			case 6: // Player
				playerAssets[newAsset->name] = (Player*)newAsset;
				break;
			case 7: // Weapon
				weaponAssets[newAsset->name] = (Weapon*)newAsset;
				break;
			}

			clog << "    : Asset '" << newAsset->name << "' parsed. Asset is ID#" << id << "\n";
		}
	}
	return unlinkedAssets;
}
void AssetManager::LinkAssets(unordered_map<Asset*, vector<string>> _unlinkedAssets) {
	clog << "MNGR: Beginning asset linking...\n";

	// Loops through each unlinked asset
	for (pair<Asset*, vector<string>> pair : _unlinkedAssets) {
		clog << "LINK: Linking asset '" << pair.first->name << "'. Asset is ID#" << assetID[pair.first->name] << "\n";

		// Takes an appropriate action based on asset type
		string getType = pair.first->GetAssetType();
		if (getType == "enemy") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*(?:(,|\n))"))) {
				Item i = *((Item*)a);
				((Enemy*)pair.first)->inventory.push_back(i);
			}
		} else if (getType == "location") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*(?:(,|\n))"))) {
				NPC n = *((NPC*)a);
				((Location*)pair.first)->npcs.push_back(n);
			}
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[1], "\\s*(.*?)\\s*(?:(,|\n))"))) {
				Enemy n = *((Enemy*)a);
				((Location*)pair.first)->enemies.push_back(n);
			}
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[2], "\\s*(.*?)\\s*(?:(,|\n))"))) {
				Item i = *((Item*)a);
				((Location*)pair.first)->loot.push_back(i);
			}
		} else if (getType == "npc") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*(?:(,|\n))"))) {
				Item i = *((Item*)a);
				((NPC*)pair.first)->inventory.push_back(i);
			}
		} else if (getType == "player") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*(?:(,|\n))"))) {
				Item i = *((Item*)a);
				((NPC*)pair.first)->inventory.push_back(i);
			}
		} else {
			clog << "    : ERROR: Asset of type '" << getType << "' was not recognized as a linkable type. Asset linking of '" << pair.first->name << "' aborted\n";
			clog << "    : WARNING: The asset is being removed from the asset map\n";
			allAssets.erase(pair.first->name);
		}
	}
}
void AssetManager::LogLoadedAssets() {
	clog << "\n\n    -====-\n Asset Logging\n    -====-\nThe following will be a complete catalog of all loaded assets.\n\n";

	vector<Asset*> allAssets = GetAllAssets();

	int i = 0;
	for (Asset* asset : allAssets) {
		i++;
		clog << "[" << asset->name << "]\n";
		clog << "\tdescription> " << asset->description << "\n";
		clog << "\ttype> " << asset->GetAssetType() << "\n";
		if (asset->GetAssetType() == "armor")
			clog << "\tamount> " << ((Armor*)asset)->amount << "\n";
		if (asset->GetAssetType() == "consumable")
			clog << "\tamount> " << ((Consumable*)asset)->amount << "\n";
		if (asset->GetAssetType() == "enemy") {
			clog << "\thealth> " << ((Enemy*)asset)->health << "\n";
			clog << "\tinventory> ";
			for (Item i : ((Enemy*)asset)->inventory)
				clog << i.name << ", ";
			clog << "\n";
		}
		if (asset->GetAssetType() == "location") {
			clog << "\tnpcs> ";
			for (NPC n : ((Location*)asset)->npcs)
				clog << n.name << ", ";
			clog << "\n\tloot> ";
			for (Item i : ((Location*)asset)->loot)
				clog << i.name << ", ";
			clog << "\n";
		}
		if (asset->GetAssetType() == "npc") {
			clog << "\thealth> " << ((Enemy*)asset)->health << "\n";
			clog << "\tinventory> ";
			for (Item i : ((NPC*)asset)->inventory)
				clog << i.name << ", ";
			clog << "\n";
		}
		if (asset->GetAssetType() == "player") {
			clog << "\thealth> " << ((Player*)asset)->health << "\n";
			clog << "\tinventory> ";
			for (Item i : ((Enemy*)asset)->inventory)
				clog << i.name << ", ";
			clog << "\n";
		}
		if (asset->GetAssetType() == "weapon")
			clog << "\tamount> " << ((Weapon*)asset)->damage << "\n";
	}
	clog << "\n\n-====-\n Done.\n-====-\n\n" << i << " asset(s) were loaded.\n\n";
}
vector<Asset*> AssetManager::ReadSubItems(vector<string> _subItems) {
	vector<Asset*> subAssets;

	// Create a random number generator
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> rng(0, 100);

	for (string subItem : _subItems) {
		// Identify the sub item component and the percent component
		string sub = Regex::FirstOccurance(subItem, "((.*)%|.*)");
		string percent = Regex::FirstOccurance(subItem, "%\\s*(\\d{1,3})");

		// Identify the 'random' function component
		string random = Regex::FirstOccurance(subItem, "[Rr][Aa][Nn][Dd][Oo][Mm]\\s*\\(\\s*(\\w*)\\s*\\)");

		// Process the percent chance if applicable
		int p;
		if (percent == "")
			p = -1;
		else
			p = stoi(percent);

		Asset* assetToAdd;

		if (random == "") {
			Asset* newAsset = nullptr;
			if (allAssets.find(sub) == allAssets.end()) {
				clog << "    : ERROR: The sub item token '" << subItem << "' was not recognized as referenceing a loaded asset. It's linking will be skipped\n";
				continue;
			}

			newAsset = allAssets[sub];
			assetToAdd = newAsset;
		} else {
			// RANDOM FUNCTION CODE
		}

		// Adjusts based on percent probability of spawning as listed in file
		if (p != -1) {
			int r = rng(generator);
			if (r <= p)
				subAssets.push_back(assetToAdd);
		} else {
			subAssets.push_back(assetToAdd);
		}

		clog << "    : The sub item token '" << subItem << "' was successfully linked";
	}

	return subAssets;
}
void AssetManager::ImportAssets() {
	LinkAssets(ParseAssets());
	clog << "MNGR: Transferring to asset logging\n\n\n";
	LogLoadedAssets();
}
vector<Asset*> AssetManager::GetAllAssets() {
	vector<Asset*> assetVector;
	for (pair<string, Asset*> pair : allAssets)
		assetVector.push_back(pair.second);
	return assetVector;
}
int AssetManager::GetAssetID(string _name) {
	if (assetID.find(_name) != assetID.end())
		return assetID[_name];
	return -1;
}