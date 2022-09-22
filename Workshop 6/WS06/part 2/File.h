/*
File: File.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 12/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <cstddef>
#include <string>

#include "Directory.h"
#include "Resource.h"
#include "Flags.h"

namespace sdds{   

    class File : public Resource {
        std::string m_contents;

        public:
        File();
        File(std::string name, std::string contents = "");

        File(const File& src) = delete;
        File& operator=(const File& src) = delete;
        File(File&& src) = delete;
        File& operator=(File&& src) = delete;

        void update_parent_path(const std::string& path);
        std::string name() const;
        int count() const;
        std::string path() const;
        size_t size() const;
        NodeType type() const;

        ~File();
    };
}

#endif