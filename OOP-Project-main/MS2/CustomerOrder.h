// Name: Stephen Suresh
// Seneca Student ID: 117916213
// Seneca email: ssuresh15@myseneca.ca
// Date of completion: April 7, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>
#include <iostream>
#include <iomanip>

#include "Utilities.h"
#include "Station.h"

namespace sdds
{
    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string &src) : m_itemName(src){};
    };

    class CustomerOrder
    {
        std::string m_name{};      // the name of the customer (e.g., John, Sara, etc)
        std::string m_product{};   // the name of the product being assembled (e.g., Desktop, Laptop, etc)
        size_t m_cntItem{0};       // a count of the number of items in the customer's order
        Item **m_lstItem{nullptr}; // a dynamically allocated array of pointers. Each element of the array points to a dynamically allocated object of type Item (see below). This is the resource that your class must manage.

        static size_t m_widthField; // the maximum width of a field, used for display purposes

    public:
        CustomerOrder();
        CustomerOrder(const std::string &record);

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;

        // rule of 5
        CustomerOrder(const CustomerOrder &source);
        CustomerOrder &operator=(const CustomerOrder &source) = delete;

        CustomerOrder(CustomerOrder &&source) noexcept;
        CustomerOrder &operator=(CustomerOrder &&source) noexcept;
        ~CustomerOrder();
    };
}

#endif