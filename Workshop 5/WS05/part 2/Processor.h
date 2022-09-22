/*
File: Processor.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 27/02/2022

trim functions in CentralUnit.h copied from: https://www.delftstack.com/howto/cpp/how-to-trim-a-string-cpp/

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/


#ifndef SDDS_PROCESSOR_H
#define SDDS_PROCESSOR_H

#include <string>
#include <functional>

#include "CentralUnit.h"
#include "Job.h"

namespace sdds{
    class Processor{
       CentralUnit<Processor>* m_host{nullptr};
       std::string m_brand{""};
       std::string m_code{""};
       size_t m_power{0};
       Job* m_current{nullptr};

       //data member that stores the address of a function
       //function pointer: returns nothing, takes hosting central unit by reference and address of a processor
        void (*complete_callback)(CentralUnit<Processor>& hosting, Processor* pAddress);
        
        //std::function object that targets a function to be run when an error occurs. targetted function returns nothing and takes address of processor
        std::function<void(Processor*)> errorFunction;


        public:
        //recieves a function pointer for a callback and assigns it to the processor
        void on_complete(void (*callback)(CentralUnit<Processor>& hosting, Processor* pAddress));
        void on_error(std::function<void(Processor*)> errorF);
        Processor();
        Processor(CentralUnit<Processor>* host, const std::string brand, const std::string code, const size_t power);
        void run();
        explicit operator bool() const;
        Processor& operator+=(Job*& assigned);
        Job* get_current_job() const;

        //an operator overload to make a Processor a functor
        void operator()();

        Job* free();

        friend std::ostream& operator<<(std::ostream& os, const Processor& proc);

    };
}
#endif