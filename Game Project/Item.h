#pragma once

class Item {
public:
	ItemType type;
	int intensity;
};

enum ItemType {
	Weapon, Potion, Armor
};

