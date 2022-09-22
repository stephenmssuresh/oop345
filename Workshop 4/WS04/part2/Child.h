/*
File: Child.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 13/02/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/
#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H

#include "Toy.h"

namespace sdds{
    class Child{
        std::string Cname{""};
        unsigned int Cage{0};
        const sdds::Toy** toyArr{nullptr};
        size_t count{0u};

        public:
        Child() {};
        Child(std::string name, int age, const Toy* toys[], size_t count);

        //copy
        Child(const Child& src);
        Child& operator=(const Child& src);

        //destructor
        ~Child();

        //move
        Child(Child&& src) noexcept;
        Child& operator=(Child&& src) noexcept;


        size_t size() const;

        friend std::ostream& operator<<(std::ostream& os, const Child& child);
    };
}

#endif