#include <iostream>
#include <conio.h>

#include "FileUtility.h"
#include "AssetManager.h"

using namespace std;

int main() {
	FileUtility::CreateNewLogFile();
	AssetManager::ImportAssets();
	FileUtility::CloseLogFile();

	vector<Asset*> allAssets = AssetManager::GetAllAssets();

	int i = 0;
	for (Asset* asset : allAssets) {
		i++;
		cout << "[" << asset->name << "]\n";
		cout << "\tdescription> " << asset->description << "\n";
		cout << "\ttype> " << asset->GetAssetType() << "\n";
		if (asset->GetAssetType() == "armor")
			cout << "\tamount> " << ((Armor*)asset)->amount << "\n";
	}
	cout << "\n\n-====-\n Done.\n-====-\n\n" << i << " asset(s) were loaded.\n\nPress any key to exit...";
	
	_getch();
}