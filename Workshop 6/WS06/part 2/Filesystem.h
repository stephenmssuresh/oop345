/*
File: Filesystem.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 12/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <exception>

#include "Directory.h"
#include "Resource.h"
#include "File.h"
#include "Flags.h"

namespace sdds{

    class Filesystem{
        
        Directory* m_root {nullptr};
        Directory* m_current {nullptr};

        //private members
        std::string& leftTrimWhitespace(std::string& str);
        std::string& rightTrimWhitespace(std::string& str);
        std::string& trimWhitespace(std::string& str);


        public:
        Filesystem();
        Filesystem(std::string filename, std::string rootDirectory = "");

        Filesystem(const Filesystem& src) = delete;
        Filesystem& operator=(const Filesystem& src) = delete;

        Filesystem(Filesystem&& src);
        Filesystem& operator=(Filesystem&& src);

        Filesystem& operator+=(Resource* res);
        Directory* change_directory(const std::string& dir = "");
        Directory* get_current_directory() const;

        ~Filesystem();

    };
}

#endif
