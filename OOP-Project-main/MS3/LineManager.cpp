// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"

namespace sdds
{
    LineManager::LineManager(const std::string &filename, const std::vector<Workstation *> &stations)
    {
        Utilities util;
        std::string record;
        std::string currentWorkstation;
        std::string nextWorkstation;

        util.setDelimiter('|');

        if (filename.empty())
        {
            throw std::string("ERROR: No filename provided.");
        }
        std::ifstream file(filename);
        if (!file)
        {
            throw std::string("Unable to open [") + filename + "] file.";
        }

        while (!file.eof())
        {

            size_t recordPos = 0;
            bool more = false;

            std::getline(file, record);

            // get first token in the line
            currentWorkstation = (util.extractToken(record, recordPos, more));

            // store the ordered workstations in  the member vector m_activeLine
            // std::vector<Workstation *>::const_iterator
            auto currentWSFromVector = std::find_if(stations.cbegin(), stations.cend(), [currentWorkstation](const Workstation *ws)
                                                    { return ws->getItemName() == currentWorkstation; });

            // https://www.cplusplus.com/reference/algorithm/find_if/
            // if it was not found
            if (currentWSFromVector == stations.cend())
            {
                throw std::string("Was not able to find the Workstation '" + currentWorkstation + "' in the file");
            }
            // dereference the iterator
            m_activeLine.push_back(*currentWSFromVector);

            // get the 2nd token in the line if any
            if (more)
            {
                nextWorkstation = (util.extractToken(record, recordPos, more));
                std::vector<Workstation *>::const_iterator nextWSFromVector = std::find_if(stations.cbegin(), stations.cend(), [nextWorkstation](const Workstation *ws)
                                                                                           { return ws->getItemName() == nextWorkstation; });
                if (nextWSFromVector == stations.cend())
                {
                    throw std::string("Was not able to find the Workstation '" + nextWorkstation + "' in the vector");
                }
                // use the iterator to set m_pNextStation to the found station
                (*currentWSFromVector)->setNextStation(*nextWSFromVector);
            }
            // else //  read the last workstation
            // {
            //     // redundant
            //     (*currentWSFromVector)->setNextStation(nullptr);
            // }
        }
        file.close();

        // get the first workstation
        // go through the workstations, if the workstation is the next for another workstation it is not the first.
        // check to see if a workstation has a previous workstation
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [this](Workstation *firstCheck)
                      {
            //std::vector<Workstation *>::iterator
            auto hasPrevious = std::find_if(m_activeLine.begin(), m_activeLine.end(), [firstCheck](Workstation *ws){
                return ws->getNextStation() == firstCheck; 
            });
            if (hasPrevious == m_activeLine.end())
            {
                m_firstStation = firstCheck;
            } });

        if (!m_firstStation)
        {
            throw std::string("Error: Not able to find the first workstation");
        }
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        // sort the station from 1st station to last
        std::vector<Workstation *> sortedVector;

        // have the first workstation already
        Workstation *ws = m_firstStation;
        while (ws) // last ws has nullptr
        {
            // first iteration - m_firstStation
            sortedVector.push_back(ws);
            // check the first workstation's nextWorkstation and then push it into sortedVector
            ws = ws->getNextStation();
        }
        // move the resources in the sorted vector to the member vector
        m_activeLine = std::move(sortedVector);
    }

    bool LineManager::run(std::ostream &os)
    {
        // track number of times run() is called
        static size_t iterations = 0;

        os << "Line Manager Iteration: " << ++iterations << std::endl;

        if (!g_pending.empty())
        {
            (*m_firstStation) += std::move(g_pending.front());
            g_pending.pop_front();
        }

        // for each station on the line, executes one fill operation
        for (auto iter = m_activeLine.begin(); iter != m_activeLine.end(); iter++)
        {
            (*iter)->fill(os);
        }

        // for each station on the line, attempts to move an order down the line
        for (auto iter = m_activeLine.begin(); iter != m_activeLine.end(); iter++)
        {
            (*iter)->attemptToMoveOrder();
        }

        return ((g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder);
    }

    void LineManager::display(std::ostream &os) const
    {
        for (auto iter = m_activeLine.begin(); iter != m_activeLine.end(); iter++)
        {
            (*iter)->display(os);
        }
    }
}