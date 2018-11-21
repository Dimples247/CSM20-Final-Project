#include "AssetManager.h"

#include <iostream>
#include "FileUtility.h"
#include "Regex.h"

unordered_map<string, Asset*> AssetManager::allAssets;
unordered_map<string, int> AssetManager::assetID;

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

		vector<string> linkStrings;

		// Loop through each element in the file
		clog << "LOAD: Parsing file '" << file << "'\n";
		for (string& asset : Regex::AllOccurances(contents, "(<(?:.*?)>(.*\n)*?)<(?:.*?)/>")) {
			// Get the tag type of the element and convert it to lower case
			string type = Regex::FirstOccurance(asset, "<(.+)>");
			for (char& c : type)
				c = tolower(c);
			clog << "    : Parsing asset of type '" << type << "'\n";

			// Use the tag type to create an object of the correct type
			Asset* newAsset = nullptr;
			if (type == "armor") {
				// Armor
				newAsset = new Armor();
				((Armor*)newAsset)->amount = stoi(Regex::FirstOccurance(asset, "(?:[aA][mM][oO][uU][nN][tT])\\s*=\\s*(\\d*)"));
			} else if (type == "consumable") {
				// Consumable
				newAsset = new Consumable();
				((Consumable*)newAsset)->amount = stoi(Regex::FirstOccurance(asset, "(?:[aA][mM][oO][uU][nN][tT])\\s*=\\s*(\\d*)"));
			} else if (type == "item") {
				// Item
				newAsset = new Item();
			} else if (type == "location") {
				// Location
				newAsset = new Location();
				string npcsAttribute = Regex::FirstOccurance(asset, "(?:[nN][pP][cC][sS])\\s*=\\s*(.*)\n");
				if (npcsAttribute != "")
					linkStrings.push_back(npcsAttribute);
				string itemsAttribute = Regex::FirstOccurance(asset, "(?:[iI][tT][eE][mM][sS])\\s*=\\s*(.*)\n");
				if (itemsAttribute != "")
					linkStrings.push_back(itemsAttribute);
				unlinkedAssets[newAsset] = linkStrings;
			} else if (type == "npc") {
				// NPC
				newAsset = new NPC();
				((NPC*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])\\s*=\\s*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])\\s*=\\s*(.*)\n");
				if (inventoryAttribute != "")
					linkStrings.push_back(inventoryAttribute);
			} else if (type == "player") {
				// Player
				newAsset = new Player();
				((Player*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])\\s*=\\s*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])\\s*=\\s*(.*)\n");
				if (inventoryAttribute != "")
					linkStrings.push_back(inventoryAttribute);
			} else if (type == "weapon") {
				// Weapon
				newAsset = new Weapon();
				((Weapon*)newAsset)->damage = stoi(Regex::FirstOccurance(asset, "(?:[dD][aA][mM][aA][gG][eE])\\s*=\\s*(\\d*)"));
			} else {
				// Unrecognized (just skips the element and moves on)
				clog << "    : Asset was of an unrecognized type. Asset parsing aborted.\n";
				continue;
			}

			// Get the name and description and insert into the asset map

			newAsset->description = Regex::FirstOccurance(asset, "(?:[dD][eE][sS][cC][rR][iI][pP][tT][iI][oO][nN])\\s*=\\s*(.*)");
			newAsset->name = Regex::FirstOccurance(asset, "(?:[nN][aA][mM][eE])\\s*=\\s*(.*)");
			allAssets[newAsset->name] = newAsset;
			assetID[newAsset->name] = id++;

			clog << "    : Asset '" << newAsset->name << "' parsed. Asset is ID#" << id << "\n";
		}
	}
	return unlinkedAssets;
}
void AssetManager::LinkAssets(unordered_map<Asset*, vector<string>> _unlinkedAssets) {
	clog << "MNGR: Beginning asset linking...\n";

	for (pair<Asset*, vector<string>> pair : _unlinkedAssets) {
		clog << "LINK: Linking asset '" << pair.first->name << "'. Asset is ID#" << assetID[pair.first->name] << "\n";

		string getType = pair.first->GetAssetType();
		if (getType == "location") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*,"))) {
				NPC n = *((NPC*)a);
				((Location*)pair.first)->npcs.push_back(n);
			}
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[1], "\\s*(.*?)\\s*,"))) {
				Item i = *((Item*)a);
				((Location*)pair.first)->loot.push_back(i);
			}
		} else if (getType == "npc") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*,"))) {
				Item i = *((Item*)a);
				((NPC*)pair.first)->inventory.push_back(i);
			}
		} else if (getType == "player") {
			for (Asset* a : ReadSubItems(Regex::AllOccurances(pair.second[0], "\\s*(.*?)\\s*,"))) {
				Item i = *((Item*)a);
				((NPC*)pair.first)->inventory.push_back(i);
			}
		} else {
			clog << "    : ERROR: Asset of type '" << getType << "' was not recognized as a linkable type. Asset linking of '" << pair.first->name << "' skipped\n";
		}
	}
}
vector<Asset*> AssetManager::ReadSubItems(vector<string> _subItems) {
	return vector<Asset*>();
}
void AssetManager::ImportAssets() {
	ParseAssets();
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