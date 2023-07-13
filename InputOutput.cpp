#include "InputOutput.h"


void InputOutput::PrintOverdueCaseList()
{
	if (!_list.Size())	// ��� ������ ������ ������� �� �������
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
				std::cout << "\x1b[33m������ ������������ ����� : \x1b[0m\n";
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
	bool exit = true;	//< bool exit - variable-flag for exiting the program / ���������-���� �� ������ �� ���������
	int numAction = 0;	//< int numAction - variable for storing an action option from the menu selected by the user

	char answer{ '�' };
	do {


		do {
			system("cls");
			std::cout << "\x1b[32m��������� �� �������� ������ ��������������� ���.\x1b[0m\n";
			PrintOverdueCaseList();

			Draw_menu(numAction);
		} while (input_menu(1, 5, numAction) != '\r');

		int nCase = 0;				//< int nCase - variable for storing the number of the selected case / ��������� �� ������� ������ ���������� ����
		int nAction = 0;			//< int nAction - variable for storing the action number on the selected case / ���������� ��� �������� ������ �������� ��� ��������� �����
		switch (numAction) {

		case 1:
			AddingCase();//< AddingCase(list) - adding a case to the list / ���������� ���� � ������

			break;
		case 2:
			do {
				do {
					system("cls");
					if (1 == ChooseCaseMenu(nCase)) { //< ���� ������ ����
						numAction = 1;
						break;
					}
				} while ('\r' != input_menu(0, _list.Size(), nCase));

				system("cls");

				//< exit to the main menu when selecting "�����"
				//< ����� � ������� ���� ��� ������ ������ "�����"
				if (nCase < 0 || nCase >= _list.Size()) {
					numAction = 1;
					break;
				}
				//< choosing an action with a selected case
				//< ����� ������� � ��������� �����

				ChangeCaseMenu(nAction, nCase);
				system("pause");
			} while (nAction == 1);

			system("cls");
			break;
		case 3:
			//< clearing the entire list
			//< ������� ����� ������
			system("cls");

			std::cout << "�� �������, ��� ������ ������� ��� ������ (�/�)? ";
			std::cin >> answer;
			if (answer == '�' || answer == 'y')
			{
				_list.Clear();
				if (!_list.Size())
					std::cout << "������ ��� ������!\n";
			}
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			//< return to the main menu with an empty to-do list
			//< ������� � ������� ���� ��� ������ ������ ���
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

// ����� ��� ������ �� ����� ��������� ����
void InputOutput::Draw_menu(const int numAction) {
	switch (numAction) {

	case 1:
		std::cout << "\n\x1b[33m�������� ��������:\x1b[0m\n\x1b[36m���������� ������ ����.\x1b[0m\n\
����� ����.\n\
������� ����� ������ ���.\n\
���������� ������.\n\
����� �� ���������.\n\
\n\
��� ������ ������ ���� ����������� ��������� ����� � ���� �� ���������� � ������� ����.\n";
		break;
	case 2:
		std::cout << "\n\x1b[33m�������� ��������:\x1b[0m\n���������� ������ ����.\n\
\x1b[36m����� ����.\x1b[0m\n\
������� ����� ������ ���.\n\
���������� ������.\n\
����� �� ���������.\n\
\n\
��� ������ ������ ���� ����������� ��������� ����� � ���� �� ���������� � ������� ����.\n";
		break;
	case 3:
		std::cout << "\n\x1b[33m�������� ��������:\x1b[0m\n���������� ������ ����.\n\
����� ����.\n\
\x1b[36m������� ����� ������ ���.\x1b[0m\n\
���������� ������.\n\
����� �� ���������.\n\
\n\
��� ������ ������ ���� ����������� ��������� ����� � ���� �� ���������� � ������� ����.\n";
		break;
	case 4:
		std::cout << "\n\x1b[33m�������� ��������:\x1b[0m\n���������� ������ ����.\n\
����� ����.\n\
������� ����� ������ ���.\n\
\x1b[36m���������� ������.\x1b[0m\n\
����� �� ���������.\n\
\n\
��� ������ ������ ���� ����������� ��������� ����� � ���� �� ���������� � ������� ����.\n";
		break;
	case 5:
		std::cout << "\n\x1b[33m�������� ��������:\x1b[0m\n���������� ������ ����.\n\
����� ����.\n\
������� ����� ������ ���.\n\
���������� ������.\n\
\x1b[36m����� �� ���������.\x1b[0m\n\
\n\
��� ������ ������ ���� ����������� ��������� ����� � ���� �� ���������� � ������� ����.\n";
		break;
	default:
		std::cout << "\n\x1b[33m�������� ��������:\x1b[0m\n���������� ������ ����.\n\
����� ����.\n\
������� ����� ������ ���.\n\
���������� ������.\n\
����� �� ���������.\n\
\n\
��� ������ ������ ���� ����������� ��������� ����� � ���� �� ���������� � ������� ����.\n";
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

	std::cout << "\x1b[33m������� �������� ������ ����������� -> \x1b[0m";
	std::string title;							//< string object for recording name of the case
	std::getline(std::cin, title);
	std::vector<int> vec_date;
	do {
		std::cout << "\x1b[33m������� ���� � ������� ��.��.���� -> \x1b[0m";
		std::getline(std::cin, date);
		
	} while (CheckDate(date) == false);
	Case newCase(title, date, false);
	_list.AddCase(newCase);
	std::cout << "\x1b[32m����� ���� ��������� � ������.\x1b[0m\n";

	system("pause");
	system("cls");

}

bool InputOutput::CheckDate(std::string date)
{
	int arr[3]{};						//< ����� 3 - ���������� ����� � ����
	std::string s_tmp;
	char c;

	for (size_t i = 0, j = 0; i <= date.length(); ++i)
	{
		if ((date[i] == '.' || i == date.length()) && s_tmp.length() != 0)
		{
			arr[j] = stoi(s_tmp);
			s_tmp.erase();
			j++;
			if (j == 3) break;	//< ����� 3 - ���������� ����� � ���� �.�. ����, �����, ��� - ��� �����
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
	unsigned short lengthOfFeb = 28; // ��������� ����� ������� / initial length of february
	switch (month) {
	case 1:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 2:
		if (isLeapYear(year))
			lengthOfFeb = 29;
		if (day < 1 || day > lengthOfFeb) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 3:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 4:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 5:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 6:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 7:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 8:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 9:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 10:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 11:
		if (day < 1 || day > 30) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	case 12:
		if (day < 1 || day > 31) {
			std::cout << "\x1b[31m����������� ����� ���� ������.\x1b[0m" << std::endl;
			return false;
		}
		break;
	}

	if (month > 12) {
		std::cout << "\x1b[31m������� ������ ���� ������ 13.\x1b[0m" << std::endl;
		return false;
	}

	if (!CheckOverdueCase(day, month, year, currentYear, currentMonth, currentDay))
		return false;

	return true;
}


bool InputOutput::isLeapYear(int year) {
	if (year % 4 == 0) {
		if ((year % 100) == 0 && (year % 400) == 0) {
			//std::cout << "��� " << year << " ����������.\n";
			return true;
		}
		else if ((year % 100) != 0) {
			// std::cout << "��� " << year << " ����������.\n";
			return true;
		}
		else {
			//std::cout << "��� " << year << " �� �������� ����������.\n";
			return false;
		}
	}

	//std::cout << "��� " << year << " �� �������� ����������.\n";
	return false;
}

bool InputOutput::CheckOverdueCase(int day, int month, int year, unsigned short currentYear, unsigned short currentMonth, unsigned short currentDay) const
{
	if (year < currentYear) {
		std::cout << "\x1b[31m����������� ��� ��� ������.\x1b[0m" << std::endl;
		return false;
	}
	else if (month < currentMonth && year == currentYear) {
		std::cout << "\x1b[31m����������� ����� ��� ������.\x1b[0m" << std::endl;
		return false;
	}
	else if (day < currentDay && month == currentMonth) {
		std::cout << "\x1b[31m����������� ���� ��� ������.\x1b[0m" << std::endl;
		return false;
	}
	return true;
}

int InputOutput::ChooseCaseMenu(int nCase)
{
	size_t listSize = _list.Size();
	if (listSize == 0) {
		std::cout << "��������������� ��� ���. ������ ����.\n";
		return 1;
	}
	else {


		std::cout << "\x1b[33m������ ��������������� ���:\x1b[0m\n";
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
			std::cout << "�����\n";
		}
		else {
			_list.PrintCaseList();
			std::cout << "\x1b[36m�����\x1b[0m\n";
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
			std::cout << "\n\x1b[36m�������� ��������\x1b[0m\n";
			std::cout << "�������� ����\n";
			std::cout << "������� ����\n";
			std::cout << "�����\n";
			break;
		case 2:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\n�������� ��������\n";
			std::cout << "\x1b[36m�������� ����\x1b[0m\n";
			std::cout << "������� ����\n";
			std::cout << "�����\n";
			break;
		case 3:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\n�������� ��������\n";
			std::cout << "�������� ����\n";
			std::cout << "\x1b[36m������� ����\x1b[0m\n";
			std::cout << "�����\n";
			break;
		case 4:
			system("cls");
			_list.GetCase(numCase)->PrintCase(_list.GetNumberOfSpaces(numCase));
			std::cout << "\n�������� ��������\n";
			std::cout << "�������� ����\n";
			std::cout << "������� ����\n";
			std::cout << "\x1b[36m�����\x1b[0m\n";
		default:
			break;
		}
	} while (input_menu(1, 4, num) != '\r');
	std::string answer;
	std::string date;
	switch (num) {
	case 1:
		std::cout << "\x1b[33m������� ����� �������� ����: \x1b[0m";
		answer = "";
		std::getline(std::cin, answer);
		break;
	case 2:
		do {
			std::cout << "\x1b[33m������� ���� � ������� ��.��.���� -> \x1b[0m";
			std::getline(std::cin, date);
		} while (CheckDate(date) == false);

		break;
	case 3:
		if (!_list.Size())
		{
			system("cls");
			std::cout << "C����� ��� ����. ������� ������.\n";
			system("pause");
		}
		else {
			std::cout << "\x1b[33m�� �������, ��� ������ ������� ���� (�/�): \x1b[0m";
			std::cin >> answer;
			if (answer[0] == 'y' || answer[0] == '�')
			{
				if (_list.DeleteCase(numCase))
					std::cout << "���� ������� �� ������.\n";
				else
					std::cout << "���� �� ������� �� ������.\n";
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

