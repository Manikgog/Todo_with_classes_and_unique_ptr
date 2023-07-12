#ifndef _CASELIST_H_
#define _CASELIST_H_

#include "Case.h"
#include "Date.h"
#include <vector>
#include <memory>


class CaseList
{
private:
	std::vector<std::unique_ptr<Case>> _caseList;				// вектор с указател€ми на экземпл€ры класса Case
	size_t MaxLength();

public:
	CaseList() {}
	~CaseList() {}
	void AddCase(const Case& case_);
	void DeleteCase(size_t index);
	size_t Size();
	void SortCaseListByDate();
	void PrintCaseList();
};

#endif