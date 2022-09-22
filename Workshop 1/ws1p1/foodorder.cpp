/*
File: foodorder.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 20/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#include<iostream>
#include<fstream>
#include <iomanip>
#include <string>
#include <cstring>

#include "foodorder.h"

double g_taxrate;
double g_dailydiscount;

using namespace std; 

namespace sdds {
	FoodOrder::FoodOrder() {
		customerName[0] = '\0';
		foodDesc[0] = '\0';
		foodPrice = 0.0;
		dailySpecial = false;
	}

	void FoodOrder::read(std::istream& istr) { //ifstream is an istream object
		char special = '\0';
		if (istr.good()) {
			//istr >> customerName;
			//istr.ignore();
			//char tempstring[7];
			istr.getline(customerName,10, ',');

			istr.getline(foodDesc, 25, ',');
			
			//istr.getline(tempstring, ',');
			//cout << endl << tempstring << endl;
			//foodPrice = atof(tempstring);

			istr >> foodPrice;
			istr.ignore();

			istr >> special;

			if (special == 'Y') {
				dailySpecial = true;
			}
			else if (special == 'N') {
				dailySpecial = false;
			}
			//cout << endl << "special: " << special << endl;
			//cout << "dailySpecial bool: " << dailySpecial << endl;
		}
		//cout << endl;
		//cout << customerName << endl;
		//cout << foodDesc << endl;
		//cout << foodPrice << endl;
		//cout << special << endl;
	}

	void FoodOrder::display() const {
		//sample output:
		//2 . Julian    |8 Piece Sushi Set        |9.03        |         7.88
		static int counter = 0;
		counter++;
		//cout.fill(' ');
		
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
		}
		else {
			cout << "No Order" << endl;
		}

	}
}