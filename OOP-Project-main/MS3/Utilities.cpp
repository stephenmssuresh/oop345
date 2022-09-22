// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
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
        std::string strToken{};
        size_t delim = str.find_first_of(m_delimiter, next_pos);
        if (delim == next_pos)
        {
            more = false;
            throw "Error: Delimiter found at the string position next_pos";
        }

        if (delim == std::string::npos)
        {
            //extract before using next_pos as npos
            strToken = str.substr(next_pos);
            next_pos = std::string::npos;
            more = false;
        }
        else
        {
            strToken = str.substr(next_pos, (delim - next_pos));
            next_pos = delim + 1;
            more = true;
        }
        m_widthField = std::max(strToken.length(), m_widthField);
        return trimWhitespace(strToken);
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