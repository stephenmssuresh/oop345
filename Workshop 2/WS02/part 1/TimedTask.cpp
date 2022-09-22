/*
File: TimedTask.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 29/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#include <iostream>
#include <iomanip>

#include "TimedTask.h"

using namespace std;

namespace sdds{
    TimedTask::TimedTask(){
        noOfRecords = 0;

        //safe empty?
        startTime = std::chrono::steady_clock::now();
        endTime = std::chrono::steady_clock::now();
    }

    void TimedTask::startClock(){ 
        //records start time
        startTime = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock(){ 
        //records end time
        endTime = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* name){ 
        //add new task to the taskList array
        taskList[noOfRecords].taskName = name;
        taskList[noOfRecords].timeUnit = "nanoseconds";
        taskList[noOfRecords].taskDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(abs(startTime - endTime));
        noOfRecords++;
    }

    std::ostream& operator<<(std::ostream& os, const TimedTask& tasks){ 
        //overloaded friend operator to print out the taskList array
        os << "--------------------------" <<endl;
        os << "Execution Times:" << endl;
        os << "--------------------------" <<endl;
        for(int i = 0; i < tasks.noOfRecords; i++){
            os.width(21);
            os.setf(ios::left);
            os << tasks.taskList[i].taskName << " ";
            os.unsetf(ios::left);

            os.setf(ios::right);
            os.width(13);
            os << tasks.taskList[i].taskDuration.count(); //https://www.geeksforgeeks.org/chrono-in-c/
            os << " " << tasks.taskList[i].timeUnit << endl;
            os.unsetf(ios::right);
        }
        os << "--------------------------" <<endl;
        return os;
    }
}