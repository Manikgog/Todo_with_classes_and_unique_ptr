#include <memory>
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

void CaseList::AddCase(const Case& case_)
{
	this->_caseList.push_back(std::make_unique<Case>(case_));
}

void CaseList::DeleteCase(size_t index)
{
	if (index < 0 || index >= this->_caseList.size())
		return;
	this->_caseList.erase(this->_caseList.begin() + index);
	return;
}

size_t CaseList::Size()
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

void CaseList::PrintCaseList()
{
	size_t maxLength = this->MaxLength();
	for (const auto& el : this->_caseList)
	{
		
		el->PrintCase(maxLength - el->GetTitle().size());
		std::cout << std::endl;
	}
}
