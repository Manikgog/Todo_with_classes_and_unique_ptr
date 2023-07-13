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
	const std::string _filename = "case.bin";
	static const int _sizeTitle = 56;
	size_t MaxLength();

public:
	CaseList();
	~CaseList();
	void AddCase(const Case& case_);
	bool DeleteCase(size_t index);
	size_t Size() const;
	void SortCaseListByDate();
	size_t GetNumberOfSpaces(size_t index);
	void PrintCaseList();
	void ChangeTitle(const std::string& title, size_t index);
	void ChangeDate(const std::string& title, size_t index);
	void MarkIsDone(size_t index);
	void MarkIsNotDone(size_t index);
	Case* GetCase(size_t index) const;
	void Clear();
};

#endif