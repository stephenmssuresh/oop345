/*
File: ConfirmOder.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 13/02/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_CONFIRMORDER_H
#define SDDS_CONFIRMORDER_H

#include "Toy.h"

namespace sdds {
    class ConfirmOrder {
        const sdds::Toy** toyOrders{ nullptr };

        size_t count{ 0u };

    public:
        ConfirmOrder() {};

        //copy
        ConfirmOrder(const ConfirmOrder& src);
        ConfirmOrder& operator=(const ConfirmOrder& src);

        //destructor
        ~ConfirmOrder();

        //move
        ConfirmOrder(ConfirmOrder&& src) noexcept;
        ConfirmOrder& operator=(ConfirmOrder&& src) noexcept;

        ConfirmOrder& operator+=(const Toy& toy);

        ConfirmOrder& operator-=(const Toy& toy);

        friend std::ostream& operator<<(std::ostream& os, const ConfirmOrder& child);
    };
}

#endif