/*
File: ConfirmOder.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 13/02/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/
#include <iostream>
#include <iomanip>
#include <string>
#include "ConfirmOrder.h"
#include "Toy.h"

using namespace std;

namespace sdds {

    ConfirmOrder::ConfirmOrder(const ConfirmOrder& src) {
        *this = src;
    }

    ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& src) {
        if (this != &src && src.toyOrders != nullptr) {
            count = src.count;

            // for(auto i =0u; i < count; i++){
            //     delete toyOrders[i];
            // }
            delete[] toyOrders;


            toyOrders = new const Toy * [count];
            for (auto i = 0u; i < count; i++) {
                if (src.toyOrders != nullptr) {
                    toyOrders[i] = src.toyOrders[i];
                }
            }
        }
        return *this;
    }

    //destructor
    ConfirmOrder::~ConfirmOrder() {
        delete[] toyOrders;


    }

    //move
    ConfirmOrder::ConfirmOrder(ConfirmOrder&& src) noexcept {
        *this = std::move(src);
    }

    ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& src) noexcept {
        if (this != &src && src.toyOrders != nullptr) {
            // delete[] toyOrders;

            delete[] toyOrders;
            //toyOrders = new const Toy * [count];

            count = src.count;
            src.count = 0;
            toyOrders = src.toyOrders;
            src.toyOrders = nullptr;
        }
        return *this;
    }

    //overloaded operators
    ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy) {
        bool inside = false;
        for (auto i = 0u; i < count && inside == false; i++) {
            if (toyOrders[i] == &toy) {
                inside = true;
            }
        }
        if (!inside) {
            const Toy** toyTemp = new const Toy * [count + 1];
            for (auto i = 0u; i < count; i++) {
                toyTemp[i] = toyOrders[i];
            }
            delete[] toyOrders;
            toyTemp[count++] = &toy;
            toyOrders = move(toyTemp);
        }
        return *this;
    }

    ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
        for (auto i = 0u; i < count; i++) {
            if (toyOrders[i] == &toy) {
                toyOrders[i] = nullptr;
                count--;
            }
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ConfirmOrder& child) {
        os << "--------------------------" << endl;
        os << "Confirmations to Send" << endl;
        os << "--------------------------" << endl;
        if (child.count == 0) {
            os << "There are no confirmations to send!" << endl;
        }
        else {
            for (auto i = 0u; i < child.count; i++) {
                if (child.toyOrders[i] != nullptr) {
                    os << *child.toyOrders[i];
                }
            }
        }
        os << "--------------------------" << endl;
        return os;
    }
}