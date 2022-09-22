/*
File: CovidCollection.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 19/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include "CovidCollection.h"

namespace sdds
{
    Covid::Covid(std::string cntry, std::string cty, std::string var, int cases, int yr, int deaths)
    {
        country = cntry;
        city = cty;
        variant = var;
        numberOfCases = cases;
        year = yr;
        m_deaths = deaths;
    }

    CovidCollection::CovidCollection(std::string filename)
    {
        std::string line;
        std::string cntry;
        std::string cty;
        std::string var;
        int cases;
        int yr;
        int deaths;

        std::ifstream file(filename);
        if (!file)
        {
            throw "Invalid File Name";
        }
        while (file.good())
        {
            getline(file, line);
            if (!file.eof())
            {
                cntry = line.substr(0, 25);
                trimWhitespace(cntry);

                cty = line.substr(25, 25);
                trimWhitespace(cty);

                var = line.substr(50, 25);
                trimWhitespace(var);

                yr = stoi(line.substr(75, 5));
                cases = stoi(line.substr(80, 5));
                deaths = stoi(line.substr(85));

                Covid covidToAdd = Covid(cntry, cty, var, cases, yr, deaths);
                this->covidCol.push_back(covidToAdd);
            }
        }
    }

    std::ostream &operator<<(std::ostream &out, const Covid &theCovid)
    {
        out.fill(' ');

        out << "| " << std::left << std::setw(21) << theCovid.country << " | " << std::setw(15) << theCovid.city << " | " << std::setw(20) << theCovid.variant << " | ";

        out.setf(std::ios::right);
        if (theCovid.year > 0)
        {
            out << std::right << std::setw(6) << theCovid.year;
        }
        else
        {
            out << std::setw(6) << " ";
        }
        out << std::right << " | " << std::setw(4) << theCovid.numberOfCases << " | " << std::setw(3) << theCovid.m_deaths << " |"; // << std::endl;
        out.unsetf(std::ios::right);

        return out;
    }

    void CovidCollection::sort(std::string field)
    {
        // https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
        if (field == "country")
        {
            std::sort(this->covidCol.begin(), this->covidCol.end(), [=](Covid &val1, Covid &val2)
                      { return val1.country < val2.country; });
        }
        else if (field == "variant")
        {
            std::sort(this->covidCol.begin(), this->covidCol.end(), [=](Covid &val1, Covid &val2)
                      { return val1.variant < val2.variant; });
        }
        else if (field == "cases")
        {
            std::sort(this->covidCol.begin(), this->covidCol.end(), [=](Covid &val1, Covid &val2)
                      { return val1.numberOfCases < val2.numberOfCases; });
        }
        else if (field == "deaths")
        {
            std::sort(this->covidCol.begin(), this->covidCol.end(), [=](Covid &val1, Covid &val2)
                      { return val1.m_deaths < val2.m_deaths; });
        }
        else
        {
            std::cout << "Invalid Field";
        }
    }

    void CovidCollection::cleanList()
    {
        std::string empty = "";
        // std::replace_if(
        //     this->covidCol.begin(), this->covidCol.end(), [](Covid &val1, Covid &val2)
        //     { return val1.variant == "[None]"; }, empty);
        // std::for_each(this->covidCol.begin(), this->covidCol.end(), [&](Covid& i)
        //          { if(i.variant == "[None]") i.variant = ""; });
        std::transform(this->covidCol.begin(), this->covidCol.end(), this->covidCol.begin(), [&](Covid &i)
                       {  Covid returnObject(i.country, i.city, i.variant, i.numberOfCases, i.year, i.m_deaths);
                          if(i.variant == "[None]") returnObject.variant = ""; 
                      return returnObject; });
        // Covid::Covid(std::string cntry, std::string cty, std::string var, int cases, int yr, int deaths)
    }

    bool CovidCollection::inCollection(std::string variantName) const
    {
        return (std::any_of(this->covidCol.begin(), this->covidCol.end(), [&](Covid i)
                            { return i.variant == variantName; }));
    }

    std::list<Covid> CovidCollection::getListForCountry(std::string countryName) const
    {
        // https://stackoverflow.com/questions/60101088/deleting-empty-elements-from-vector
        // https://stackoverflow.com/questions/7958216/c-remove-if-on-a-vector-of-objects
        std::list<Covid> copyList(this->covidCol.size());
        std::copy(this->covidCol.begin(), this->covidCol.end(), copyList.begin());
        
        // https://stackoverflow.com/questions/39019806/using-erase-remove-if-idiom
        copyList.erase(std::remove_if(std::begin(copyList), std::end(copyList), [=](Covid &i)
                                      { return i.country == countryName; }),
                       std::end(copyList));
        return copyList;
    }

    std::list<Covid> CovidCollection::getListForVariant(std::string variantName) const
    {
        // https://stackoverflow.com/questions/60101088/deleting-empty-elements-from-vector
        // https://stackoverflow.com/questions/7958216/c-remove-if-on-a-vector-of-objects
        std::list<Covid> copyList(this->covidCol.size());
        std::copy_if(this->covidCol.begin(), this->covidCol.end(), copyList.begin(), [=](Covid i)
                     { return (i.variant == variantName); });
        // https://stackoverflow.com/questions/39019806/using-erase-remove-if-idiom
        copyList.erase(std::remove_if(std::begin(copyList), std::end(copyList), [](Covid &i)
                                      { return i.country.empty(); }),
                       std::end(copyList));
        return copyList;
    }

    void CovidCollection::display(std::ostream &out) const
    {
        size_t totalCases = 0;
        size_t totalDeaths = 0;
        std::for_each(this->covidCol.begin(), this->covidCol.end(), [&](Covid i)
                      { std::cout << i << std::endl; 
                  totalCases += i.numberOfCases; 
                  totalDeaths += i.m_deaths; });
        std::cout.fill('-');
        std::cout << std::setw(89) << "\n";
        std::cout.fill(' ');

        std::cout << "|" << std::right << std::setw(78) << "Total Cases Around the World:" << std::setw(7) << totalCases << " |" << std::endl;
        std::cout << "|" << std::right << std::setw(78) << "Total Deaths Around the World:" << std::setw(7) << totalDeaths << " |" << std::endl;
    }

    // helpers
    std::string &CovidCollection::leftTrimWhitespace(std::string &str)
    {
        str.erase(0, str.find_first_not_of(' '));
        return str;
    }

    std::string &CovidCollection::rightTrimWhitespace(std::string &str)
    {
        str.erase(str.find_last_not_of(' ') + 1);
        return str;
    }

    std::string &CovidCollection::trimWhitespace(std::string &str)
    {
        return leftTrimWhitespace(rightTrimWhitespace(str));
    }
}