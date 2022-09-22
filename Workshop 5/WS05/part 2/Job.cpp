/*
File: Job.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 27/02/2022

trim functions in CentralUnit.h copied from: https://www.delftstack.com/howto/cpp/how-to-trim-a-string-cpp/

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/


#include <stdexcept>
#include <iomanip>

#include "Job.h"

namespace sdds{
    Job::Job(){};

    Job::Job(std::string title){
        jobTitle = title;
        workUnits = ( ((title.length()) % 10) + 1);
        remainingWork = workUnits;
    }

    bool Job::is_active(){
        return active;
    }
    
    bool Job::is_complete(){
        return (remainingWork == 0) ? true : false;
    }

    std::string Job::name(){
        return jobTitle;
    }

    void Job::display(std::ostream& os){
        os << "`" << jobTitle << "` [" << std::setw(2) << std::setfill('0') << remainingWork << "/" << std::setw(2) << std::setfill('0') << workUnits << " remaining]";
    }
    
    void Job::operator()(size_t work){
        if(work > remainingWork){
            remainingWork = 0;
            active = false;
            throw std::underflow_error("Performed less than passed work");
        }

        remainingWork -= work;
        if(remainingWork == 0){
            active = false;
        }
    }

    std::ostream& operator<<(std::ostream& os, Job& job){
        job.display(os);
        return os;
    }
}