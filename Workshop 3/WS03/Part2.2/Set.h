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
#include <cmath>

namespace sdds{
    template<class T>
    class Set : public Collection<T,100>{
        const size_t CAPACITY = 100;
        public:
        Set() {};


        bool add(const T& item){
            bool ret = false;
            bool isthere = false;
            size_t i;
            if (this->count < CAPACITY){
                for(i = 0u; i < this->count && !isthere; i++){
                    if(this->typeCol[i] == item){
                        ret = false;
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

    template<>
	bool Set<double>::add(const double& item)
	{
		for (size_t i = 0; i < this->count; i++)
		{
			if (std::fabs(item - this->typeCol[i]) <= 0.01)
			{
				return false;
			}
		}
		return Collection<double, 100>::add(item);
	};

}

#endif