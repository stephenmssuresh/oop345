/*
File: Collection.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 05/02/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include "Pair.h"
#include <string>
#include <iostream>

namespace sdds{
    //template <typename T, unsigned int CAPACITY>
    template <typename T, unsigned int CAPACITY>
    class Collection{
        protected:
        T typeCol[CAPACITY] {};
        size_t count{0};
        //static T dummy;
        T dummy;

        public:
        Collection() {
        }; 

        size_t size(){
            return count;
        }
        
        virtual void display(std::ostream& os = std::cout){
            os << "----------------------" << std::endl;
            os << "| Collection Content |" << std::endl;
            os << "----------------------" << std::endl;
            for(size_t i = 0u; i < count; i++){
                os << typeCol[i] << std::endl;
            }
            os << "----------------------" << std::endl;
        }

        virtual bool add(const T& item){
            bool ret = false;
            if (count < CAPACITY){
                typeCol[count] = item;
                count++;
                ret = true;
            }
            return ret;
        }

        T operator[](size_t index){
            return index < count ? typeCol[index] : dummy;
        }

        virtual ~Collection() {};

    };


   
    // template<typename T, unsigned int CAPACITY>
    // T Collection<T, CAPACITY>::dummy = 0;

    // template<>
    // sdds::Pair Collection<Pair, CAPACITY>::dummy = Pair empty("","");

    // template<>
    // bool Collection<float, CAPACITY>::add(){

    // }

    // template<typename Pair, unsigned int CAPACITY>
    // Pair Collection<Pair,CAPACITY>::dummy = empty("", "");

    // template<>
    // Pair Collection<Pair,100u>::dummy = Pair empty("No Key", "No Value");

}

#endif