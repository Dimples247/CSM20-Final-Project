#pragma once

#include "Item.h"

class Armor : public Item {
public:
	int amount = 0;

	string GetAssetType();
};

