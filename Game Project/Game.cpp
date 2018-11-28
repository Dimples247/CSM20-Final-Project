#include "Game.h"

#include <iostream>
#include <string>
#include "Regex.h"
#include "AssetManager.h"

void Game::DrawBorder() {

}
vector<string> Game::GetUserInput() {
	string userInput;
	getline(cin, userInput);
	return Regex::AllOccurances(userInput, "(\\w*)*");
}
bool Game::ProcessInput(vector<string> _userInput) {


	return true;
}



void Move() {

}
void Inspect(string _object) {
	cout << AssetManager::allAssets[_object]->description << "\n";
}
void Attack(string _character) {
	Enemy* character = (Enemy*)AssetManager::allAssets[_character];


}
void Consume() {

}
void Equip() {

}
void Unequip() {

}
void Grab() {

}
void Drop() {

}