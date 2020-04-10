#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <limits.h>

#define STRING_ULONG_MAX "4294967295"
#define DECIMALCHARSET "0123456789"
#define SYMBOL_NOT_FOUND string::npos

using namespace std;

struct ArgSet
{
	string val;
	string baseCharset;
	string destCharset;
};
//PROTOTYPES::
string iToBase(unsigned int nb, const string base);
unsigned int baseToUInt(string val, string base);
string iToBase(string nb, string baseSrc, string baseDest);
ArgSet* argCheck(int argc, char* argv[]);
bool repeatingSymbolsExist(const char* str);
bool isValueMatchBase(string val, string base);
//------------

int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "rus");//Исключительно ради котиков
	ArgSet* args = argCheck(argc, argv);
	if (args == NULL)
	{
		cout << "Usage:\t task1 val destBase" << endl;
		cout << "Or:\t task1 val valBase destBase" << endl;
		cout << "val - convertible value" << endl;
		cout << "valBase - val number system" << endl;
		cout << "destBase - designated number system" << endl;
	}
	cout << iToBase(args->val, 
		(args->baseCharset.empty()) ? DECIMALCHARSET : args->baseCharset, 
		args->destCharset) << endl;
	delete args;
    return 0;
}

string iToBase(unsigned int nb, const string base)
{
	string result;
	while (nb >= base.length())
	{
		unsigned int left = nb % base.length();
		result = base[left] + result;
		nb /= base.length();
	}
	result = base[nb] + result;
	return result;
}

string iToBase(string nb, string baseSrc, string baseDest)
{
	return iToBase(baseToUInt(nb, baseSrc), baseDest);
}

unsigned int baseToUInt(string val, string base)
{
	unsigned int result = 0;
	for (unsigned int i = 0; i < val.length(); i++)
	{
		result = (result * base.length()) + base.find(val[i]);
	}
	return result;
}

bool isValueMatchBase(string val, string base)
{
	for (unsigned int i = 0; i < val.length(); i++)
	{
		if (base.find(val[i]) == SYMBOL_NOT_FOUND) return false;
	}
	return true;
}

bool repeatingSymbolsExist(const char* str)
{
	const string argv2 = str;
	int matches = 0;
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		for (unsigned int j = 0; j < strlen(str); j++)
		{
			if (argv2[i] == argv2[j]) matches++;
			if (matches > 1) return true;
		}
		matches = 0;
	}
	return false;
}

ArgSet* argCheck(int argc, char** argv)
{
	unsigned int num = 0;
	string srcBase, destBase, src, val;
	ArgSet* result = NULL;
	if (argc < 3 || argc > 4) return NULL;
	try
	{
		//Получено три аргумента, следовательно возможен вызов программы для перевода числа в другую
		//систему счисления
		if (argc == 3)
		{
			//Проверка соответствия первого аргумента десятичной системе счисления
			if (!isValueMatchBase(argv[1], DECIMALCHARSET)) return NULL;
			num = baseToUInt(argv[1], DECIMALCHARSET);
			//Проверка символов в целевой системе счисления
			if (strlen(argv[2]) < 2) return NULL;
			//Проверка наличия повторяющихся символов
			if (repeatingSymbolsExist(argv[2])) return NULL;
			destBase = argv[2];
		}
		//Получено четыре аргумента, следовательно возможен вызов программы для перевода между
		//нестандартными системами счисления
		if (argc == 4)
		{
			//Проверка соответствия первого аргумента десятичной системе счисления
			if (!isValueMatchBase(argv[1], DECIMALCHARSET)) return NULL;
			num = baseToUInt(argv[1], DECIMALCHARSET);

			//Проверка базовой системы счисления
			if (strlen(argv[2]) < 2) return NULL;
			if (repeatingSymbolsExist(argv[2])) return NULL;
			srcBase = argv[2];

			//Проверка целевой системы счисления
			if (strlen(argv[3]) < 2) return NULL;
			if (repeatingSymbolsExist(argv[3])) return NULL;
			destBase = argv[3];
		}
		//Паранойя mode ON
		result = new ArgSet();
		result->val = argv[1];
		result->baseCharset = srcBase;
		result->destCharset = destBase;
	}
	catch (...) //Слабоумие и отвага!
	{
		return NULL;
	}
	return result;

}