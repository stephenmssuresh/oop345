/*
File: CovidCollection.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 19/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>

namespace sdds
{
    struct Covid
    {
        std::string country{""};
        std::string city{""};
        std::string variant{""};
        int numberOfCases{0};
        int year{0};
        int m_deaths{0};

        Covid(){};
        Covid(std::string cntry, std::string cty, std::string var, int cases, int yr, int deaths);
    };

    class CovidCollection
    {
        std::vector<Covid> covidCol;

        //helpers to trim the strings
        std::string& leftTrimWhitespace(std::string& str);
        std::string& rightTrimWhitespace(std::string& str);
        std::string& trimWhitespace(std::string& str);

    public:
        CovidCollection(){};
        CovidCollection(std::string filename);
        void display(std::ostream &out) const;

        void sort(std::string field);
        void cleanList();
        bool inCollection(std::string variantName) const;
        std::list<Covid> getListForCountry(std::string countryName) const;
        std::list<Covid> getListForVariant(std::string variantName) const;
    };
    std::ostream &operator<<(std::ostream &out, const Covid &theCovid);
}

#endif