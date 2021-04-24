#include "../include/ShoesWarehouse.h"

ShoesWarehouse::ShoesWarehouse(string title, string city, int capacity) : Warehouse(title, city, capacity)
{

}

ShoesWarehouse::ShoesWarehouse(ShoesWarehouse* data) : Warehouse(data)
{
	Stuff = data->Stuff;
}

ShoesWarehouse::ShoesWarehouse(string text)
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
		int size = stoi(sizeData[0]);
		for (int j = 1; j < sizeData.size(); j++)
		{
			auto stuffData = Split(sizeData[j]);
			Stuff[size][stuffData[0]] = stoi(stuffData[1]);
		}
	}
}

void ShoesWarehouse::AddStuff(vector<string> data)
{
	string type = data[0]; int size = stoi(data[1]), count = stoi(data[2]);

	if (Size + count > Capacity)
		throw "Warehouse is too small for that";
	Stuff[size][type] += count;
	Size += count;
}

void ShoesWarehouse::RemoveStuff(vector<string> data)
{
	string type = data[0]; int size = stoi(data[1]), count = (data[2] == "all" ? Stuff[size][type] : stoi(data[2]));

	if (Stuff.find(size) == Stuff.end())
		throw "There are not such things";

	if (Stuff[size][type] - count < 0)
		throw "There are not so many things";

	Stuff[size][type] -= count;
	Size -= count;
	if (Stuff[size][type] == 0)
	{
		Stuff[size].erase(type);
		if (Stuff[size].size() == 0)
			Stuff.erase(size);
	}
}

bool ShoesWarehouse::HasItems(bool isSmall)
{
	for (auto item : Stuff)
	{
		if (isSmall)
		{
			if (item.first < 36)
				return true;
		}
		else
		{
			if (item.first >= 45)
				return true;
		}
	}
	return false;
}

string ShoesWarehouse::ToString()
{
	stringstream out;
	out << "S\n";
	out << Title << endl << City << endl << Capacity << endl << Size << endl;
	for (auto i : Stuff)
	{
		out << "#" << endl << i.first << endl;
		for (auto j : i.second)
		{
			out << j.first << " " << j.second << endl;
		}
	}
	return out.str();
}

void ShoesWarehouse::Print(std::ostream& out)
{
	out
		<< "Title: " << Title << endl
		<< "Type: Shoes" << endl
		<< "City: " << City << endl
		<< "Capacity: " << Capacity << endl
		<< "Size: " << Size << endl << endl;
	if (Stuff.size() > 0)
		out << "Items:\n\n";
	for (auto i : Stuff)
	{
		out << "Size: " << i.first << endl;
		for (auto j : i.second)
		{
			out << "\tType: " << j.first << "\n\t\tCount: " << j.second << endl;
		}
		out << endl;
	}
}