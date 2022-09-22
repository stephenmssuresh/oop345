/*
File: foodorder.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 20/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_FOODORDER_H
#define SDDS_FOODORDER_H

extern double g_taxrate;
extern double g_dailydiscount;

namespace sdds {
	class FoodOrder {
		char customerName[10];
		char foodDesc[25];
		double foodPrice;
		bool dailySpecial;


	public:
		FoodOrder();
		void read(std::istream& istr);
		void display() const;
	};
}

#endif