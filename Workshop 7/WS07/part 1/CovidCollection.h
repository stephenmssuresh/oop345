#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <list>
#include <vector>
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
        int numberOfDeaths{0};

        Covid(){};
        Covid(std::string cntry, std::string cty, std::string var, int cases, int yr, int deaths);
    };

    class CovidCollection
    {
        std::list<Covid> covidCol;

        //to trim the strings
        std::string& leftTrimWhitespace(std::string& str);
        std::string& rightTrimWhitespace(std::string& str);
        std::string& trimWhitespace(std::string& str);

    public:
        CovidCollection(){};
        CovidCollection(std::string filename);
        void display(std::ostream &out) const;
    };
    std::ostream &operator<<(std::ostream &out, const Covid &theCovid);
}

#endif