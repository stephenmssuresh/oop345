/*
File: Directory.cpp
Name: Stephen Suresh
Student ID: 117916213
Email: ssuresh15@myseneca.ca
Date completed : 12/03/2022

I have done all the coding by myself and only copied the code that my professor provided to complete my workshopsand assignments
*/

#include "Directory.h"

namespace sdds{
    Directory::Directory(){
    }

    Directory::Directory(std::string name){
        m_name = name;
    }

   void  Directory::update_parent_path(const std::string& path){
       m_parent_path = path;

       
        //for(Resource* resource : m_contents){ resource->update_parent_path(m_parent_path)}
        //or use std::vector<Resource*>::iterator
        for(auto it = m_contents.begin(); it != m_contents.end(); it++){
           //(*it)->update_parent_path(m_parent_path);
           (*it)->update_parent_path(this->path());
       }    
    }

    std::string Directory::name() const{
        return m_name;
    }

    int Directory::count() const{
    //a query that returns the number of resources that this directory holds.
        return m_contents.size();
    }

    std::string Directory::path() const{
        return (m_parent_path + m_name);
    }

    size_t Directory::size() const{ //recursive function
    // a query that returns the size of the directory in bytes. The size of the directory is the sum of the individual sizes of each resource that this directory holds. This member returns 0u if the directory is empty.
        size_t contentsSize = 0u;
        // if(!m_contents.empty()){
        //
            for(Resource* resource : m_contents){
                contentsSize += resource->size();
            }
        // }
        return contentsSize;
    }

    NodeType Directory::type() const{
        return NodeType::DIR;
    }

    Directory& Directory::operator+=(Resource* resource){
        for(Resource* res : m_contents){
            if(res->name() == resource->name()){throw "already exists in the root";}
        }
        m_contents.push_back(resource);
        resource->update_parent_path(this->path());
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags){
        bool recursiveFind = false;
        for (auto i : flags){
            if(i == OpFlags::RECURSIVE){
                recursiveFind = true;
            }
        }

        for(Resource* resource : m_contents){
            if(resource->name() == name){
                return resource;
            }
            if(recursiveFind && resource->type() == NodeType::DIR){
                Resource* r = dynamic_cast<Directory*>(resource)->find(name, flags);
                if(r != nullptr) return r;
            }
        }
        return nullptr;
    }

    Directory::~Directory(){
        while(!m_contents.empty()){
            delete m_contents.back();
            m_contents.pop_back();
        }
    }
}