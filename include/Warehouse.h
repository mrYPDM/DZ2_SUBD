#pragma once
#include "Global.h"

class Warehouse
{
protected:
	string Title;
	string City;
	unsigned int Capacity = 0;
	unsigned int Size = 0;
public:
	Warehouse();

	// Основной конструктор
	Warehouse(string title, string city, int capacity);

	//Конструктор, по-сути, копирования
	Warehouse(Warehouse* data);

	string GetTitle();

	void SetTitle(string newtitle);

	string GetCity();

	void SetCity(string newcity);

	int GetCapacity();

	void SetCapacity(int newcapcity);

	int GetSize();

	 // Есть ли маленькие/большие элементы
	virtual bool HasItems(bool isSmall) = 0;

	// Перевод в строку
	virtual string ToString() = 0;

	// Печать
	virtual void Print(std::ostream& out = std::cout) = 0;

	// Добавить вещи
	virtual void AddStuff(vector<string> data) = 0;

	// Удалить вещи
	virtual void RemoveStuff(vector<string> data) = 0;
};