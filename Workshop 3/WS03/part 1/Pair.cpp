/*
File: Pair.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 05/02/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/
#include <iostream>
#include "Pair.h"

namespace sdds{
    //std::ostream& operator<<(std::ostream& os, const Pair& pairs) {
    std::ostream& operator<<(std::ostream& os, Pair& pairs) {
        os.width(20);
        os << pairs.getKey();
        os << ": " << pairs.getValue();
        return os;
    }

    Pair& Pair::operator=(const int source){
        if (source == 0){
            m_key = "";
            m_value = "";
        }
        return *this;
    }

    Pair::Pair(){
        m_key = "";
        m_value = "";
    };
}