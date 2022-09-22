/*
File: Set.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 05/02/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_SET_H
#define SDDS_SET_H

#include "Collection.h"

namespace sdds{
    template<typename T>
    class Set : public Collection<T,100u>{

        public:

        virtual bool add(const T& item){
            bool ret = false;
            bool isthere = false;

            if (this->count < 100){
                for(size_t i = 0u; i < this->count && !isthere; i++){
                    if(this->typeCol[i] == item){
                        std::cout << this->typeCol[i] << std::endl;
                        isthere = true;
                    }
                }
                if(!isthere){
                    this->typeCol[this->count] = item;
                    this->count++;
                    ret = true;
                }
            }
            return ret;
        }

        ~Set(){};

    };

    // template<>
    // sdds::Pair Collection<sdds::Pair, 100u>::dummy = Pair noKey("No key", "No value");

    
    
}

#endif