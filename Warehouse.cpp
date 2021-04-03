#include "Warehouse.h"

Warehouse::Warehouse()
{

}

Warehouse::Warehouse(string title, string city, int capacity) : Title(title), City(city), Capacity(capacity)
{

}

Warehouse::Warehouse(Warehouse* data)
{
	Title = data->GetTitle();
	City = data->GetCity();
	Capacity = data->GetCapacity();
	Size = data->GetSize();
}

string Warehouse::GetTitle()
{
	return Title;
}

void Warehouse::SetTitle(string newtitle)
{
	Title = newtitle;
}

string Warehouse::GetCity()
{
	return City;
}

void Warehouse::SetCity(string newcity)
{
	City = newcity;
}

int Warehouse::GetCapacity()
{
	return Capacity;
}

void Warehouse::SetCapacity(int newcapcity)
{
	Capacity = newcapcity;
}

int Warehouse::GetSize()
{
	return Size;
}