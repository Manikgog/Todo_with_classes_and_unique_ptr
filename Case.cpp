#include "Case.h"


Case::Case()
	: _title(""), _date(Date()) {}

Case::Case(std::string title, std::string date, bool markIsDone)
	: _title(title), _date(Date(date)), _isDone(markIsDone) {}

Case::Case(std::string title, Date date, bool markIsDone) : _title(title), _date(Date(date)), _isDone(markIsDone) {}

std::string Case::GetTitle()
{
	return _title;
}

Date Case::GetDate()
{
	return _date;
}

void Case::PrintCase(int elLength)
{
	std::cout << _title;
	while (elLength-- > 0)
		std::cout << ' ';				// ������������ ��� � ������� �������� �� ����� ����� ������� ������
	std::cout << ' ';
	_date.PrintDate();
	if (_isDone)
		std::cout << "���������";
	else
		std::cout << "�� ���������";
}

bool Case::GetIsDoneMark() const
{
	return _isDone;
}

