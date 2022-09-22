/*
File: Pair.h
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 05/02/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#ifndef SDDS_PAIR_H
#define SDDS_PAIR_H

namespace sdds{
    class Pair
{
	std::string m_key{};
	std::string m_value{};
public:
	const std::string& getKey() { return m_key; }
	const std::string& getValue() { return m_value; }
	Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};

	// TODO: Add here the missing the prototypes for the members
	//           that are necessary if this class is to be used
	//           with the template classes described below.
	//       Implement them in the Pair.cpp file.
     
    // void setEmpty();
    Pair();
    friend std::ostream& operator<<(std::ostream& os, const Pair& pairs);
    Pair& operator=(const int source);
	friend bool operator==(const Pair& pair1, const Pair& pair2);
};
}

#endif