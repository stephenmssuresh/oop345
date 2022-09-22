#ifndef SDDS_CENTRALUNIT_H
#define SDDS_CENTRALUNIT_H

#include <string>
#include <cstddef>
#include <fstream>

#include "Job.h"

namespace sdds{

    template<typename T>
    class CentralUnit{
        std::string m_type{""};
        T** m_items{nullptr}; //array of pointers
        Job* m_jobs[4]; //array of pointers
        size_t m_size{0};
        size_t m_count{0};


        //helper functions trim spaces from strings
        //3 trim functions below copied from : https://www.delftstack.com/howto/cpp/how-to-trim-a-string-cpp/
        std::string leftTrim(std::string str) {
            str.erase(0, str.find_first_not_of(' '));
            return str;
        }

        std::string rightTrim(std::string str){
            str.erase(str.find_last_not_of(' ') + 1);
            return str;
        }

        std::string trimString(std::string str) {
            return leftTrim(rightTrim(str));
        }




        public:
        //a class member function that receives a central unit (by reference) and the address of a type T unit as its arguments
        static void complete_job(CentralUnit<T>& cUnit, T* Taddress);

        //class data member
        static std::ostream& log;

        //functions
        ~CentralUnit(){
            for(size_t i = 0; i < m_size; i++){
                delete m_items[i];
            }
            for(size_t i = 0; i < m_count; i++){
                delete m_jobs[i];
            }
            delete[] m_items;
        }
        
        CentralUnit(){}

        CentralUnit(const CentralUnit& src){
            throw "Central Unit cannot be copy-assigned.";
        }

        CentralUnit& operator=(const CentralUnit& src) = delete;

        CentralUnit(std::string typeOfWork, const char* filename){
            m_type = typeOfWork;
            std::ifstream file(filename);
            if(!file){
                throw std::invalid_argument("File cannot be opened.");
            }

            std::string items;

            //count number of items (m_size)
            do{
                std::getline(file,items);
                if(file){
                    this->m_size++;
                }
            }while(file);

            m_items = new T*[m_size];

            //clear eof and fail flags
            file.clear();
            //set position of next character extracted to be the beginning
            file.seekg(std::ios::beg);

            for(size_t i = 0; i < m_size; i++){
                std::string unitType;
                std::string unitName;
                std::string capacityString;
                size_t capacity;

                std::getline(file, unitType, '|');
                std::getline(file, unitName, '|');
                std::getline(file, capacityString);


                unitType = trimString(unitType);
                unitName = trimString(unitName);
                capacityString = trimString(capacityString);

                try{
                    capacity = std::stoi(capacityString);
                }
                catch(...){
                    capacity = 1;
                }

                m_items[i] = new T(this, unitType, unitName, capacity);
            }
        }

        CentralUnit(CentralUnit&& src){
            *this = std::move(src);
        }

        CentralUnit& operator=(CentralUnit&& src){
            if(this!=&src){
                for(size_t i = 0; i < this->m_size; i++){
                    delete this->m_items[i];
                }
                for(size_t i = 0; i < this->m_count; i++){
                    delete this->m_jobs[i];
                }

                this->m_size = src.m_size;
                this->m_items = src.m_items;
                this->m_count = src.m_count;
                this->m_jobs = src.m_jobs;

                for(size_t i = 0; i < src.m_size; i++){
                    delete src.m_items[i];
                }
                src.m_size = 0u;

                for(size_t i = 0; i < src.m_count; i++){
                    delete src.m_jobs[i];
                }
                src.m_count = 0u;
            }
        }

        CentralUnit& operator+=(std::string jobName){
            if(m_count >= 4){
                throw std::string("Job queue is full.");
            }

            m_jobs[m_count] = new Job(jobName);
            m_count++;

            return *this;
        }

        void run(){
            for (size_t i = 0; i < m_size; i++){
                if(!(*m_items[i]) && m_count > 0){
                    *m_items[i] += m_jobs[m_count-1];
                    m_jobs[m_count-1] = nullptr;
                    m_count--;
                }
                m_items[i]->run();
            }
        }
        
        bool has_jobs(){
            bool retvalue = false;
            for(size_t i = 0; i < this->m_size; i++){
                if(*m_items[i]){
                    retvalue = true;
                }
            }
            if(m_count > 0) retvalue = true;
            return retvalue;
        }

        size_t get_available_units(){
            size_t availableCount = 0u;
            for(size_t i = 0; i < this->m_size; i++){
                if(!*m_items[i]){
                    availableCount++;
                }
            }
            return availableCount;
        }

    };

    template<typename T>
    std::ostream& CentralUnit<T>::log = std::cout;

    //This function frees the unit received and clears memory allocated for the job that was assigned to that unit
    template<typename T>
    static void complete_job(CentralUnit<T>& cUnit, T* unit){
        Job* job = unit->free();
    }

}



#endif