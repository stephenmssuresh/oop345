/*
File: GeneratingList.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 26/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds
{
	template <typename T>
	class GeneratingList
	{

		std::vector<T> list;

	public:
		GeneratingList() {}
		GeneratingList(const char *f)
		{
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file)
			{
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T &operator[](size_t i) const { return list[i]; }

		// TODO: Implement the Luhn Algorithm to check the
		//       valadity of SIN No's

		// https://en.wikipedia.org/wiki/Luhn_algorithm
		// function checkLuhn(string purportedCC) {
		// int nDigits := length(purportedCC)
		// int sum := integer(purportedCC[nDigits-1])
		// int parity := (nDigits-2) modulus 2
		// for i from 0 to nDigits - 2 {
		// 	int digit := integer(purportedCC[i])
		// 	if i modulus 2 = parity
		//     	digit := digit × 2
		// 	if digit > 9
		//     	digit := digit - 9
		// 	sum := sum + digit
		// }
		// return (sum modulus 10) = 0
		// }
		// purportedCC is SIN in this case

		bool sinValidation(const std::string &sin) const //const qualifier
		{
			int nDigits = sin.length(); // number of digits in the SIN

			// char& string::at (size_type idx)
			// https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
			int sum = (sin.at(nDigits - 1)) - '0'; // get last digit of the SIN

			int parity = (nDigits - 2) % 2;
			int digit;
			for (int i = 0; i <= nDigits - 2; i++)
			{
				digit = (sin.at(i)) - '0';
				if (i % 2 == parity)
				{
					digit *= 2;
				}
				if (digit > 9)
				{
					digit -= 9;
				}
				sum += digit;
			}

			return ((sum % 10) == 0); //true if valid
		}

		// TODO: Overload the += operator with a raw pointer
		//  as a second operand.
		void operator+=(T *objectToAdd)
		{
			list.push_back(std::move(*objectToAdd));
		}

		void print(std::ostream &os) const
		{
			os << std::fixed << std::setprecision(2);
			for (auto &e : list)
				e.print(os);
		}
	};

	template <typename T>
	std::ostream &operator<<(std::ostream &os, const GeneratingList<T> &rd)
	{
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
