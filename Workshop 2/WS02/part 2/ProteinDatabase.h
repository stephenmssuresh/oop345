/*
File: ProteinDatabase.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 29/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_PROTEINDATABSE_H
#define SDDS_PROTEINDATABSE_H

#include <string>

namespace sdds{

    class ProteinDatabase{
        int noOfProteins;
        std::string* proteins{nullptr};
        public:
        ProteinDatabase();
        ProteinDatabase(const std::string filename);
        int size();
        std::string operator[](int index);

        ProteinDatabase& operator=(const ProteinDatabase& source);
        ProteinDatabase(const ProteinDatabase& source);
        ~ProteinDatabase();

        //move constructor and assignment operator
        ProteinDatabase(ProteinDatabase&& source) noexcept;
        ProteinDatabase& operator=(ProteinDatabase&& source) noexcept;
    };

}

#endif