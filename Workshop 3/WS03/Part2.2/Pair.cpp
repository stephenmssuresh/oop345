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
    std::ostream& operator<<(std::ostream& os, const Pair& pairs) {
        os.width(20);
        os << pairs.m_key;
        os << ": " << pairs.m_value;
        return os;
    }

    Pair::Pair(){
        m_key = "";
        m_value = "";
    };

    bool operator==(const Pair& pair1, const Pair& pair2){
        //return(pair1.m_key == pair2.m_key && pair1.m_value == pair2.m_value);
        return(pair1.m_key == pair2.m_key);
    }
}