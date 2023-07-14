#ifndef _INPUTOUTPUT_H_
#define _INPUTOUTPUT_H_

#include <iostream>
#include <string>
#include <conio.h>
#include "Case.h"
#include "Date.h"
#include "CaseList.h"

/*!
\brief класс, обеспечивает интерфейс с пользователем приложения
Класс выполняет:
- отображение основного меню;
- добавление нового дела;
- удаление всего списка дел;
- сортировку списка по дате;
- выбор дела и его изменение или удаление;
- выход из программы.
*/
class InputOutput
{
private:
	CaseList _list;
	void PrintOverdueCaseList();
	void Draw_menu(const int numAction);
	char input_menu(int low, int hi, int& numAcion);
	void AddingCase();
	bool CheckDate(std::string date);
	bool IsValidDate(int day, int month, int year);
	bool isLeapYear(int year);
	bool CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const;
	int ChooseCaseMenu(int nCase);
	int ChangeCaseMenu(int numCase);
	void ChangeCase(int numCase, int num);
	void ChangeTitle(int numCase);
	void ChangeDate(int numCase);
	void DeleteCase(int numCase);
	void MarkCase(int numCase);
public:
	InputOutput();
	void MainMenu();
	
};


#endif // !

