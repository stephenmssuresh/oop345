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
        T typeCol[CAPACITY] {};
        size_t count{0};
        static T dummy;

        public:
        Collection() {
            //dummy = 0;
        }; 

        size_t size(){
            return count;
        }
        
        void display(std::ostream& os = std::cout){
            os << "----------------------" << std::endl;
            os << "| Collection Content |" << std::endl;
            os << "----------------------" << std::endl;
            for(size_t i = 0u; i < count; i++){
                os << typeCol[i] << std::endl;
            }
            os << "----------------------" << std::endl;
        }

        bool add(const T& item){
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

    };

    // template<typename T, unsigned int CAPACITY>
    // T Collection<T, CAPACITY>::dummy=0;

    // template<>
    // Pair Collection<Pair,100u>::dummy = Pair emptyP("No Key", "No Value");

    // template<unsigned int CAPACITY>
    // class Collection<Pair, CAPACITY>{
    //     Pair typeCol[CAPACITY] {};
    //     size_t count{0};
    //     static Pair dummy;
    //     public:
    //     Collection() {
    //         std::string emptystring = "";
    //         dummy.getValue() = emptystring;
    //         dummy.getKey() = emptystring;
    //     }; 

    //     size_t size(){
    //         return count;
    //     }
        
    //     void display(std::ostream& os = std::cout){
    //         os << "----------------------" << std::endl;
    //         os << "| Collection Content |" << std::endl;
    //         os << "----------------------" << std::endl;
    //         for(size_t i = 0u; i < count; i++){
    //             os << typeCol[i] << std::endl;
    //         }
    //         os << "----------------------" << std::endl;
    //     }

    //     bool add(const Pair& item){
    //         bool ret = false;
    //         if (count < CAPACITY){
    //             typeCol[count] = item;
    //             count++;
    //             ret = true;
    //         }
    //         return ret;
    //     }

    //     Pair operator[](size_t index){
    //         return index < count ? typeCol[index] : dummy;
    //     }

    // };

    // template<class Pair, unsigned int CAPACITY>
    // Pair Collection<Pair, CAPACITY>::dummy = pair emptyP("","");
    // template<class Pair, unsigned int CAPACITY>
    // Pair Collection<Pair, CAPACITY>::dummy("","");

    // template<typename int T, unsigned int CAPACITY>
    // int Collection<int, CAPACITY>::dummy=0;
}

#endif