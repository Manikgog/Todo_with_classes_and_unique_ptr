#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Case.h"
#include "Date.h"
#include "CaseList.h"

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); 
	
	Case c1("_title", Date("12.07.2023"), false);
	Case c2("exercise C++", Date("13.07.2023"), false);
	Case c3("C++", Date("14.07.2023"), false);
	Case c4("C++ lesson", Date("17.07.2023"), false);
	CaseList caseList;
	caseList.AddCase(c4);
	caseList.AddCase(c3);
	caseList.AddCase(c2);
	caseList.AddCase(c1);
	caseList.PrintCaseList();
	//caseList.DeleteCase(1);
	caseList.SortCaseListByDate();
	caseList.PrintCaseList();



	return 0;
}
