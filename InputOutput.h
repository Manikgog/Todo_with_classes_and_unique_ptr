#ifndef _INPUTOUTPUT_H_
#define _INPUTOUTPUT_H_

#include <iostream>
#include <string>
#include <conio.h>
#include "Case.h"
#include "Date.h"
#include "CaseList.h"


class InputOutput
{
private:
	CaseList _list;
	void PrintOverdueCaseList();
public:
	InputOutput();
	void MainMenu();
	void Draw_menu(const int numAction);
	char input_menu(int low, int hi, int& numAcion);
	void AddingCase();
	bool CheckDate(std::string date);
	bool IsValidDate(int day, int month, int year);
	bool isLeapYear(int year);
	bool CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const;
	int ChooseCaseMenu(int nCase);
	int ChangeCaseMenu(int nAction, int numCase);
};


#endif // !

