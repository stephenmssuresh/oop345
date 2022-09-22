/*
File: WritingRecord.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 26/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds
{
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee> &emp, const GeneratingList<Salary> &sal)
	{
		GeneratingList<EmployeeWage> activeEmp;

		// TODO: Add your code here to build a list of employees
		//         using raw pointers

		// quadratic complexity
		for (size_t i = 0; i < emp.size(); i++)
		{ // loop though emp then loop through sal to compare id
			for (size_t j = 0; j < sal.size(); j++)
			{
				if (sal[j].id == emp[i].id)
				{
					if (!emp.sinValidation(emp[i].id))
					{
						throw std::string("Invalid SIN");
					}

					// create new EmployeeWage object to validate before adding
					EmployeeWage *newEmp = new EmployeeWage(emp[i].name, sal[j].salary);

					// validate salary using rangeValidator()
					try
					{
						newEmp->rangeValidator();
						// use overloaded += operator in GeneratingList to move the object
						activeEmp += newEmp;
						delete newEmp; // delete after moving the resource to activeEmp
					}
					
					// catch (char* except)
					catch (const std::string except)
					{
						delete newEmp;
						throw except;
					}

					// validate SIN using GeneratingList::sinValidation()
					// do this validation earlier so you don't have to deallocate newEmp
					// if (!sal.sinValidation(sal[j].id))
					// {
					// 	delete newEmp;
					// 	throw std::string("Invalid SIN");
					// }
				}
			}
		}
		return activeEmp;
	}

}