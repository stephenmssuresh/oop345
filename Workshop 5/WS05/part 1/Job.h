#ifndef SDDS_JOB_H
#define SDDS_JOB_H

#include <iostream>
#include <string>
#include <cstddef>

namespace sdds{
    class Job{
        std::string jobTitle{""};
        size_t workUnits{0u};
        size_t remainingWork{0u};
        bool active{false};

        public:
        Job();
        Job(std::string title);
        bool is_active();
        bool is_complete();
        std::string name();
        void display(std::ostream& os);

        //operator overload for function object
        void operator()(size_t work);        
    };

    std::ostream& operator<<(std::ostream& os, Job& job); //call display()
}

#endif