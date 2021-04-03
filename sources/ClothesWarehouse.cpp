#include "../include/ClothesWarehouse.h"

ClothesWarehouse::ClothesWarehouse(string title, string city, int capacity) : Warehouse(title, city, capacity)
{

}

ClothesWarehouse::ClothesWarehouse(ClothesWarehouse* data) : Warehouse(data)
{
	Stuff = data->Stuff;
}

ClothesWarehouse::ClothesWarehouse(string text)
{
	auto data = Split(text, "#\n");
	{
		auto mainData = Split(data[0], "\n");
		Title = mainData[0];
		City = mainData[1];
		Capacity = stoi(mainData[2]);
		Size = stoi(mainData[3]);
	}
	for (int i = 1; i < data.size(); i++)
	{
		auto sizeData = Split(data[i], "\n");
		auto mainSize = Split(sizeData[0]);
		pair<int, int> size(stoi(mainSize[0]), stoi(mainSize[1]));
		for (int j = 1; j < sizeData.size(); j++)
		{
			auto stuffData = Split(sizeData[j]);
			Stuff[size][stuffData[0]] = stoi(stuffData[1]);
		}
	}
}

void ClothesWarehouse::AddStuff(vector<string> data)
{
	string type = data[0];
	pair<int, int> size(stoi(data[1]), stoi(data[2]));
	int count = stoi(data[3]);

	if (Size + count > Capacity)
		throw "Warehouse is too small for that";
	Stuff[size][type] += count;
	Size += count;
}

void ClothesWarehouse::RemoveStuff(vector<string> data)
{
	string type = data[0];
	pair<int, int> size(stoi(data[1]), stoi(data[2]));
	int count = (data[3] == "all" ? Stuff[size][type] : stoi(data[3])); // Можно передать вместо кол-ва all, удалив все вещи

	if (Stuff[size][type] - count < 0)
		throw "There are not so many things";
	Stuff[size][type] -= count;
	Size -= count;
	// Если вещей 0, то удаляем эти вещи из БД, чтобы не было лишнего
	if (Stuff[size][type] == 0)
	{
		Stuff[size].erase(type);
		if (Stuff[size].size() == 0)
			Stuff.erase(size);
	}
}

bool ClothesWarehouse::HasItems(bool isSmall)
{
	for (auto item : Stuff)
	{
		if (isSmall)
		{
			if (item.first.first < 120 || item.first.second < 40)
				return true;
		}
		else
		{
			if (item.first.first >= 150 || item.first.second >= 50)
				return true;
		}
	}
	return false;
}

string ClothesWarehouse::ToString()
{
	stringstream out;
	out << "C\n";
	out << Title << endl << City << endl << Capacity << endl << Size << endl;
	for (auto i : Stuff)
	{
		out << "#" << endl << i.first.first << " " << i.first.second << endl;
		for (auto j : i.second)
		{
			out << j.first << " " << j.second << endl;
		}
	}
	return out.str();
}

void ClothesWarehouse::Print(std::ostream& out)
{
	out
		<< "Title: " << Title << endl
		<< "Type: Clothes" << endl
		<< "City: " << City << endl
		<< "Capacity: " << Capacity << endl
		<< "Size: " << Size << endl << endl;
	if (Stuff.size() > 0)
		out << "Items:\n\n";
	for (auto i : Stuff)
	{
		out << "Size: " << i.first.first << ", " << i.first.second << endl;
		for (auto j : i.second)
		{
			out << "\tType: " << j.first << "\n\t\tCount: " << j.second << endl;
		}
		out << endl;
	}
}