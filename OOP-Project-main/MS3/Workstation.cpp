// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 10, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds
{
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(std::string &record) : Station(record) {}

    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        bool moved = false;
        // attempts to move the order order at the front of the queue to the next station in the assembly line:
        // can use reference instead of pointer
        CustomerOrder *order = &(m_orders.front());

        if (!m_orders.empty())
        {
            if (order->isItemFilled(this->getItemName()) || this->getQuantity() < 1)
            {
                if (this->getNextStation() != nullptr)
                {
                    *(this->getNextStation()) += std::move(m_orders.front());
                }
                else // if item was at the last station
                {
                    if (order->isOrderFilled())
                    {
                        // move order into g_completed
                        g_completed.push_back(std::move(*order));
                    }
                    else
                    {
                        // move order into g_incomplete
                        g_incomplete.push_back(std::move(*order));
                    }
                }
                moved = true;
                // remove order from m_orders
                m_orders.pop_front();
            }
        }
        return moved;
    }

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const
    {
        os << this->getItemName() << " --> ";
        if (this->getNextStation() == nullptr)
        {
            os << "End of Line" << std::endl;
        }
        else
        {
            os << (this->getNextStation())->getItemName() << std::endl;
        }
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        (this->m_orders).push_back(std::move(newOrder));
        return *this;
    }

   // Workstation::~Workstation() {}
}