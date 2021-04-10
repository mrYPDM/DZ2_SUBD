#include "include/Database.h"
#include "include/Global.h"
/*
* Создание: однотипные и гибридные +
* Вывод списка БД +
* Удаление БД +
* Переименование БД +
* Открытие БД +
* Сохранение БД +
* Добавить запись +
* Редакт. запись +
* Удаление записей +
* Вывод записей +
* Сортировка записей +
* Выборка записей по правилу (значение поля) +
* Сохранение выборки как новой БД +
*/

/*
* 24 Вариант
* 
* Склад вещей
* Склад обуви
* Имя, город, вместимость, размеры, групп. по типу одежды или обуви, кол-во товара для каждого размера
* Размер одежды: размер, рост
* Размер обуви: размер
* 
* Подсчет кол-ва товара на складе +
* Поиск склада по имени +
* 
* Сортировка по имени +
* Сортировка по вместимости +
* 
* Выборка по городу +
* Выборка по большим/маленьким размерам: от 50/до 40 у одежды; от 45/до 36 у обуви +
*/

// Интерпритатор СУБД
void SUBD();

// Интерпритатор для Записи БД, т.к. запись БД - тоже БД
void SUBDI(string, Warehouse*);

// Если есть открытая БД, а действие ведет к её закрытию
bool YesNoQuestion(Database* db)
{
	char s = 'Y';
	if (db != nullptr)
	{
		cout << "There is an open database. Are Sure? (Y/N): ";
		cin >> s;
		cin.ignore();
	}
	return s == 'Y';
}

int main()
{
	setlocale(LC_ALL, "");
	SUBD();
}

void SUBD()
{
	Database* currentDatabase = nullptr;
	vector<Warehouse*> group; // Вектор для выборки
	string str = "";
	while (true)
	{
		// Выводим зеленым цветом
		cout << "\x1B[32m" << "subd@" + (currentDatabase == nullptr ? "null" : currentDatabase->GetTitle()) + ": " << "\033[0m";
		getline(cin, str);
		auto data = Split(str);
		if (data.size() == 0)
			continue;

		try
		{
			// exit
			if (data[0] == "exit")
			{
				if (YesNoQuestion(currentDatabase))
					break;
			}
			// create <title> <hybrid|clothes|shoes>
			// open <title>
			else if ((data[0] == "create" && data.size() == 3) || (data[0] == "open" && data.size() == 2))
			{
				if (YesNoQuestion(currentDatabase))
				{
					// Если решились закрыть - отчищаем память
					if (currentDatabase != nullptr)
					{
						currentDatabase->~Database();
						delete currentDatabase;
						currentDatabase = nullptr;
					}
					if (data[0] == "open")
						currentDatabase = new Database(data[1] + ".db");
					else if (data[0] == "create")
						currentDatabase = new Database(data[1], (data[2] == "shoes" ? 2 : data[2] == "clothes"));
				}
			}
			// add <shoes|clothes> <title> <city> <capacity> - for hybrid
			// add <title> <city> <capacity> - for not hybrid
			else if (data[0] == "add")
			{
				Warehouse* newItem = nullptr;
				// Если БД гибридная
				if (currentDatabase->GetHybrid() == 0 && data.size() == 5)
				{
					if (data[1] == "shoes")
						newItem = new ShoesWarehouse(data[2], data[3], stoi(data[4]));
					else if (data[1] == "clothes")
						newItem = new ClothesWarehouse(data[2], data[3], stoi(data[4]));
					else
						throw "Unidentified type";
				}
				// Если БД только по одежде
				else if (currentDatabase->GetHybrid() == 1 && data.size() == 4)
				{
					newItem = new ClothesWarehouse(data[1], data[2], stoi(data[3]));
				}
				// Только по обуви
				else if (currentDatabase->GetHybrid() == 2 && data.size() == 4)
				{
					newItem = new ShoesWarehouse(data[1], data[2], stoi(data[3]));
				}
				currentDatabase->AddItem(newItem);
			}
			// erase <title>
			else if (data[0] == "erase" && data.size() == 2)
			{
				if (currentDatabase != nullptr)
					currentDatabase->RemoveItem(data[1]);
			}
			// print - print DatabaseItems
			// print <name> - print Stuff of Warehouse;
			else if (data[0] == "print")
			{
				// Выводим БД
				if (data.size() == 1)
					currentDatabase->Print();
				// Выводим инфу по конкретной записи
				else
				{
					auto item = currentDatabase->FindByName(data[1]);
					if (item == nullptr)
						throw "Can not find warehouse";
					item->Print();
				}
			}
			// group by <city|size> <city name|size tpype>
			// group save <title>
			// group print
			else if (data[0] == "group")
			{
				// Группировка
				if (data[1] == "by" && data.size() == 4)
				{
					if (data[2] == "size")
						group = currentDatabase->GroupBySize(data[3] == "small");
					else if (data[2] == "city")
						group = currentDatabase->GroupByCity(data[3]);
					else
						throw "Unidentified param";
					cout << "Got group with " << group.size() << " elements\n";
				}
				// Сохранение выборки
				else if (data[1] == "save" && data.size() == 3)
				{
					if (group.empty())
						throw "Group is empty";
					Database* newDb = new Database(data[2], currentDatabase->GetHybrid(), group);
					newDb->SaveToFile();
					group.clear();
					newDb->~Database();
					delete newDb;
				}
				// Печать выборки
				else if (data[1] == "print")
				{
					if (group.empty())
						cout << "Group is empty\n";
					for (auto i : group)
						i->Print();
				}
				else
					throw "Something is wrong";
			}
			// sort by <name|capacity>
			// sort by des <name|capacity>
			else if (data[0] == "sort")
			{
				if (!(data.size() == 3 || data.size() == 4))
					throw "Something is wrong";
				bool descending = data[2] == "des"; // Сортировка по убыванию
				currentDatabase->Sort(data[2 + descending], descending); // Если по убыванию, то 2+1=3, иначе 2+0=2
			}
			// get <name>
			else if (data[0] == "get")
			{
				Warehouse* item = currentDatabase->FindByName(data[1]);
				if (item != nullptr)
					SUBDI("subd@" + currentDatabase->GetTitle() + "@" + item->GetTitle() + ": ", item);
				else
					throw "Can not find warehouse";
			}
			// save
			// save <title>
			else if (data[0] == "save")
			{
				if (currentDatabase != nullptr)
					currentDatabase->SaveToFile((data.size() == 2 ? data[1] : "\0")); // Если есть второй объект, передаём его как имя файла
				else
					throw "There is not opened database";
			}
			// show
			// Показываем все доступные БД
			else if (data[0] == "show")
			{
				for (auto i : fs::directory_iterator(fs::current_path()))
				{
					if (i.path().extension() == ".db")
						cout << i.path().stem() << endl;
				}
			}
			// rename <new title>
			// rename <title> <new title>
			else if (data[0] == "rename")
			{
				// Если пытаемся сохранить БД, которой нет
				if (currentDatabase == nullptr && data.size() == 2)
					throw "There is not opened database";
				// Добавляем имя текущей БД, чтобы привести все к формату rename <title> <new title>, чтобы не повторять код
				if (currentDatabase != nullptr && data.size() == 2)
					data.insert(data.begin() + 1, currentDatabase->GetTitle());
				fs::rename(fs::current_path().string() + "\\" + data[1] + ".db", fs::current_path().string() + "\\" + data[2] + ".db");
				if (currentDatabase != nullptr && data[1] == currentDatabase->GetTitle())
					currentDatabase->SetTitle(data[2]);
			}
			// remove
			// remove <name>
			else if (data[0] == "remove")
			{
				// Конструкция, аналогичная rename
				if (data.size() == 1 && currentDatabase == nullptr)
					throw "There is no opened database";
				if (data.size() == 1)
				{
					data.push_back(currentDatabase->GetTitle());
				}
				fs::remove(fs::current_path().string() + "\\" + data[1] + ".db");
				if (currentDatabase != nullptr && data[1] == currentDatabase->GetTitle())
				{
					currentDatabase->~Database();
					delete currentDatabase;
					currentDatabase = nullptr;
				}
			}
			// clear
			else if (data[0] == "clear")
			{
				system("cls");
			}
			// close
			else if (data[0] == "close")
			{
				if (currentDatabase == nullptr)
					throw "There is not opened database";
				if (YesNoQuestion(currentDatabase))
				{
					currentDatabase->~Database();
					delete currentDatabase;
					currentDatabase = nullptr;
				}
			}
			// help
			else if (data[0] == "help")
			{
			cout
				<< "exit\n" << "clear\n" << "close\n" << "help\n"
				<< "create <title> <hybrid|shoes|clothes>\n"
				<< "open <title>\n"
				<< "show\n" << "print\n" << "print <name>\n"
				<< "add <title> <city> <capacity>\n"
				<< "add <shoe|clothe> <title> <city> <capacity>\n"
				<< "erase <title>\n"
				<< "remove\n"
				<< "remove <title>\n"
				<< "get <name>\n"
				<< "save\n"
				<< "save <title>\n"
				<< "sort by <title|capacity>\n"
				<< "sort by des <title|capacity>\n"
				<< "group by <city|size> <city name|size type>\n"
				<< "group save <title>\n"
				<< "group print\n"
				<< "rename <new title>\n"
				<< "rename <title> <new title>";
			}
		}
		catch (const char* e)
		{
			// Выводим красным цветом
			cerr << "\x1B[91m" << e << "\033[0m\n";
		}
		catch (const exception& e)
		{
			cerr << "\x1B[91m" << e.what() << "\033[0m\n";
		}
	}
}

void SUBDI(string placeholder, Warehouse* currentItem)
{
	string str = "";
	while (true)
	{
		cout << "\x1B[32m" << placeholder << "\033[0m";
		getline(cin, str);
		auto data = Split(str);
		if (data.size() == 0)
			continue;
		try {
			// exit
			if (data[0] == "exit")
			{
				break;
			}
			// clear
			else if (data[0] == "clear")
			{
				system("cls");
			}
			// add <type> <size1> <size2> <count>
			// add <type> <size> <count>
			else if (data[0] == "add")
			{
				// Так как Clothes и Shoes наследники Warehouse, а AddStuff абстрактная и аргументы к разным классам различны, приходится передавать вектор
				currentItem->AddStuff(vector<string>(data.begin() + 1, data.end()));
			}
			// remove <type> <size1> <size2> <count|all>
			// remove <type> <size> <count|all>
			else if (data[0] == "remove")
			{
				currentItem->RemoveStuff(vector<string>(data.begin() + 1, data.end()));
			}
			// print
			else if (data[0] == "print")
			{
				currentItem->Print();
			}
			// edit <title|city|capacity> <new title|new city|new capacity>
			else if (data[0] == "edit" && data.size() == 3)
			{
				if (data[1] == "title")
					currentItem->SetTitle(data[2]);
				else if (data[1] == "city")
					currentItem->SetCity(data[2]);
				else if (data[1] == "capacity")
					currentItem->SetCapacity(stoi(data[2]));
			}
			// help
			else if (data[0] == "help")
			{
				cout
					<< "exit\n"
					<< "clear\n"
					<< "help\n"
					<< "add <type> <size1> <size2> <count> - for clothes\n"
					<< "remove <type> <size1> <size2> <count> - for clothes\n"
					<< "add <type> <size> <count> - for shoes\n"
					<< "remove <type> <size> <count> - for shoes\n"
					<< "print\n"
					<< "edit <title|city|capacity> <new title|new city|new capacity>\n";
			}
		}
		catch (const char* e)
		{
			cerr << "\x1B[91m" << e << "\033[0m\n";
		}
		catch (const exception& e)
		{
			cerr << "\x1B[91m" << e.what() << "\033[0m\n";
		}
	}
}
