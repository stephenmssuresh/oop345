// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

#include <deque>
#include <iomanip>
#include <iostream>

namespace sdds
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;   // orders processed by this workstation
        Workstation *m_pNextStation{nullptr}; // pointer to the next station on the assembly line

    public:
        Workstation(std::string &record);
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station = nullptr);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);

        // cannot be copied or moved
        Workstation(const Workstation &source) = delete;
        Workstation &operator=(const Workstation &source) = delete;
        Workstation(Workstation &&source) = delete;
        Workstation &operator=(Workstation &&source) = delete;
        // ~Workstation();
    };
}

#endif