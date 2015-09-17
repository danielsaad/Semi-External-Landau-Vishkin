#ifndef LANDAUVISHKIN_HPP
#define LANDAUVISHKIN_HPP

/*
 * LandauVishkin.hpp
 *
 *  Created on: Dec 9, 2013
 *      Author: daniel
 */

#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "text.hpp"
#include "types.hpp"

//#define SHOW


static const integer LV_DIRECT_MIN_BLOCK = 8;
static const integer LV_STRING_SIZE = 5;
static const integer LV_BLOCK_SIZE = 1024*1024;
static const integer LV_NUMBER_OF_THREADS =4;

typedef struct LV_DC_parallel_struct_t{
    integer* l_array;
    integer base;
    integer prev;
    integer cur;
    integer next;
    integer begin;
    integer last;
    integer end;
    byte* pattern;
    byte* text;
    integer text_length;
    integer pattern_length;
}LV_DC_parallel_struct_t;


// Landau-Vishkin with direct comparisons only
void landauVishkin_DC(Text* text_text,Text* pattern_text,integer errors, Text* output);

void landauVishkin_DC_Navarro(Text* text_text,Text* pattern_text,integer errors, Text* output);

//Landau-Vishkin with direct comparisons only (text based). Semi-external approach.
void landauVishkin_DC_Semi_External(Text* text_text,Text* pattern_text,integer errors, Text* output);


integer match(const byte* str1,const byte* str2);

//Parallel processing of Landau-Vishkin Algorithm using Threads
void landauVishkin_DC_Parallel(Text* text_text,Text* pattern_text,integer errors, Text* output);
void landauVishkin_DC_Parallel_ProcessDiagonals(const LV_DC_parallel_struct_t& LV_struct);

//Requires a SA with support to LCP and Inverse Suffix Array
template<class TSA> void landauVishkin_DMin(Text* text_text,Text* pattern_text,integer errors, Text* output);


//Landau-Vishkin using suffix arrays and direct comparisons
template<class TSA> void landauVishkin_DMin(Text* text_text,Text* pattern_text,integer errors, Text* output);
template<class TSA> integer directComparisons(TSA* sa,word i,word j);
template<class TSA> integer directMin(TSA* sa,word i,word j);

//Classical LV-solution with suffix arrays and RMQ
template<class TSA> void landauVishkin_RMQ(Text* text_text,Text* pattern_text,integer errors, Text* output);



//Landau-Vishkin using suffix arrays and direct comparisons only
template<class TSA>
void landauVishkin_DMin(Text* text_text,Text* pattern_text,integer errors, Text* output){
    integer text_length;
    integer pattern_length;
    integer* l_array;
    Text* text_and_pattern_text;
    TSA* index;
    integer base;
    integer s1,s2;
    integer prev,cur,next;
    std::fstream file;
    int fd;


    char tmp_name[] = "/tmp/fileXXXXXX";

    //generate filename
    fd = mkstemp(tmp_name);
    if(fd==-1){
        std::cout << "mkstemp error\n";
        std::exit(EXIT_FAILURE);
    }
    close(fd);
    try{
        file.open(tmp_name,std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
    }
    catch (std::fstream::failure e){
        std::cout << e.what();
    }

    text_text->reset();
    pattern_text->reset();

    //Append text and pattern into the temporary file
    file << text_text->file.rdbuf() << "$" << pattern_text->file.rdbuf() << '#';
    file.close();

    text_and_pattern_text = new Text(tmp_name, std::ios::in | std::ios::binary);

    //initialization
    text_length = text_text->getLength();
    pattern_length = pattern_text->getLength();
    l_array =  new integer[errors+text_length+1];
    index = new TSA(text_and_pattern_text);

    //LV algorithm
    for(integer i =0; i<errors+text_length+1;i++){
        l_array[i] = -2;
    }
    base = errors;
    for(integer i=0;i<=errors;i++){
        prev = -2;
        cur = i-2;
        next = l_array[base-i+1];
        for(integer j=base-i;j<i+text_length;j++){
            if(cur+j-base >= text_length-1){
                l_array[j] = std::max(next+1,prev);
                l_array[j] = std::max(cur,l_array[j]);
            }
            else{
                l_array[j] = std::max(cur+1,prev);
                l_array[j] = std::max(l_array[j],next+1);
            }
            l_array[j] = std::min(l_array[j],pattern_length-1);
            //Extend diagonal
            s1 = index->_isa[j-(base-i)+l_array[j]+1];
            s2 = index->_isa[text_length+l_array[j]+2];
            if(s1>s2) std::swap(s1,s2);
            if(s2-s1<=LV_DIRECT_MIN_BLOCK){
                l_array[j]+=directMin(index,s1,s2);
            }
            else{
                l_array[j]+=directComparisons(index,index->_sa[s1],index->_sa[s2]);
            }
            prev = cur;
            cur = next;
            next = l_array[j+2];
        }
    }

#ifdef SHOW
    std::cout << "The pattern ends in text with at most " << errors << " errors " << "at positions:" << "\n";
    for(integer j=0;j<errors+text_length;j++){
        if(l_array[j]==pattern_length-1){
            std::cout << j-errors+l_array[j]  << "\n";
        }
    }
#endif

    //clean up

    delete text_and_pattern_text;
    if(remove(tmp_name)!=0)
        std::cerr << "Error deleting file " << tmp_name << "\n";
    delete index;
    delete[] l_array;
}


//Classical LV-solution with suffix arrays and RMQ
template<class TSA>
void landauVishkin_RMQ(Text* text_text,Text* pattern_text,integer errors, Text* output){
    integer text_length;
    integer pattern_length;
    integer* l_array;
    Text* text_and_pattern_text;
    TSA* index;
    integer base;
    int fd;
    integer s1,s2;
    integer next,prev,cur;
    std::fstream file;

    text_text->reset();
    pattern_text->reset();
    char tmp_name[]= "/tmp/fileXXXXXX";

    //generate filename
    fd = mkstemp(tmp_name);
    if(fd==-1){
        std::cout << "mkstemp error" <<"\n";
        std::exit(EXIT_FAILURE);
    }
    close(fd);
    try{
        file.open(tmp_name,std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
    }
    catch (std::fstream::failure e){
        std::cout << e.what();
    }

    //Append text and pattern into the temporary file
    file << text_text->file.rdbuf() << "$" << pattern_text->file.rdbuf() << '#';
    file.close();

    text_and_pattern_text = new Text(tmp_name, std::ios::in | std::ios::binary);

    //initialization
    text_length = text_text->getLength();
    pattern_length = pattern_text->getLength();
    l_array =  new integer[errors+text_length+1];
    index = new TSA(text_and_pattern_text);

    //LV algorithm
    for(integer i =0; i<errors+text_length+1;i++){
        l_array[i] = -2;
    }
    base = errors;
    for(integer i=0;i<=errors;i++){
        prev = -2;
        cur = i-2;
        next = l_array[base-i+1];
        for(integer j=base-i;j<base+text_length;j++){
            if(cur+j-base >= text_length-1){
                l_array[j] = std::max(next+1,prev);
                l_array[j] = std::max(cur,l_array[j]);
            }
            else{
                l_array[j] = std::max(cur+1,prev);
                l_array[j] = std::max(l_array[j],next+1);
            }
            l_array[j] = std::min(l_array[j],pattern_length-1);
            //Extend diagonal
            s1 = index->_isa[j-(base-i)+l_array[j]+1];
            s2 = index->_isa[text_length+l_array[j]+2];
            if(s1>s2){
                std::swap(s1,s2);
            }
            l_array[j]+= ((*index->_lcp)[index->_rmq->query(s1,s2-1)]);
            prev = cur;
            cur = next;
            next = l_array[j+2];
        }
    }

#ifdef SHOW
    std::cout << "The pattern ends in text with at most " << errors << " errors " << "at positions:" << "\n";
    for(integer j=0;j<errors+text_length;j++){
        if(l_array[j]==pattern_length-1){
            std::cout << j-errors+l_array[j]  << "\n";
        }
    }
#endif

    //clean up
    delete[] l_array;
    delete text_and_pattern_text;
    if(remove(tmp_name)!=0)
        std::cerr << "Error deleting file " << tmp_name << "\n";
    delete index;
}



template<class TSA>
integer directComparisons(TSA* sa,word i,word j){
    word c=0;
    while(sa->_textStr[i+c] == sa->_textStr[j+c]){
        c++;
    }
    return(c);
}

template<class TSA>
integer directMin(TSA* sa,word i,word j){
    integer minLCP = (*(sa->_lcp))[i];
    for(word k=i+1;k<j;k++){
        minLCP = std::min((*(sa->_lcp))[k],minLCP);
    }
    return(minLCP);
}

#endif // LANDAUVISHKIN_HPP
