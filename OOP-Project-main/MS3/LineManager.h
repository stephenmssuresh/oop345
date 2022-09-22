// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include "Workstation.h"
#include "Utilities.h"

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

namespace sdds
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine; // collection of workstation objects
        size_t m_cntCustomerOrder{0}; // total number of customer orders
        Workstation *m_firstStation{nullptr}; // pointer to first active workstation

    public:
        LineManager(const std::string &filename, const std::vector<Workstation *> &stations);
        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
    };
}

#endif