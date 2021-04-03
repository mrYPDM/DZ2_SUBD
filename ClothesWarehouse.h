#pragma once
#include "Warehouse.h"

class ClothesWarehouse : public Warehouse
{
	// Рост - Размер - Тип - Кол-во
	map<pair<int, int>, map<string, int>> Stuff;
public:
	ClothesWarehouse(string title, string city, int capacity);
	
	ClothesWarehouse(ClothesWarehouse* data);

	ClothesWarehouse(string text);

	void AddStuff(vector<string> data) override;

	void RemoveStuff(vector<string> data) override;

	bool HasItems(bool isSmall) override;

	string ToString() override;

	void Print(std::ostream& out = std::cout) override;
};

