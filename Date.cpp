#include "Date.h"

std::string Date::NumberToString(int month)
{
	std::string month_str;
	switch (month) {
	case 1:
		month_str = "������";
		break;
	case 2:
		month_str = "�������";
		break;
	case 3:
		month_str = "�����";
		break;
	case 4:
		month_str = "������";
		break;
	case 5:
		month_str = "���";
		break;
	case 6:
		month_str = "����";
		break;
	case 7:
		month_str = "����";
		break;
	case 8:
		month_str = "�������";
		break;
	case 9:
		month_str = "��������";
		break;
	case 10:
		month_str = "�������";
		break;
	case 11:
		month_str = "������";
		break;
	case 12:
		month_str = "�������";
		break;
	}
	return month_str;
}

Date::Date() : _day(1), _month(1), _year(1970) {}

Date::Date(int day, int month, int year)
	: _day(day), _month(month), _year(year)
{}

Date::Date(std::string date)
{
	int arr[3]{};
	std::string s_tmp;
	char c;

	for (size_t i = 0, j = 0; i <= date.length(); ++i)
	{
		if ((date[i] == '.' || i == date.length()) && s_tmp.length() != 0)
		{
			arr[j] = stoi(s_tmp);
			s_tmp.erase();
			j++;
			if (j == 3) break;
		}

		if (date[i] >= '0' && date[i] <= '9')
		{
			c = date[i];
			s_tmp += c;
		}
	}
	_day = arr[0];
	_month = arr[1];
	_year = arr[2];
}


int Date::GetDay()
{
	return _day;
}

int Date::GetMonth()
{
	return _month;
}

int Date::GetYear()
{
	return _year;
}

bool Date::operator<(const Date& date)
{
	if (_year < date._year) {
		//std::cout << "\x1b[31m����������� ��� ��� ������.\x1b[0m" << std::endl;
		return true;
	}
	else if (_month < date._month && _year == date._year) {
		//std::cout << "\x1b[31m����������� ����� ��� ������.\x1b[0m" << std::endl;
		return true;
	}
	else if (_day < date._day && _month == date._month) {
		//std::cout << "\x1b[31m����������� ���� ��� ������.\x1b[0m" << std::endl;
		return true;
	}
	return false;
}

bool Date::operator==(const Date& date)
{
	if (_year == date._year && _month == date._month && _day == date._day)
	{
		return true;
	}
	return false;
}

bool Date::operator>(const Date& date)
{
	if ((*this < date) || (*this == date))
		return false;
	return true;
}

void Date::PrintDate()
{
	std::cout << GetDay();
	if (GetDay() < 10)
		std::cout << ' ';
	std::cout << ' ' << NumberToString(GetMonth());
	int maxLengthOfMonth = 8; //��������
	int numberOfSpaces = maxLengthOfMonth - NumberToString(GetMonth()).size();
	while (numberOfSpaces-- > 0)
		std::cout << ' ';
	std::cout << ' ' << GetYear() << ' ';

}
