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
#include <utility>

#include "ProteinDatabase.h"

using namespace std;

namespace sdds{
    ProteinDatabase::ProteinDatabase(){
        noOfProteins = 0;
    }

    ProteinDatabase::ProteinDatabase(const string filename){
        noOfProteins = 0;


        char character;
        string tempstring;
        ifstream fin;
        fin.open(filename);

        if(fin.is_open()){
            while(fin){
                fin.ignore(200, '\n');
                fin.ignore(20000, '>');
                noOfProteins++;
            }
            //cout << endl << "noOfProteins before decrementing: " << noOfProteins << endl << "'''''''''''''''''''''" << endl;
            //but why
            noOfProteins--;

            //cout << endl << "noOfProteins after decrementing: " << noOfProteins << endl << "'''''''''''''''''''''" << endl;
            fin.close();
            fin.clear();
            fin.open(filename);

            proteins = new string[noOfProteins];
            int counter = -1;
            while(fin && counter < noOfProteins){
                //fin.get(character);
                if(!fin.get(character).eof()){
                    if (character != '>'){
                    //https://www.codeproject.com/Questions/865342/Displaying-an-extra-character-problem-while-readin
                    proteins[counter].push_back(character);
                    getline(fin, tempstring, '\n');
                    proteins[counter].append(tempstring);
                    }
                    else{
                    fin.ignore(300,'\n');
                    counter++;
                    }
                }
                
            }
            //cout << endl<< proteins[counter] << endl;
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

    //copy
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

    //destructor
    ProteinDatabase::~ProteinDatabase(){
        delete[] proteins;
    }

    //move
    ProteinDatabase::ProteinDatabase(ProteinDatabase&& source) noexcept{
        noOfProteins = 0;
        *this = std::move(source);
    }

    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& source) noexcept{
        if(this != &source){
            delete[] proteins;
            proteins = source.proteins;
            source.proteins = nullptr;
            noOfProteins = source.noOfProteins;
            source.noOfProteins = 0;
        }
        return *this;
    }
}