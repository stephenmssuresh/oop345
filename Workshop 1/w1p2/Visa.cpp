// Visa.cpp implementation file
#include <cstring>
#include <utility>
#include <string>
#include "Visa.h"

size_t Visa::noOfVisas{0};

Visa::Visa(){
    noOfVisas++;
};

Visa::Visa(const char* visaID, VisaType visatype){
    if(!visaID || strlen(visaID) < 10){
        std::string vid(visaID);
        throw (std::string("Exception: Visa ID (" + vid + ") is not valid, it must be a string of 10 characters"));
    }
    this->type = visatype;
    size_t length = strlen(visaID);
    this->id = new char[length + 1];
    strcpy(this->id, visaID);
    noOfVisas++;
}

double Visa::visaFee(){
    double fee = 0.0;
    if(id){
        switch(this->type){
        case VisaType::Employment:
        fee = 250.00;
        break;
        case VisaType::Buisness: //typo
        fee = 780.00;
        break;
        case VisaType::Tourist :
        fee = 890.00;
        break;
        case VisaType::Immigrant :
        fee = 540.00;
        break;
        default:
        fee = 0.0;
        }
    }
    else{
        fee = 0.0;
    }
    return fee;
}


size_t Visa::totalNoOfVisas(){
    return noOfVisas;
}


    //copy constructor
Visa::Visa(const Visa& src){
    *this = src;
    noOfVisas++;
}

    //copy assignemnt operator
Visa& Visa::operator=(const Visa& src){
    if(this != &src){
        //shallow copy
        this->type = src.type;

        //dynamically allocate memory for id before deep copy
        delete[] this->id;
        size_t length = strlen(src.id);
        this->id = new char[length + 1];
        strcpy(this->id, src.id);
    }
    return *this;
}

    //move constructor
Visa::Visa(Visa&& src){
    *this = std::move(src);
    noOfVisas++;
}

    //move assignment operator
Visa& Visa::operator=(Visa&& src){
    if(this != &src){
        //shallow copy
        this->type = src.type;

        //delete contents pointed to by this->id before assigning it the address
        delete[] this->id;
        this->id = src.id;

        //remove address from the source object and set to empty state
        src.id = nullptr;
        src.type = VisaType::Tourist; //for consistency?
    }
    return *this;
}

    //destructor
Visa::~Visa(){
    delete[] id;
    noOfVisas--;
}