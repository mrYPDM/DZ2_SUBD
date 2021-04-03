#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::map;
using std::cerr;
using std::clog;
using std::exception;
using std::cin;
using std::pair;
using std::invalid_argument;

namespace fs = std::filesystem;

// Функция разбивки строки
static vector<string> Split(string str, string sep = " ", bool RemoveEmptyString = true)
{
	str += sep;
	vector<string> vec;

	int pos;
	while ((pos = str.find(sep)) != string::npos)
	{
		vec.push_back(str.substr(0, pos));
		str.erase(0, pos + sep.size()); // Стираем полученный фрагмент
	}

	if (RemoveEmptyString)
		vec.erase(remove(vec.begin(), vec.end(), ""), vec.end());

	return vec;
}