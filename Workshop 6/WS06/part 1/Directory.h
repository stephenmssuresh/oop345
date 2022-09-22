/*
File: Directory.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 12/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include <string>

#include "Flags.h"
#include "File.h"
#include "Resource.h"

namespace sdds
{
    class Directory : public Resource{
        std::vector<Resource*> m_contents;

        public:
        Directory();
        Directory(std::string name);

        Directory(const Directory& src) = delete;
        Directory& operator=(const Directory& src) = delete;
        Directory(const Directory&& src) = delete;
        Directory& operator=(const Directory&& src) = delete;

        void update_parent_path(const std::string& path);
        std::string name() const;
        int count() const;
        std::string path() const;
        size_t size() const;
        NodeType type() const;

        Directory& operator+=(Resource* resource);
        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
        
        ~Directory();
    };
}

#endif