#pragma once

#include "Item.h"

class Weapon : public Item {
public:
	int damage = 0;

	string GetAssetType();
};

