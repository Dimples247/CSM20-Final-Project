#include <iostream>
#include <conio.h>

#include "FileUtility.h"
#include "AssetManager.h"

#include "Console.h"

using namespace std;

int main() {
	FileUtility::CreateNewLogFile();
	AssetManager::ImportAssets();
	FileUtility::CloseLogFile();


	
	/*string userInput;
	Regex::AllOccurances(userInput, "(\\w*)*");*/

	_getch();
}