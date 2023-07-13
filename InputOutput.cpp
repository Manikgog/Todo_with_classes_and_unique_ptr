#include "InputOutput.h"


void InputOutput::PrintOverdueCaseList()
{
	if (!_list.Size())	// при пустом списке выходим из функции
		return;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	unsigned short currentYear = 1900 + ltm->tm_year;
	unsigned short currentMonth = 1 + ltm->tm_mon;
	unsigned short currentDay = ltm->tm_mday;
	bool is_first = true;
	for (size_t i = 0; i < _list.Size(); i++)
	{
		if (_list.GetCase(i)->GetDate() < Date(currentDay, currentMonth, currentYear))
		{
			if (is_first)
				std::cout << "\x1b[33mСписок просроченных задач : \x1b[0m\n";
			is_first = false;
			_list.GetCase(i)->PrintCase(_list.GetNumberOfSpaces(i));
			std::cout << std::endl;
		}
	}
}

InputOutput::InputOutput()
{
	/*CaseList list;
	for (size_t i = 0; i < list.Size(); i++)
	{
		_list.AddCase(*(list.GetCase(i)));
	}*/
}

void InputOutput::MainMenu()
{
	bool exit = true;	//< bool exit - variable-flag for exiting the program / переменна¤-флаг дл¤ выхода из программы
	int numAction = 0;	//< int numAction - variable for storing an action option from the menu selected by the user

	char answer{ 'н' };
	do {


		do {
			system("cls");
			std::cout << "\x1b[32mПрограмма дл¤ создания списка запланированных дел.\x1b[0m\n";
			PrintOverdueCaseList();

			Draw_menu(numAction);
		} while (input_menu(1, 5, numAction) != '\r');

		int nCase = 0;				//< int nCase - variable for storing the number of the selected case / переменна¤ дл¤ хранени¤ номера выбранного дела
		int nAction = 0;			//< int nAction - variable for storing the action number on the selected case / переменная для хранения номера действия над выбранным делом
		switch (numAction) {

		case 1:
			AddingCase();//< AddingCase(list) - adding a case to the list / добавление дела в список

			break;
		case 2:
			do {
				do {
					system("cls");
					if (1 == ChooseCaseMenu(nCase)) { //< если список пуст
						numAction = 1;
						break;
					}
				} while ('\r' != input_menu(0, _list.Size(), nCase));

				system("cls");

				//< exit to the main menu when selecting "Назад"
				//< выход в главное меню при выборе пункта "Назад"
				if (nCase < 0 || nCase >= _list.Size()) {
					numAction = 1;
					break;
				}
				//< choosing an action with a selected case
				//< выбор действи¤ с выбранным делом

				ChangeCaseMenu(nAction, nCase);
				system("pause");
			} while (nAction == 1);

			system("cls");
			break;
		case 3:
			//< clearing the entire list
			//< очистка всего списка
			system("cls");

			std::cout << "Вы уверены, что хотите удалить все задачи (д/н)? ";
			std::cin >> answer;
			if (answer == 'д' || answer == 'y')
			{
				_list.Clear();
				if (!_list.Size())
					std::cout << "Список дел очищен!\n";
			}
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			//< return to the main menu with an empty to-do list
			//< возврат в главное меню при пустом списке дел
			if (!_list.Size()) {
				numAction = 1;
				break;
			}
			_list.SortCaseListByDate();
			_list.PrintCaseList();
			system("pause");
			system("cls");
			break;
		case 5:
			exit = false;
			break;
		}
	} while (exit);
}

// метод для вывода на экран основного меню
void InputOutput::Draw_menu(const int numAction) {
	switch (numAction) {

	case 1:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\n\x1b[36mДобавление нового дела.\x1b[0m\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 2:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
\x1b[36mВыбор дела.\x1b[0m\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 3:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
\x1b[36mОчистка всего списка дел.\x1b[0m\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 4:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
\x1b[36mСортировка списка.\x1b[0m\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	case 5:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
\x1b[36mВыход из программы.\x1b[0m\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
		break;
	default:
		std::cout << "\n\x1b[33mВарианты действий:\x1b[0m\nДобавление нового дела.\n\
Выбор дела.\n\
Очистка всего списка дел.\n\
Сортировка списка.\n\
Выход из программы.\n\
\n\
Для выбора пункта меню пользуйтесь стрелками вверх и вниз на клавиатуре и кнопкой ВВОД.\n";
	}
}

char InputOutput::input_menu(int low, int hi, int& numAcion) {
	int c1 = 0;
	int c2 = 0;
	int c = c1 + c2;
	do {
		bool f = false;
		if (_kbhit()) {
			c1 = _getch();
			if (c1 == 13) {
				f = true;
				break;
			}
			c2 = _getch();
			c = c1 + c2;
			switch (c) {
			case 296:
				--numAcion;
				break;
			case 304:
				++numAcion;
				break;
			}
		}

	} while (c1 != 13 && c != 296 && c != 304);
	if (numAcion < low)
		numAcion = hi;
	else if (numAcion > hi)
		numAcion = low;
	return (char)c1;
}

void InputOutput::AddingCase()
{
	std::string date;							//< string object for entering the date

	std::cout << "\x1b[33mВведите название нового мероприятия -> \x1b[0m";
	std::string title;							//< string object for recording name of the case
	std::getline(std::cin, title);
	std::vector<int> vec_date;
	do {
		std::cout << "\x1b[33mВведите дату в формате ДД.ММ.ГГГГ -> \x1b[0m";
		std::getline(std::cin, date);
		
	} while (CheckDate(date) == false);
	Case newCase(title, date, false);
	_list.AddCase(newCase);
	std::cout << "\x1b[32mНовое дело добавлено в список.\x1b[0m\n";

	system("pause");
	system("cls");

}

bool InputOutput::CheckDate(std::string date)
{
	int arr[3]{};						//< цифра 3 - количество чисел в дате
	std::string s_tmp;
	char c;

	for (size_t i = 0, j = 0; i <= date.length(); ++i)
	{
		if ((date[i] == '.' || i == date.length()) && s_tmp.length() != 0)
		{
			arr[j] = stoi(s_tmp);
			s_tmp.erase();
			j++;
			if (j == 3) break;	//< число 3 - количество чисел в дате т.е. день, месяц, год - три числа
		}

		if (date[i] >= '0' && date[i] <= '9')
		{
			c = date[i];
			s_tmp += c;
		}
	}
	
	
	if (IsValidDate(arr[0], arr[1], arr[2]))
		return true;
	return false;

}

bool InputOutput::IsValidDate(int day, int month, int year)
{
	// current date/time based on current system
	time_t now = time(0);

	//std::cout << "Number of sec since January 1,1970:" << now << std::endl;

	tm* ltm = localtime(&now);

	// print various components of tm structure.
	unsigned short currentYear = 1900 + ltm->tm_year;
	unsigned short currentMonth = 1 + ltm->tm_mon;
	unsigned short currentDay = ltm->tm_mday;
	unsigned short lengthOfFeb = 28; // начальная длина февраля / initial length of february
	switch (month) {
	case 1:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 2:
		if (isLeapYear(year))
			lengthOfFeb = 29;
		if (day < 1 || day > lengthOfFeb) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 3:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 4:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 5:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 6:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 7:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 8:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 9:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 10:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 11:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 12:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31mНеправильно введён день месяца.\x1b[0m" << std::endl;
			return false;
		}
		break;
	}

	if (month > 12) {
		std::cout << "\x1b[31mМесяцев должно быть меньше 13.\x1b[0m" << std::endl;
		return false;
	}

	if (!CheckOverdueCase(day, month, year, currentYear, currentMonth, currentDay))
		return false;

	return true;
}


bool InputOutput::isLeapYear(int year) {
	if (year % 4 == 0) {
		if ((year % 100) == 0 && (year % 400) == 0) {
			//std::cout << "Год " << year << " високосный.\n";
			return true;
		}
		else if ((year % 100) != 0) {
			// std::cout << "Год " << year << " високосный.\n";
			return true;
		}
		else {
			//std::cout << "Год " << year << " не является високосным.\n";
			return false;
		}
	}

	//std::cout << "Год " << year << " не является високосным.\n";
	return false;
}

bool InputOutput::CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const
{
	if (year < currentYear) {
		std::cout << "\x1b[31mПланируемый год уже прошёл.\x1b[0m" << std::endl;
		return false;
	}
	else if (month < currentMonth && year == currentYear) {
		std::cout << "\x1b[31mПланируемый месяц уже прошёл.\x1b[0m" << std::endl;
		return false;
	}
	else if (day < currentDay && month == currentMonth) {
		std::cout << "\x1b[31mПланируемый день уже прошёл.\x1b[0m" << std::endl;
		return false;
	}
	return true;
}

int InputOutput::ChooseCaseMenu(int nCase)
{
	size_t listSize = _list.Size();
	if (listSize == 0) {
		std::cout << "Запланированных дел нет. Список пуст.\n";
		return 1;
	}
	else {


		std::cout << "\x1b[33mСписок запланированных дел:\x1b[0m\n";
		if (nCase >= 0 && nCase < listSize) {
			for (int i = 0; i < listSize; ++i) {
				if (nCase == i)
				{
					std::cout << "\x1b[36m";
					_list.GetCase(i)->PrintCase(_list.GetNumberOfSpaces(i));
					std::cout << "\x1b[0m";
				}
				else
					_list.GetCase(i)->PrintCase(_list.GetNumberOfSpaces(i));
					std::cout << std::endl;
			}
			std::cout << "Назад\n";
		}
		else {
			_list.PrintCaseList();
			std::cout << "\x1b[36mНазад\x1b[0m\n";
		}
	}
	return 0;
}

int InputOutput::ChangeCaseMenu(int nAction, int numCase)
{
	if (numCase < 0) numCase = 0;
	int num = 1;
	do {

		switch (num)
		{
		case 1:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\n\x1b[36mИзменить название\x1b[0m\n";
			std::cout << "Изменить дату\n";
			std::cout << "Удалить дело\n";
			std::cout << "Назад\n";
			break;
		case 2:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "\x1b[36mИзменить дату\x1b[0m\n";
			std::cout << "Удалить дело\n";
			std::cout << "Назад\n";
			break;
		case 3:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "Изменить дату\n";
			std::cout << "\x1b[36mУдалить дело\x1b[0m\n";
			std::cout << "Назад\n";
			break;
		case 4:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\nИзменить название\n";
			std::cout << "Изменить дату\n";
			std::cout << "Удалить дело\n";
			std::cout << "\x1b[36mНазад\x1b[0m\n";
		default:
			break;
		}
	} while (input_menu(1, 4, num) != '\r');
	std::string answer;
	std::string date;
	switch (num) {
	case 1:
		std::cout << "\x1b[33mВведите новое название дела: \x1b[0m";
		answer = "";
		std::getline(std::cin, answer);
		break;
	case 2:
		do {
			std::cout << "\x1b[33mВведите дату в формате ДД.ММ.ГГГГ -> \x1b[0m";
			std::getline(std::cin, date);
		} while (CheckDate(date) == false);

		break;
	case 3:
		if (!_list.Size())
		{
			system("cls");
			std::cout << "Cписок дел пуст. Удалять нечего.\n";
			system("pause");
		}
		else {
			std::cout << "\x1b[33mВы уверены, что хотите удалить дело (д/н): \x1b[0m";
			std::cin >> answer;
			if (answer[0] == 'y' || answer[0] == 'д')
			{
				if (_list.DeleteCase(numCase))
					std::cout << "Дело удалено из списка.\n";
				else
					std::cout << "Дело НЕ удалено из списка.\n";
			}
		}
		break;
	case 4:
		return 1;
	}
	if (num == 1)
	{
		_list.ChangeTitle(answer, numCase);
	}
	else if (num == 2)
	{
		_list.ChangeDate(date, numCase);
	}
	return 0;
}

