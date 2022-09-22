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
        numberOfDeaths = deaths;
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
        out << std::right << " | " << std::setw(4) << theCovid.numberOfCases << " | " << std::setw(3) << theCovid.numberOfDeaths << " |" << std::endl;
        out.unsetf(std::ios::right);

        return out;
    }

    void CovidCollection::display(std::ostream &out) const
    {
        // size_t totalCases = 0;
        // size_t totalDeaths = 0;
        for_each(this->covidCol.begin(), this->covidCol.end(), [&](Covid i)
                 { std::cout << i; 
                //  totalCases += i.numberOfCases; 
                //  totalDeaths += i.numberOfDeaths; 
                });
        // std::cout.fill('-');
        // std::cout << std::setw(89) << "\n";
        // std::cout.fill(' ');

        // std::cout << "|" << std::right << std::setw(78) << "Total Cases Around the World:" << std::setw(7) << totalCases << " |" << std::endl;
        // std::cout << "|" << std::right << std::setw(78) << "Total Deaths Around the World:" << std::setw(7) << totalDeaths << " |" << std::endl;
    }

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