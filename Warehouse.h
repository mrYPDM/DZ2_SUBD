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

	// �������� �����������
	Warehouse(string title, string city, int capacity);

	//�����������, ��-����, �����������
	Warehouse(Warehouse* data);

	string GetTitle();

	void SetTitle(string newtitle);

	string GetCity();

	void SetCity(string newcity);

	int GetCapacity();

	void SetCapacity(int newcapcity);

	int GetSize();

	 // ���� �� ���������/������� ��������
	virtual bool HasItems(bool isSmall) = 0;

	// ������� � ������
	virtual string ToString() = 0;

	// ������
	virtual void Print(std::ostream& out = std::cout) = 0;

	// �������� ����
	virtual void AddStuff(vector<string> data) = 0;

	// ������� ����
	virtual void RemoveStuff(vector<string> data) = 0;
};