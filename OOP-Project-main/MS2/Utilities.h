// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 7, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <cstddef>
#include <iostream>
#include <string>
#include <algorithm> //for std::max()
// #include <cmath>

namespace sdds
{
    class Utilities
    {
        size_t m_widthField{1};
        static char m_delimiter;

        // helpers to trim strings:
        std::string &leftTrimWhitespace(std::string &str);
        std::string &rightTrimWhitespace(std::string &str);
        std::string &trimWhitespace(std::string &str);

    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string &str, size_t &next_pos, bool &more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };
}

#endif