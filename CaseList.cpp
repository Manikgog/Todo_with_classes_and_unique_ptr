#include <memory>
#include <fstream>
#include "CaseList.h"
#include "Case.h"

size_t CaseList::MaxLength()
{
	size_t maxLength = 0;
	for (const auto& el : this->_caseList)
	{
		if (maxLength < el->GetTitle().size())
			maxLength = el->GetTitle().size();
	}
	return maxLength;
}

CaseList::CaseList() 
{
	
	std::ifstream fin; //< creating an ifstream object to read data from a file

	fin.open(this->_filename, std::ios_base::in | std::ios_base::binary);
	//< writing cases from a file to the listCases array
	//< запись дел из файла в массив listCases
	if (!fin.is_open()) {
		std::cout << "Ошибка открытия файла.\n";
		return;
	}
	else {
		//std::cout << "Файл открыт.\n";
		struct C4se
		{
			char title[_sizeTitle]{};
			Date date;
			bool isDone;
		};
		C4se c4se;
		while (fin.read((char*)&c4se, sizeof(C4se)))
		{
			this->AddCase(Case(c4se.title, c4se.date, c4se.isDone));
		}
	}

	fin.close();
	return;
}

CaseList::~CaseList()
{
	std::ofstream fout;
	fout.open(this->_filename, std::ios_base::out | std::ios_base::binary);

	if (!fout.is_open()) {
		std::cout << "Невозможно открыть файл.\n";
		return;
	}

	struct C4se
	{
		char title[_sizeTitle]{};
		Date date;
		bool isDone{};
	};

	for (int j = 0; j < this->Size(); ++j)
	{
		C4se c4se;
		size_t lengthOfTitleString = this->_caseList.at(j)->GetTitle().size();
		if (lengthOfTitleString >= _sizeTitle)
			lengthOfTitleString = _sizeTitle - 1;
		for (int i = 0; i < lengthOfTitleString; ++i)
		{
			c4se.title[i] = this->_caseList.at(j)->GetTitle().at(i);
		}
		c4se.date = this->_caseList.at(j)->GetDate();
		c4se.isDone = this->_caseList.at(j)->GetIsDoneMark();
		fout.write((char*)&c4se, sizeof(C4se));
	}

	fout.close();
	return;
}

void CaseList::AddCase(const Case& case_)
{
	this->_caseList.push_back(std::make_unique<Case>(case_));
}

bool CaseList::DeleteCase(size_t index)
{
	if (index < 0 || index >= this->_caseList.size())
		return false;
	this->_caseList.erase(this->_caseList.begin() + index);
	return true;
}

size_t CaseList::Size() const
{
	return this->_caseList.size();
}


void CaseList::SortCaseListByDate()
{
	for (size_t i = 0; i < this->Size() - 1; i++)
	{
		std::unique_ptr<Case> tmp_case;
		size_t index = i;
		for (size_t j = i + 1; j < this->Size(); j++)
		{
			if (_caseList.at(i)->GetDate() > _caseList.at(j)->GetDate())
			{
				tmp_case.reset();
				tmp_case = std::make_unique<Case>(_caseList.at(j)->GetTitle(), _caseList.at(j)->GetDate(), _caseList.at(j)->GetIsDoneMark());
				index = j;
			}
		}
		if (index != i)
		{
			_caseList.at(index).reset();
			_caseList.at(index) = std::make_unique<Case>(*(_caseList.at(i).release()));
			_caseList.at(i).reset();
			_caseList.at(i) = std::make_unique<Case>(*(tmp_case.release()));
		}
	}
}

/*!
метод возвращает количество пробелов после названия дела(задачи) до начала даты для выравнивания по ширине.
Количество пробелов получается путём вычитания длины самого длинного названия дела и дела, которое выводится на печать.
\param[in] index индекс дела(задачи) в векторе задач _caseList
\param[out] size_t количество пробелов после выведенного на экран названия дела.
*/
size_t CaseList::GetNumberOfSpaces(size_t index)
{
	size_t maxLength = this->MaxLength();
	return maxLength - this->_caseList.at(index)->GetTitle().size();
}

void CaseList::PrintCaseList()
{
	
	for (size_t i = 0; i < this->Size(); i++)
	{
		_caseList.at(i)->PrintCase(this->GetNumberOfSpaces(i));
		std::cout << std::endl;
	}
}

void CaseList::ChangeTitle(const std::string& title, size_t index)
{
	Date date = this->_caseList.at(index)->GetDate();
	bool isDone = this->_caseList.at(index)->GetIsDoneMark();
	this->DeleteCase(index);
	this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, isDone));
}

void CaseList::ChangeDate(const std::string& date, size_t index)
{
	std::string title = _caseList.at(index)->GetTitle();
	Date newDate(date);
	bool isDone = _caseList.at(index)->GetIsDoneMark();
	this->DeleteCase(index);
	this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, isDone));
}

void CaseList::MarkIsDone(size_t index)
{
	if (_caseList.at(index)->GetIsDoneMark() == true)
		return;
	else
	{
		std::string title = _caseList.at(index)->GetTitle();
		Date date = this->_caseList.at(index)->GetDate();
		this->DeleteCase(index);
		this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, true));
	}
}

void CaseList::MarkIsNotDone(size_t index)
{
	if (_caseList.at(index)->GetIsDoneMark() == false)
		return;
	else
	{
		std::string title = _caseList.at(index)->GetTitle();
		Date date = this->_caseList.at(index)->GetDate();
		this->DeleteCase(index);
		this->_caseList.insert(_caseList.begin() + index, std::make_unique<Case>(title, date, false));
	}
}

Case* CaseList::GetCase(size_t index) const
{
	return _caseList.at(index).get();
}

void CaseList::Clear()
{
	_caseList.clear();
}

