#include "Visa.h"
#include <iostream>
#include <utility>

int main()
{
    std::cout << "\tNo of Visas: " << Visa::totalNoOfVisas() << std::endl;
    try
    {
        Visa a[2];
        std::cout << "\tNumber of of Visas: " << Visa::totalNoOfVisas() << std::endl;
        Visa p0("S5632D9YBA", VisaType::Employment);
        std::cout << "\tp0 Visa Fee: " << p0.visaFee() << std::endl;
        Visa p1("S345602YDC", VisaType::Buisness);
        std::cout << "\tp1 Visa Fee: " << p1.visaFee() << std::endl;
        Visa p2("S267570YOP", VisaType::Tourist);
        std::cout << "\tp2 Visa Fee: " << p2.visaFee() << std::endl;
        Visa p3("S336563YNL");
        std::cout << "\tp3 Visa Fee: " << p3.visaFee() << std::endl;
        Visa p4(p3);
        std::cout << "\tNumber of Visas: " << Visa::totalNoOfVisas() << std::endl;
        Visa p5 = std::move(p2);
        Visa p6 = p0;
        std::cout << "\tp5 Visa Fee: " << p5.visaFee() << std::endl;
        std::cout << "\tMoved p2 Visa Fee: " << p2.visaFee() << std::endl;
        std::cout << "\tp0 Visa Fee: " << p0.visaFee() << std::endl;
        std::cout << "\tp6 Visa Fee: " << p6.visaFee() << std::endl;
        std::cout << "\tNumber of Visas: " << Visa::totalNoOfVisas() << std::endl;
        Visa p7("S34CDE", VisaType::Tourist);
    }
    catch (const std::string& error)    {
        std::cerr <<"\t*************" << error << "\n";
    }
    std::cout << "\tNumber of Visas: " << Visa::totalNoOfVisas() << std::endl;
    return 0;
}


