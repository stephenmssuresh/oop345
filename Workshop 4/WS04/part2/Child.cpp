/*
File: Child.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 13/02/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include "Child.h"
#include "Toy.h"

using namespace std;

namespace sdds{

     Child::Child(std::string name, int age, const Toy* toys[], size_t count) {
        this->Cname = name;
        this->Cage = age;
        this->count = count;
        toyArr = new const Toy*[count];
        for(auto i = 0u; i < count; i++){
            if(toys[i] != nullptr){
                toyArr[i] = new Toy(*toys[i]);
            }
        }
     }

    std::ostream& operator<<(std::ostream& os, const Child& child){
        static unsigned int CALL_CNT = 0;
        CALL_CNT++;
        os << "--------------------------" << endl;
        os << "Child " << CALL_CNT << ": " << child.Cname <<" " << child.Cage << " years old:" << endl;
        os << "--------------------------" << endl;
        if(child.count == 0){
            os << "This child has no toys!" << endl;
        }
        else{
            for(auto i = 0u; i < child.count; i++){
                os << *(child.toyArr[i]);
            }
        }
        os << "--------------------------" << endl;
        return os;
    }

     size_t Child::size() const{
        return count;
     }

    Child::Child(const Child& src){
        if(this!=&src){
            *this = src;
        }
    }

    Child& Child::operator=(const Child& src){
        if(this!=&src){
            Cname = src.Cname;
            Cage = src.Cage;
            //count = src.count;
            for (auto i = 0u; i < count; i++){
            delete toyArr[i];
            toyArr[i] = nullptr;
            }
            delete[] toyArr;

            count = src.count;

            toyArr = new const Toy*[count];
            for(auto i = 0u; i < count; i++){
                if(src.toyArr[i] != nullptr){
                    toyArr[i] = new Toy(*src.toyArr[i]);
                }
            }
        }
        return *this;
    }

    Child::Child(Child&& src) noexcept{
        if(this != &src){
            *this = std::move(src);
        }
    };

    Child& Child::operator=(Child&& src) noexcept{
        if(this != &src){
            Cname = src.Cname;
            Cage = src.Cage;

            for (auto i = 0u; i < count; i++){
            delete toyArr[i];
            toyArr[i] = nullptr;
            }
            
            count = src.count;
            src.Cage = 0;
            src.Cname = "";
            src.count = 0;

            delete[] toyArr;
            //dont need for loop
            toyArr = src.toyArr;
            src.toyArr = nullptr;
        }
        return *this;
    }

    Child::~Child(){
        for (auto i = 0u; i < count; i++){
            delete toyArr[i];
            toyArr[i] = nullptr;
        }
        delete[] toyArr;
        toyArr = nullptr;
    }

}