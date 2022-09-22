/*
File: ProteinDatabase.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 29/01/2022

I have done all the coding by myselfand only copied the code that my professor provided to complete my workshopsand assignments
*/

#include <iostream>
#include <iomanip>
#include <fstream>

#include "ProteinDatabase.h"

using namespace std;

namespace sdds{
    ProteinDatabase::ProteinDatabase(){
        noOfProteins = 0;
        proteins = nullptr;
    }

    ProteinDatabase::ProteinDatabase(const string filename){
        noOfProteins = 0;
        proteins = nullptr;

        int counter = 0;
        ifstream fin;
        fin.open(filename);

        if(fin.is_open()){
            while(fin){
                fin.ignore(200, '\n');
                fin.ignore(20000, '>');
                noOfProteins++;
            }
            //cout << endl << "noOfProteins before decrementing: " << noOfProteins << endl << "'''''''''''''''''''''" << endl;
            noOfProteins--;
            //cout << endl << "noOfProteins after decrementing: " << noOfProteins << endl << "'''''''''''''''''''''" << endl;
            fin.close();
            fin.clear();
            fin.open(filename);
            proteins = new string[noOfProteins];
            while(fin && counter < noOfProteins){
                fin.ignore(200, '\n');
                getline(fin, proteins[counter], '>');
                counter++;
            }
        }
        else{
            cout << "Cannot Open the File" << endl;
        }
        //cout << counter;
    }

    int ProteinDatabase::size(){
        return noOfProteins;
    }

    std::string ProteinDatabase::operator[](int index){
        // a query that returns a copy of the protein sequence at the index received as the function parameter. If the index is invalid, this function should return an empty string.
        if(index >= noOfProteins || index < 0){
            return "";
        }
        else{
            return proteins[index];
        }
    }

    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& source){
        if(this != &source){
            noOfProteins = source.noOfProteins;
            delete[] proteins;
            proteins = new string[noOfProteins];
            for (auto i = 0; i < noOfProteins; i++){
                proteins[i] = source.proteins[i];
            }
        }
        return *this;
    }

    ProteinDatabase::ProteinDatabase(const ProteinDatabase& source){
        noOfProteins = 0;
        proteins = nullptr;
        *this = source;
    }

    ProteinDatabase::~ProteinDatabase(){
        delete[] proteins;
    }
}