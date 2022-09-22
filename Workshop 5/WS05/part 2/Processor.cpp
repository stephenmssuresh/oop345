/*
File: Processor.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 27/02/2022

trim functions in CentralUnit.h copied from: https://www.delftstack.com/howto/cpp/how-to-trim-a-string-cpp/

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/


#include <stdexcept>
#include <string>
#include <functional>

#include "CentralUnit.h"
#include "Processor.h"

//processor 
namespace sdds{
    Processor::Processor(){}
    
    Processor::Processor(CentralUnit<Processor>* host, const std::string brand, const std::string code, const size_t power){
        if(host){
            m_host = host;
            m_brand = brand;
            m_code = code;
            m_power = power;
            m_current = nullptr;
        }
    }

    void Processor::run(){
        if(m_current != nullptr && m_host){
            if(m_current->is_complete()){
                delete m_current;
                m_current = nullptr;
            }
            else{
                try{
                //calling overloaded () operator
                (*m_current)(m_power);
                }
                catch(std::underflow_error& err){
                CentralUnit<Processor>::log << "Processed over quota for " << (*m_current) <<std::endl;
                delete m_current;
                m_current = nullptr;
                }
            }
        }
    }

    Processor::operator bool() const{
        return (m_current == nullptr) ? false : true;
    }

    Processor& Processor::operator+=(Job*& assigned){
        if(m_current){
            throw "ERROR IN OPERATOR += in PROCESSOR";
        }
        m_current = assigned;
        return *this;
    }

    Job* Processor::get_current_job() const{
        return m_current;
    }

    //recieves a function pointer for a callback and assigns it to the processor
    void Processor::on_complete(void (*callback)(CentralUnit<Processor>& hosting, Processor* pAddress)){
        complete_callback = callback;
    }

    //receives std::function callback to register and run when a job encounters an error during processing and sets the respective instance member
    void Processor::on_error(std::function<void(Processor*)> errorF){
        errorFunction = errorF;
    }

    void Processor::operator()(){
        if(m_current != nullptr && m_host){
            if(m_current->is_complete()){
                //do nothing if already completed
            }
            else{
                try{
                //calling overloaded () operator
                (*m_current)(m_power);
                
                //calling the function set (given the address to a member function pointer) by on_complete() when completed after running when incomplete
                if(m_current->is_complete() && complete_callback != nullptr){
                    complete_callback(*m_host, this);
                }
                }
                catch(std::underflow_error& err){
                    //calling the std::function object that was set by the on_error() function
                    if(errorFunction){
                        errorFunction(this);
                    }
                }
            }
        }
    }

    //called in the CentralUnit template
    Job* Processor::free(){
        //Job* m_current{nullptr};
        Job* returnJob = m_current;
        m_current = nullptr;
        return returnJob;
    }


    //friend helper operator overload
    std::ostream& operator<<(std::ostream& os, const Processor& proc){
        os << "(" << proc.m_power << ") " << proc.m_brand << " " << proc.m_code;
        if(proc) {
            os << " processing " << *(proc.m_current);
        }
        return os;
    }
}