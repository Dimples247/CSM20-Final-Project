#pragma once

#include <vector>
#include "Location.h"

using namespace std;

class Game{
public:
	Location* currentLocation;

	void DrawBorder();
	vector<string> GetUserInput();
	bool ProcessInput(vector<string> _userInput);

	void Move();
	void Inspect(string _object);
	void Attack(string _character);
	void Consume();
	void Equip();
	void Unequip();
	void Grab();
	void Drop();
};

