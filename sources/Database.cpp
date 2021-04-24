#include "../include/Database.h"

bool Database::sortbyname(Warehouse* lhs, Warehouse* rhs)
{
	return lhs->GetTitle() < rhs->GetTitle();
}

bool Database::sortbycapacity(Warehouse* lhs, Warehouse* rhs)
{
	return lhs->GetCapacity() < rhs->GetCapacity();
}

bool Database::sortbynamedes(Warehouse* lhs, Warehouse* rhs)
{
	return lhs->GetTitle() > rhs->GetTitle();
}

bool Database::sortbycapacitydes(Warehouse* lhs, Warehouse* rhs)
{
	return lhs->GetCapacity() > rhs->GetCapacity();
}

Database::Database(string name, int hybrid) : Title(name), Hybrid(hybrid)
{

}

Database::Database(string name, int hybrid, vector<Warehouse*> vec) : Title(name), Hybrid(hybrid)
{
	for (auto i : vec)
	{
		if (auto w = dynamic_cast<ShoesWarehouse*>(i))
		{
			MainVector.push_back(new ShoesWarehouse(w));
		}
		else if (auto w = dynamic_cast<ClothesWarehouse*>(i))
		{
			MainVector.push_back(new ClothesWarehouse(w));
		}
	}
}

Database::Database(string path)
{
	ifstream input(path);
	if (input.is_open())
	{
		stringstream ss;
		ss << input.rdbuf();
		auto data = Split(ss.str(), "###\n");
		input.close();
		{
			auto mainData = Split(data[0], "\n");
			Title = mainData[0];
			Hybrid = stoi(mainData[1]);
		}
		for (int i = 1; i < data.size(); i++)
		{
			if (data[i][0] == 'C')
				MainVector.push_back(new ClothesWarehouse(data[i].substr(2)));
			else if (data[i][0] == 'S')
				MainVector.push_back(new ShoesWarehouse(data[i].substr(2)));
		}
	}
	else
		throw invalid_argument("Invalid path");
}

Database::~Database()
{
	for (int i = 0; i < MainVector.size(); i++)
		delete MainVector[i];
	MainVector.clear();
}

string Database::GetTitle()
{
	return Title;
}

void Database::SetTitle(string newtitle)
{
	Title = newtitle;
}

int Database::GetHybrid()
{
	return Hybrid;
}

void Database::Sort(string param, bool isDescending)
{
	if (param == "name")
		sort(MainVector.begin(), MainVector.end(), (isDescending ? sortbynamedes : sortbyname));
	else if (param == "capacity")
		sort(MainVector.begin(), MainVector.end(), (isDescending ? sortbycapacitydes : sortbycapacity));
	else
		throw "Unidentified param";
}

Warehouse* Database::FindByName(string name)
{
	auto it = std::find_if(MainVector.begin(), MainVector.end(), [=](Warehouse* item) { return item->GetTitle() == name; });
	return (it == MainVector.end() ? nullptr : *it);
}

vector<Warehouse*> Database::GroupByCity(string city)
{
	vector<Warehouse*> group;
	for (auto item : MainVector)
	{
		if (item->GetCity() == city)
		{
			group.push_back(item);
		}
	}
	return group;
}

vector<Warehouse*> Database::GroupBySize(bool isSmall)
{
	vector<Warehouse*> group;
	for (auto item : MainVector)
	{
		if (item->HasItems(isSmall))
			group.push_back(item);
	}
	return group;
}

void Database::AddItem(Warehouse* item)
{
	if (item == nullptr)
		throw "Unidentified item";
	if (FindByName(item->GetTitle()) != nullptr)
		throw "Already Exist";
	MainVector.push_back(item);
}

void Database::RemoveItem(string name)
{
	auto it = FindByName(name);
	if (it == nullptr)
		throw "Can not find";
	MainVector.erase(remove(MainVector.begin(), MainVector.end(), it), MainVector.end());
	delete it;
}

string Database::ToString(string title)
{
	stringstream ss;
	ss << title << endl << Hybrid << endl;
	for (auto item : MainVector)
	{
		ss << "###" << endl << item->ToString();
	}
	return ss.str();
}

void Database::Print()
{
	cout << "Title: " << Title << endl
		<< "Type: " << (Hybrid == 2 ? "Shoes" : (Hybrid == 1 ? "Clothes" : "Hybrid")) << endl;
	if (MainVector.size() > 0)
		cout << "\nItems:\n\n";
	for (int i = 0; i < MainVector.size(); i++)
	{
		MainVector[i]->Print();
	}
}

void Database::SaveToFile(string title)
{
	ofstream output((title == "\0" ? Title : title) + ".db");
	output << ToString((title == "\0" ? Title : title));
	output.close();
}