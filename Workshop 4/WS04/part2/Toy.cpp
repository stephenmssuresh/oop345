/*
File: Toy.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 13/02/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Toy.h"

using namespace std;

namespace sdds {
    double Toy::salesTax = 0.13;
    
    //3 trim functions below copied from : https://www.delftstack.com/howto/cpp/how-to-trim-a-string-cpp/
    std::string Toy::leftTrim(std::string str) {
        str.erase(0, str.find_first_not_of(' '));
        return str;
    }

    std::string Toy::rightTrim(std::string str){
        str.erase(str.find_last_not_of(' ') + 1);
        return str;
    }

    std::string Toy::trimString(std::string str) {
        return leftTrim(rightTrim(str));
    }   
    
    // string Toy::removeSpaces(const std::string& spaceString) {
    //     //remove spaces from a string
    //     size_t initialLength = 0;
    //     size_t lengthAfterRemoval = 0;
    //     std::string stringRet = spaceString;

    //     do {
    //         initialLength = stringRet.length();
    //         stringRet.erase(std::find(stringRet.begin(), stringRet.end(), ' '));
    //         lengthAfterRemoval = stringRet.length();
    //     } while (lengthAfterRemoval != initialLength);

    //     return stringRet;
    // }
    



    Toy::Toy(const std::string& toy) {
        orderID = 0; toyName = ""; noOfItems = 0; price = 0.0; salesTax = 0.13;
        //toy ex: 1000121  :  Red Bike:1  :  89.99
        //size_t delimiterPos = 0; //where the delimiter is - initialize to start of string
        if(!toy.empty()){

            char delim = ':';
            size_t substrPos1 = 0;
            size_t substrPos2 = 0;
            size_t delimPos = toy.find(delim); //first instance of delimiter
            orderID = stoi(toy.substr(substrPos1,delimPos++));
            

            substrPos1 = delimPos;
            delimPos = toy.find(delim, substrPos1);
            substrPos2 = delimPos - substrPos1;
            toyName = trimString(toy.substr(substrPos1, substrPos2));
            delimPos++;

            substrPos1 = delimPos;
            delimPos = toy.find(delim, substrPos1);
            substrPos2 = delimPos - substrPos1;
            noOfItems = stoi(toy.substr(substrPos1,substrPos2));
            //cout << endl << noOfItems<< endl;
            
            delimPos++;
            substrPos1 = delimPos;
            price = stod(toy.substr(substrPos1));

            
            //cout << endl << toyName<< endl;

            //string placeholder2 = removeSpaces(placeholder);
            //cout << endl<< placeholder << endl;
            //cout << endl<< placeholder2 << endl;
            // orderID = stoi(removeSpaces(toy.substr(0,delimiterPos)));

            // size_t delimiterPos = toyString.find(delim); 
            // orderID = stoi(removeSpaces(toyString.substr(0, delimiterPos))); //substring up to the delimiter
            // toyString.erase(0, delimiterPos + 1); //erase up up to the first char after the delimiter


            // delimiterPos = toyString.find(delim);
            // this->toyName = removeSpaces(toyString.substr(0, delimiterPos));
            // toyString.erase(0, delimiterPos + 1);
 
            // delimiterPos = toyString.find(delim);

            // this->noOfItems = stoi(removeSpaces(toyString.substr(0, delimiterPos)));
            // toyString.erase(0, delimiterPos + 1);
 

            // this->price = stod(removeSpaces(toyString));
        }

    }

    void Toy::update(int numItems) {
        noOfItems = numItems;
    }

    std::ostream& operator<<(std::ostream& os, const Toy& toy) {
        os << "Toy";
        os.setf(std::ios::right);
        os.width(8);
        os << toy.orderID << ":";

        os.width(18);
        os << toy.toyName;

        os.width(3);
        os << toy.noOfItems;
        //os.unsetf(std::ios::right);
        os << " items";

        os.width(8);
        os.setf(std::ios::fixed);
        os.precision(2);
        os << toy.price << "/item  subtotal:";

        os.width(7);
        double subtotal = toy.price * toy.noOfItems;
        os << subtotal;

        double tax = subtotal * toy.salesTax;
        os << " tax:";

        os.width(6);
        os << tax;

        os << " total:";
        os.width(7);
        os << tax + subtotal << endl;
        os.unsetf(std::ios::right);
        os.unsetf(std::ios::fixed);
        
        return os;
    }
}