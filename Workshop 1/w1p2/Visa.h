//Visa.h header file

#ifndef VISA_H
#define VISA_H

#include <cstddef> //for size_t

enum class VisaType{
    Employment,
    Buisness, //this is a typo
    Tourist,
    Immigrant
};

class Visa{
    char* id{nullptr};
    VisaType type{VisaType::Tourist};
    static size_t noOfVisas; //static variable for totalNoofVisas()
    public:
    //constructors
    Visa();
    Visa(const char* visaID, VisaType visatype = VisaType::Immigrant); //default to tourist if not provided

    double visaFee();

    static size_t totalNoOfVisas();

    //rule of 5
    //copy constructor
    Visa(const Visa& src);

    //copy assignemnt operator
    Visa& operator=(const Visa& src);

    //move constructor
    Visa(Visa&& src);

    //move assignment operator
    Visa& operator=(Visa&& src);

    //destructor
    ~Visa();
};

#endif

