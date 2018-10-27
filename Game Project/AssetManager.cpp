#include "AssetManager.h"

#include <iostream>
#include "FileUtility.h"
#include "Regex.h"

unordered_map<string, Asset*> AssetManager::allAssets;

void AssetManager::ImportAssets() {
	clog << "MNGR: Begininning asset parsing...\n";
	if (!FileUtility::IsDirectory(ASSETS_FOLDER) || FileUtility::IsEmpty(ASSETS_FOLDER)) {
		clog << "MNGR: The assets folder at '" << ASSETS_FOLDER << "' is empty or does not exist";
		return;
	}
	unordered_map<Asset*, vector<string>> unlinkedAssetsNpcs;
	unordered_map<Asset*, vector<string>> unlinkedAssetsItems;
	unordered_map<Asset*, vector<string>> unlinkedAssetsInventory;
	for (string& file : FileUtility::GetFilesInDirectory(ASSETS_FOLDER)) {
		string contents;
		if (!FileUtility::IsEmpty(file))
			contents = FileUtility::GetFileAsString(file);
		else
			continue;
		clog << "LOAD: Parsing file " << file << "\n";
		for (string& asset : Regex::AllOccurances(contents, "(<(?:.*?)>(.*\n)*?)<(?:.*?)/>")) {
			string type = Regex::FirstOccurance(asset, "<(.+)>");
			for (char& c : type)
				c = tolower(c);
			clog << "    : Parsing asset '" << type << "'\n";
			Asset* newAsset = nullptr;
			if (type == "armor") {
				newAsset = new Armor();
				((Armor*)newAsset)->amount = stoi(Regex::FirstOccurance(asset, "(?:[aA][mM][oO][uU][nN][tT])\\s*=\\s*(\\d*)"));
			} else if (type == "consumable") {
				newAsset = new Consumable();
				((Consumable*)newAsset)->amount = stoi(Regex::FirstOccurance(asset, "(?:[aA][mM][oO][uU][nN][tT])\\s*=\\s*(\\d*)"));
			} else if (type == "item") {
				newAsset = new Item();
			} else if (type == "location") {
				newAsset = new Location();
				string npcsAttribute = Regex::FirstOccurance(asset, "(?:[nN][pP][cC][sS])\\s*=\\s*(.*)\n");
				unlinkedAssetsNpcs[newAsset] = Regex::AllOccurances(npcsAttribute, "\\[(.*?)\\]");
				string itemsAttribute = Regex::FirstOccurance(asset, "(?:[iI][tT][eE][mM][sS])\\s*=\\s*(.*)\n");
				unlinkedAssetsItems[newAsset] = Regex::AllOccurances(itemsAttribute, "\\[(.*?)\\]");
			} else if (type == "npc") {
				newAsset = new NPC();
				((NPC*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])\\s*=\\s*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])\\s*=\\s*(.*)\n");
				unlinkedAssetsInventory[newAsset] = Regex::AllOccurances(inventoryAttribute, "\\[(.*?)\\]");
			} else if (type == "player") {
				newAsset = new Player();
				((Player*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])\\s*=\\s*(\\d*)"));
				string inventoryAttribute = Regex::FirstOccurance(asset, "(?:[iI][nN][vV][eE][nN][tT][oO][rR][yY])\\s*=\\s*(.*)\n");
				unlinkedAssetsInventory[newAsset] = Regex::AllOccurances(inventoryAttribute, "\\[(.*?)\\]");
			} else if (type == "weapon") {
				newAsset = new Weapon();
				((Weapon*)newAsset)->damage = stoi(Regex::FirstOccurance(asset, "(?:[dD][aA][mM][aA][gG][eE])\\s*=\\s*(\\d*)"));
			} else
				continue;
			clog << "    : Asset parsed.\n";
			newAsset->description = Regex::FirstOccurance(type, "(?:[dD][eE][sS][cC][rR][iI][pP][tT][iI][oO][nN])\\s*=\\s*(.*)");
			newAsset->name = Regex::FirstOccurance(type, "(?:[nN][aA][mM][eE])\\s*=\\s*(.*)");
			allAssets.insert[newAsset->name] = newAsset;


		}
	}
}