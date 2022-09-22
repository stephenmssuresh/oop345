// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include "Utilities.h"

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>

namespace sdds
{
    class Station
    {
        int m_stationID;           // the id of the station (integer)
        std::string m_itemName;    // the name of the item handled by the station (string)
        std::string m_stationDesc; // the description of the station (string)
        size_t m_serialNumber;     // the next serial number to be assigned to an item at this station (non-negative integer)  
        size_t m_quantity;         // the number of items currently in stock (non-negative integer)

        static size_t m_widthField; // the maximum number of characters required to print to the screen the item name for any object of type Station. Initial value is 0.
        static size_t id_generator; // a variable used to generate IDs for new instances of type Station. Every time a new instance is created, the current value of the id_generator is stored in that instance, and id_generator is incremented. Initial value is 0.

    public:
        Station();
        Station(const std::string &record);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };
}

#endif