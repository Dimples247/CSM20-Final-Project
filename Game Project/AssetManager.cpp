#include "AssetManager.h"

#include "FileUtility.h"
#include "Regex.h"

void AssetManager::ImportAssets() {
	if (!FileUtility::IsDirectory(ASSETS_FOLDER) || FileUtility::IsEmpty(ASSETS_FOLDER))
		return;
	for (string& file : FileUtility::GetFilesInDirectory(ASSETS_FOLDER)) {
		string contents;
		if (!FileUtility::IsEmpty(file))
			contents = FileUtility::GetFileAsString(file);
		else
			continue;
		for (string& asset : Regex::AllOccurances(contents, "(<(?:.*?)>(.*\n)*?)<(?:.*?)/>")) {
			string type = Regex::FirstOccurance(asset, "<(.+)>");
			for (char& c : type)
				c = tolower(c);
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
			} else if (type == "npc") {
				newAsset = new NPC();
				((NPC*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])\\s*=\\s*(\\d*)"));
			} else if (type == "player") {
				newAsset = new Player();
				((Player*)newAsset)->health = stoi(Regex::FirstOccurance(asset, "(?:[hH][eE][aA][lL][tT][hH])\\s*=\\s*(\\d*)"));
			} else if (type == "weapon") {
				newAsset = new Weapon();
				((Weapon*)newAsset)->damage = stoi(Regex::FirstOccurance(asset, "(?:[dD][aA][mM][aA][gG][eE])\\s*=\\s*(\\d*)"));
			} else
				continue;
			newAsset->description = Regex::FirstOccurance(type, "(?:[dD][eE][sS][cC][rR][iI][pP][tT][iI][oO][nN])\\s*=\\s*(.*)");
			newAsset->name = Regex::FirstOccurance(type, "(?:[nN][aA][mM][eE])\\s*=\\s*(.*)");
			allAssets.insert[newAsset->name] = newAsset;
		}
	}
}