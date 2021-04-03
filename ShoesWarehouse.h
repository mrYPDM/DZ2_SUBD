#pragma once
#include "Warehouse.h"

class ShoesWarehouse : public Warehouse
{
	// Размер - Тип - Кол-во
	map<int, map<string, int>> Stuff;
public:
	ShoesWarehouse(string title, string city, int capacity);

	ShoesWarehouse(string text);

	ShoesWarehouse(ShoesWarehouse* data);

	void AddStuff(vector<string> data) override;

	void RemoveStuff(vector<string> data) override;

	bool HasItems(bool isSmall) override;

	string ToString() override;

	void Print(std::ostream& out = std::cout) override;
};