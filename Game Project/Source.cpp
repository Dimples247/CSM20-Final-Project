#include <iostream>

#include "FileUtility.h"
#include "AssetManager.h"

using namespace std;

int main() {
	FileUtility::CreateNewLogFile();
	AssetManager::ImportAssets();
	FileUtility::CloseLogFile();


}