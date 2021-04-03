#pragma once
#include "ShoesWarehouse.h"
#include "ClothesWarehouse.h"
#include "Global.h"

class Database
{
	string Title;
	int Hybrid; // ��� �� // 0 - ������, 1 - ����, 2 - �����
	vector<Warehouse*> MainVector;

	// �����������
	static bool sortbyname(Warehouse* lhs, Warehouse* rhs);

	static bool sortbycapacity(Warehouse* lhs, Warehouse* rhs);

	static bool sortbynamedes(Warehouse* lhs, Warehouse* rhs);

	static bool sortbycapacitydes(Warehouse* lhs, Warehouse* rhs);
public:

	// �������� �����������
	Database(string name, int hybrid);
	
	// ����������� �� ������� (��� ���������� �������)
	Database(string name, int hybrid, vector<Warehouse*> vec);
	
	// ������ �� �� �����
	Database(string path);

	~Database();

	string ToString();

	string GetTitle();

	void SetTitle(string newtitle);

	// ���������� �� ��������� �� ����./��.
	void Sort(string param, bool isDescending);
	
	Warehouse* FindByName(string name);

	vector<Warehouse*> GroupByCity(string city);

	vector<Warehouse*> GroupBySize(bool isSmall);

	void AddItem(Warehouse* item);

	void RemoveItem(string name);

	int GetHybrid();

	void Print();

	// ���������� � ����
	void SaveToFile(string title = "\0");
	/* 
	* ������
	* <��� ��>
	* <��� ��>
	* ### - ����������� �������
	* <��� ������>
	* <��� ������>
	* <�����>
	* <�����������>
	* <������� �����������>
	* # - ����������� ��������
	* <������>
	* <���> <����������>
	* ...
	*/
};