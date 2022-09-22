// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 7, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

namespace sdds
{
    // int m_stationID; // the id of the station (integer)
    // std::string m_itemName; // the name of the item handled by the station (string)
    // std::string m_stationDesc; // the description of the station (string)
    // size_t m_serialNumber; // the next serial number to be assigned to an item at this station (non-negative integer)
    // size_t m_quantity; // the number of items currently in stock (non-negative integer)

    size_t Station::m_widthField{0}; // the maximum number of characters required to print to the screen the item name for any object of type Station. Initial value is 0.
    size_t Station::id_generator{0}; // a variable used to generate IDs for new instances of type Station. Every time a new instance is created, the current value of the id_generator is stored in that instance, and id_generator is incremented. Initial value is 0.

    Station::Station()
    {
        m_stationID = ++id_generator; // since it starts at 0
    };

    Station::Station(const std::string &record)
    {
        std::cout << "In Station 1-arg constructor" << std::endl;
        sdds::Utilities util;
        size_t recordPos = 0;
        bool more = false;

        m_stationID = ++id_generator; // since it starts at 0
                                      // id_generator++;

        // this constructor assumes that the string contains 4 fields separated by the delimiter, in the following order:

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