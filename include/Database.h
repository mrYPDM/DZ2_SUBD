#pragma once
#include "ShoesWarehouse.h"
#include "ClothesWarehouse.h"
#include "Global.h"

class Database
{
	string Title;
	int Hybrid; // Тип БД // 0 - Гибрид, 1 - Вещи, 2 - Обувь
	vector<Warehouse*> MainVector;

	// Компараторы
	static bool sortbyname(Warehouse* lhs, Warehouse* rhs);

	static bool sortbycapacity(Warehouse* lhs, Warehouse* rhs);

	static bool sortbynamedes(Warehouse* lhs, Warehouse* rhs);

	static bool sortbycapacitydes(Warehouse* lhs, Warehouse* rhs);
public:

	// Основной конструктор
	Database(string name, int hybrid);
	
	// Конструктор по записям (для сохранения выборок)
	Database(string name, int hybrid, vector<Warehouse*> vec);
	
	// Чтение БД из файла
	Database(string path);

	~Database();

	string ToString();

	string GetTitle();

	void SetTitle(string newtitle);

	// Сортировка по параметру по возр./уб.
	void Sort(string param, bool isDescending);
	
	Warehouse* FindByName(string name);

	vector<Warehouse*> GroupByCity(string city);

	vector<Warehouse*> GroupBySize(bool isSmall);

	void AddItem(Warehouse* item);

	void RemoveItem(string name);

	int GetHybrid();

	void Print();

	// Сохранение в файл
	void SaveToFile(string title = "\0");
	/* 
	* Формат
	* <Имя БД>
	* <Тип БД>
	* ### - разделитель записей
	* <Тип склада>
	* <Имя склада>
	* <Город>
	* <Вместимость>
	* <Занятое пространсто>
	* # - разделитель размеров
	* <размер>
	* <тип> <количество>
	* ...
	*/
};