// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

namespace sdds
{
    size_t Station::m_widthField{0};
    size_t Station::id_generator{0};

    Station::Station()
    {
        m_stationID = ++id_generator; // since id_generator starts at 0
    };

    Station::Station(const std::string &record)
    {
        sdds::Utilities util;
        size_t recordPos = 0;
        bool more = false;

        m_stationID = ++id_generator; // since id_generator starts at 0

        // this constructor assumes that the string contains 4 fields separated by the delimiter
        m_itemName = util.extractToken(record, recordPos, more);
        if (more)
        {
            m_serialNumber = stoi(util.extractToken(record, recordPos, more));
        }
        if (more)
        {
            m_quantity = stoi(util.extractToken(record, recordPos, more));
        }
        // before extracting description, it updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField.
        m_widthField = std::max(Station::m_widthField, util.getFieldWidth());
        if (more)
        {
            m_stationDesc = util.extractToken(record, recordPos, more);
        }
    };

    const std::string &Station::getItemName() const
    {
        return m_itemName;
    };

    size_t Station::getNextSerialNumber()
    {
        size_t currentSerialNumber = m_serialNumber;
        m_serialNumber++;
        return currentSerialNumber;
    };

    size_t Station::getQuantity() const
    {
        return m_quantity;
    };

    void Station::updateQuantity()
    {
        if (m_quantity > 0)
        {
            m_quantity--;
        };
    };

    void Station::display(std::ostream &os, bool full) const
    {
        os << std::setw(3) << std::setfill('0') << std::right << m_stationID << " | "
           << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " | "
           << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";
        if (full)
        {
            os << std::setw(4) << std::setfill(' ') << std::right << m_quantity << " | "
               << std::setfill(' ') << std::left << m_stationDesc;
        };
        os << std::endl;
        os.unsetf(std::ios::left);
        os.unsetf(std::ios::right);
    };
}