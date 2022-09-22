// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 7, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds
{
    Utilities::Utilities(){};

    char Utilities::m_delimiter{' '};

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    };

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    };

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        // //next_pos - position of the next delimiter

        // // variable to store the token that will be returned at the end
        // std::string strToken{""};

        // //no of chars to extract from the string 'str' (to be used in substr() function)
        // size_t noOfChars = 0;

        // // get location of the next delimiter starting from next_pos position in the string
        // // get position of delimiter and find out how many chars to extract from str
        // // https://www.cplusplus.com/reference/string/string/find_first_of/
        // size_t end_pos = str.find_first_of(m_delimiter, next_pos);

        // //
        // if (end_pos == next_pos)
        // {
        //     more = false; // set to false because more is used to loop through a string
        //     throw "Error: Delimiter found at the string position next_pos";
        // }

        // // if delimiter was not found, you are extracting the last token so bool more = false and next_pos = end of string
        // if (end_pos == std::string::npos)
        // {
        //     next_pos = std::string::npos;
        //     more = false;
        //     noOfChars = end_pos;
        // }
        // else
        // {
        //     noOfChars = end_pos - next_pos;
        //     more = true;
        // }

        // strToken = str.substr(next_pos, (noOfChars)); //if end_pos == string::npos, substr til end of string, else substr for the number of characters in the token

        // //updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
        // // if( m_widthField < strToken.length()){
        // //     m_widthField = strToken.length();
        // // }
        // m_widthField = std::max(strToken.length(), m_widthField);

        // // if (end_pos != std::string::npos){ //no need because of more bool?
        // next_pos = end_pos + 1;
        // // }

        // return trimWhitespace(strToken);

        ///////////////////////////////////////////////////////////////////
        // test
        std::string token{};
        size_t delimPos = str.find_first_of(m_delimiter, next_pos);
        if (delimPos == next_pos)
        {
            more = false;
            throw "Error: Delimiter found at the string position next_pos";
        }

        if (delimPos == std::string::npos)
        {
            token = str.substr(next_pos);
            next_pos = std::string::npos;
            more = false;
        }
        else
        {
            token = str.substr(next_pos, (delimPos - next_pos));
            next_pos = delimPos + 1;
            more = true;
        }
        m_widthField = std::max(token.length(), m_widthField);
        return trimWhitespace(token);
    };

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    };

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    };

    std::string &Utilities::leftTrimWhitespace(std::string &str)
    {
        str.erase(0, str.find_first_not_of(' '));
        return str;
    }
    std::string &Utilities::rightTrimWhitespace(std::string &str)
    {
        str.erase(str.find_last_not_of(' ') + 1);
        return str;
    }
    std::string &Utilities::trimWhitespace(std::string &str)
    {
        return leftTrimWhitespace(rightTrimWhitespace(str));
    }
}