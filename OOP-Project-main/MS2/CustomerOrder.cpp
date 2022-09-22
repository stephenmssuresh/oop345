// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 7, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"

namespace sdds
{
    size_t CustomerOrder::m_widthField{0};

    CustomerOrder::CustomerOrder()
    {
    }

    CustomerOrder::CustomerOrder(const CustomerOrder &source)
    {
        throw "Copy operations are not allowed!";
    }

    CustomerOrder::CustomerOrder(const std::string &record)
    {
        //this was a mistake
        //size_t m_cntItem = 0;

        m_cntItem = 0;
        sdds::Utilities util;
        size_t recordPos = 0;
        bool more = false;

        // for creatig the m_lstItem array
        size_t itemsInRecord = 0;

        m_name = util.extractToken(record, recordPos, more);
        if (more)
        {
            m_product = util.extractToken(record, recordPos, more);
        }
        if (more)
        {
            // create a new Utilities object and count the number of items in the record
            sdds::Utilities util2;
            bool more2 = more;
            size_t recordPos2 = recordPos;
            std::string notUsed;
            while (more2)
            {
                notUsed = util.extractToken(record, recordPos2, more2);
                itemsInRecord++;
            }
        }
        // could have also used std::count() function and iterator
        // https://www.techiedelight.com/count-occurrences-char-string-cpp/
        // allocate memory for the same number of items in the record
        m_lstItem = new Item *[itemsInRecord];
        m_cntItem = itemsInRecord;

        // doesn't work??
        // m_cntItem = itemsInRecord;

        // add items to the array
        // can also use for loop
        // while (more)
        // {
        //     //doesn't work because of the mistake
        //     // m_lstItem[m_cntItem++] = new Item(util.extractToken(record, recordPos, more));
        //     m_lstItem[m_cntItem] = new Item(util.extractToken(record, recordPos, more));
        //     m_cntItem++;
        //     std::cout << "m_cntItem = "<< m_cntItem << std::endl;
        // }
        for (size_t i = 0; i < m_cntItem && more; i++)
        {
            m_lstItem[i] = new Item(util.extractToken(record, recordPos, more));
        }
        m_widthField = std::max(m_widthField, util.getFieldWidth());
    }

    bool CustomerOrder::isOrderFilled() const
    {
        bool retvalue = true;
        for (size_t i = 0; i < m_cntItem && retvalue; i++)
        {
            if (!m_lstItem[i]->m_isFilled)
            {
                retvalue = false;
            }
        }
        return retvalue;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        bool retvalue = true;
        for (size_t i = 0; i < m_cntItem && retvalue; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
            {
                retvalue = false;
            }
        }
        return retvalue;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        bool exit = false;
        for (size_t i = 0; i < m_cntItem && !exit; i++)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false)
            {
                if (station.getQuantity() > 0)
                {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    exit = true;
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << m_name << ", " << m_product << "[" << station.getItemName() << "]" << std::endl;
                }
                else
                {
                    os << "Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                    exit = true;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::setw(CustomerOrder::m_widthField) << std::left << this->m_lstItem[i]->m_itemName << " - ";
            if (m_lstItem[i]->m_isFilled)
            {
                os << "FILLED" << std::endl;
            }
            else
            {
                os << "TO BE FILLED" << std::endl;
            }
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&source) noexcept
    {
        *this = std::move(source);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&source) noexcept
    {
        if (this != &source)
        {
            for (size_t i = 0; i < m_cntItem; i++)
            {
                delete this->m_lstItem[i];
            }
            delete[] m_lstItem;
            m_lstItem = source.m_lstItem;
            m_name = source.m_name;
            m_product = source.m_product;
            m_cntItem = source.m_cntItem;

            source.m_lstItem = nullptr;

            //needed for destructor for source
            source.m_cntItem = 0;

            // source.m_name = "";
            // source.m_product = "";
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }
}