#pragma once

#include "Item.h"

class Consumable : public Item {
public:
	int amount = 0;

	string GetAssetType();
};