/*
File: Filesystem.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 12/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include "Filesystem.h"

namespace sdds
{
    Filesystem::Filesystem() {}

    Filesystem::Filesystem(std::string filename, std::string rootDirectory)
    {
        m_root = new Directory(rootDirectory);
        //m_current = new Directory;
        std::ifstream file(filename);
        if (!file)
        {
            delete m_root;
            delete m_current;
            throw "Invalid File Name";
        }
        change_directory(); //put m_current = m_root

        std::string items;
        size_t noOfLines = 0;
        std::string line;

        do
        {
            std::getline(file, items);
            if (file)
            {
                noOfLines++;
            }
        } while (file);

        // clear eof and fail flags
        file.clear();
        // set position of next character extracted to be the beginning
        file.seekg(std::ios::beg);

        for (size_t i = 0; i < noOfLines; i++)
        {
            this->change_directory(); // go to root
            std::getline(file, line);
            bool done = false;

            size_t found = line.find_first_of("/|");
            size_t initPos = 0; // start at position 0 of the string

            // if(found != std::string::npos){
            //     std::cout << "found is successful " << found << std::endl;
            // }

            while (found != std::string::npos)
            {
                if (line[found] == '/')
                {
                    std::string dirname = line.substr(initPos, found - initPos + 1);
                    trimWhitespace(dirname);
                    // dirname += '/';
                    
                    if (!m_current->find(dirname))
                    {
                        // std::cout << std::endl << "added directory :"
                        //       << dirname << std::endl; // to remove
                        try
                        {
                            *m_current += new Directory(dirname);
                        }
                        catch (...)
                        {
                            std::cout << "error with the += operator in directory";
                        }
                    }
                    this->change_directory(dirname);
                }
                else if (line[found] == '|')
                {
                    std::string filename = line.substr(initPos, found - initPos - 1);
                    trimWhitespace(filename);
                    initPos = found + 1;
                    found = line.find_first_of("/|", initPos);
                    std::string contents = line.substr(initPos, found - initPos - 1);
                    trimWhitespace(contents);
                    // std::cout << std::endl
                    //           << filename << std::endl
                    //           << contents << std::endl; // to remove
                    if (!m_current->find(filename))
                    {
                        try
                        {
                            *m_current += new File(filename, contents);
                        }
                        catch (std::string str)
                        {
                            std::cout << str;
                        }
                    }
                    done = true;
                }
                if (!done)
                {
                    initPos = found + 1;
                    found = line.find_first_of("/|", initPos);
                }
            }
        }
        change_directory(rootDirectory);
    }

    Filesystem::Filesystem(Filesystem &&src)
    {
        *this = std::move(src);
    }

    Filesystem &Filesystem::operator=(Filesystem &&src)
    {
        if (this != &src)
        {
            delete m_root;
            delete m_current;
            m_root = src.m_root;
            m_current = src.m_current;

            //forgot the nullptr before submitting
            src.m_root = nullptr;
            src.m_current = nullptr;
        }
        return *this;
    }

    Filesystem &Filesystem::operator+=(Resource *res)
    {
        (*m_current) += res;
        return *this;
    }

    Directory *Filesystem::change_directory(const std::string &dir)
    {
        if (dir.length() == 0)
        {
            m_current = m_root;
        }
        else
        {
            std::vector<sdds::OpFlags> oflags;
            oflags.push_back(sdds::OpFlags::RECURSIVE);
            Resource *test = m_root->find(dir, oflags);
            if (test != nullptr && test->type() == NodeType::DIR)
            {
                m_current = dynamic_cast<Directory *>(test);
            }
            else
            {
                throw std::invalid_argument("Cannot change directory! DIR_NAME not found!");
            }
        }
        return m_current;
    }

    Directory *Filesystem::get_current_directory() const
    {
        return m_current;
    }

    Filesystem::~Filesystem()
    {
        delete m_root;
        //delete m_current;
    }

    std::string &Filesystem::leftTrimWhitespace(std::string &str)
    {
        str.erase(0, str.find_first_not_of(' '));
        return str;
    }

    std::string &Filesystem::rightTrimWhitespace(std::string &str)
    {
        str.erase(str.find_last_not_of(' ') + 1);
        return str;
    }

    std::string &Filesystem::trimWhitespace(std::string &str)
    {
        return leftTrimWhitespace(rightTrimWhitespace(str));
    }
}