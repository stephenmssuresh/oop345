/*
File: TimedTask.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 29/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_TIMEDTASK_H
#define SDDS_TIMEDTASK_H

#include <string>
#include <cstring>
#include <chrono>

namespace sdds{
    struct Task{
        std::string taskName;
        std::string timeUnit;
        std::chrono::steady_clock::duration taskDuration;
    };

    class TimedTask{
        int noOfRecords;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point endTime;
        Task taskList[10];

        public:
        TimedTask();
        void startClock();
        void stopClock();
        void addTask(const char* name);

        friend std::ostream& operator<<(std::ostream& os, const TimedTask& tasks);
    };
}
#endif