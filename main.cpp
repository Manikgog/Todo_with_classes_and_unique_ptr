#include <iostream>
#include <locale.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Case.h"
#include "Date.h"
#include "CaseList.h"
#include "InputOutput.h"

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); 
	/*
	Case c1("_title", Date("12.07.2023"), false);
	Case c2("exercise C++", Date("13.07.2023"), false);
	Case c3("C++", Date("14.07.2023"), false);
	Case c4("C++ lesson", Date("17.07.2023"), false);
	CaseList caseList;
	caseList.AddCase(c4);
	caseList.AddCase(c3);
	caseList.AddCase(c2);
	caseList.AddCase(c1);
	Case* p_case = caseList.GetCase(0);
	caseList.PrintCaseList(); std::cout << std::endl;
	caseList.DeleteCase(1);
	caseList.SortCaseListByDate();
	caseList.PrintCaseList();	std::cout << std::endl;
	caseList.ChangeTitle("Lesson C++", 2);
	caseList.PrintCaseList(); std::cout << std::endl;
	caseList.ChangeDate("13.07.2023", 0);
	caseList.PrintCaseList(); std::cout << std::endl;
	caseList.MarkIsDone(0);
	caseList.PrintCaseList(); std::cout << std::endl;
	caseList.MarkIsNotDone(0);
	caseList.PrintCaseList(); std::cout << std::endl;
	*/

	InputOutput I;
	I.MainMenu();


	return 0;
}
