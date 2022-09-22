/*
File: foodorder.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 20/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include <iomanip>
#include <string>
#include <cstring>

#include "foodorder.h"

double g_taxrate = 10;
double g_dailydiscount = 10;

const static int MAX_DESC_LEN = 50; //set max length for reading a foodDesc string in read()

using namespace std; 

namespace sdds {
	FoodOrder::FoodOrder() {
		customerName[0] = '\0';
		foodPrice = 0.0;
		dailySpecial = false;
		foodDesc = nullptr;
	}

	void FoodOrder::read(std::istream& istr) { 
		char special = '\0';
		char descTemp[MAX_DESC_LEN + 1]{};
		
		if (istr.good()) {

			istr.getline(customerName, 10, ',');

			istr.getline(descTemp, MAX_DESC_LEN, ',');

			delete[] foodDesc;
			foodDesc = nullptr;

			foodDesc = new char[strlen(descTemp) + 1];
			strcpy(foodDesc, descTemp);

			istr >> foodPrice;
			istr.ignore();

			istr >> special;

			if (special == 'Y') {
				dailySpecial = true;
			}
			else if (special == 'N') {
				dailySpecial = false;
			}
		}
	}

	void FoodOrder::display() {
		static int counter = 0;
		counter++;
		
		cout.width(2);
		cout.setf(ios::left);
		cout << counter;

		cout << ". ";

		if (strlen(customerName) != 0) {
			cout.width(10);
			cout << customerName;

			cout << "|";

			cout.width(25);
			cout << foodDesc;

			cout << "|";

			cout.width(12);
			cout.setf(ios::fixed);
			cout.precision(2);
			//double tax = g_taxrate;
			cout << foodPrice * (1 + g_taxrate);
			cout.unsetf(ios::fixed);
			cout.unsetf(ios::left);

			cout << "|";
			if (dailySpecial == true) {
				cout.setf(ios::fixed);
				cout.width(13);
				cout.setf(ios::right);
				//double discount = g_dailydiscount;
				cout << (foodPrice * (1 + g_taxrate)) - g_dailydiscount;
				cout.unsetf(ios::fixed);
				cout.unsetf(ios::right);
			}
			cout << endl;
			//delete[] foodDesc;
			//foodDesc = nullptr;
		}
		else {
			cout << "No Order" << endl;
		}
	}

	FoodOrder& FoodOrder::operator=(FoodOrder& source) {
		if (this != &source && source.foodDesc != nullptr) {
			strcpy(customerName, source.customerName);
			foodPrice = source.foodPrice;
			dailySpecial = source.dailySpecial;

			delete[] foodDesc;
			foodDesc = nullptr;
			foodDesc = new char[strlen(source.foodDesc) + 1];
			strcpy(foodDesc, source.foodDesc);

			//delete[] source.foodDesc;
			//source.foodDesc = nullptr;
		}
		return *this;
	}
	
	FoodOrder::FoodOrder(const FoodOrder& source) {
		foodPrice = source.foodPrice;
		strcpy(customerName, source.customerName);
		dailySpecial = source.dailySpecial;
		if (source.foodDesc != nullptr) {
			foodDesc = new char[strlen(source.foodDesc) + 1];
			strcpy(foodDesc, source.foodDesc);
		}
	}

	FoodOrder::~FoodOrder() {
		delete[] foodDesc;
		foodDesc = nullptr;
	}

}