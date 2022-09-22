#ifndef SDDS_TOY_H
#define SDDS_TOY_H

namespace sdds{
    class Toy{
        unsigned int orderID;
        std::string toyName;
        unsigned int noOfItems;
        double price;
        static double salesTax;

        //private member to remove spaces from a string, called in 1-arg constructor
        //std::string removeSpaces(const std::string& spaceString);

        //3 trim functions below copied from : https://www.delftstack.com/howto/cpp/how-to-trim-a-string-cpp/
        std::string leftTrim(std::string str);
        std::string rightTrim(std::string str);
        std::string trimString(std::string str);

        public:
        Toy() : orderID{0},toyName {""},noOfItems{0}, price{0.0}{};
        Toy(const std::string& toy);
        void update(int numItems);
        
        friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
    };
}

#endif