/*!
\brief Класс Case (задача, дело), который содержит поля название дела и дату
*/
#ifndef _CASE_H_
#define _CASE_H_

#include <string>
#include "Date.h"

class Date;

class Case
{
private:
	std::string _title;
	Date _date;
	bool _isDone;
public:
	Case();
	Case(std::string title, std::string date, bool markIsDone);
	Case(std::string title, Date date, bool markIsDone);
	std::string GetTitle();
	Date GetDate();
	void PrintCase(int elLength);
	bool GetIsDoneMark() const;
};

#endif // !_CASE_H_

