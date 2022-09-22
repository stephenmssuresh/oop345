/*
File: File.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 12/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include "File.h"

namespace sdds{
    File::File(){}

    File::File(std::string name, std::string contents){
        m_contents = contents;
        m_name = name;
    }

    void File::update_parent_path(const std::string& path){
        m_parent_path = path;
    }

    std::string File::name() const{
        return m_name;
    }

    int File::count() const{
        return -1;
    }

    std::string File::path() const{
        return (m_parent_path + m_name);
    }

    size_t File::size() const{
        return m_contents.length();
    }

    NodeType File::type() const{
        return NodeType::FILE;
    }

    File::~File(){

    }
    
}