
/*
 * LandauVishkinMain.cpp
 *
 *  Created on: Dec 12, 2013
 *      Author: Daniel Saad Nogueira Nunes
 */

#include <iostream>
#include <cstdlib>
#include <lvlib/LandauVishkin.hpp>
#include <lvlib/text.hpp>
#include <lvlib/RMQ.hpp>
#include <lvlib/Index.hpp>


/**
 * argv[1] = text
 * argv[2] = pattern
 * argv[3] = errors
 * argv[4] = output
 */
int main(int argc, char** argv){
    word errors;
    Text* t;
    Text* p;
    Text* out;

    if(argc!=5){
        std::cerr << "Error " << "\n" << "Usage: ./LandauVishkin <text> <pattern> <number of errors> <output>\n";
        exit(EXIT_FAILURE);
    }

    if(argc==5){
        t =  new Text(argv[1],std::ios::in | std::ios::binary);
        p = new Text(argv[2],std::ios::in | std::ios::binary);
        errors = atoi(argv[3]);
        out = new Text(argv[4],std::ios::out);
        landauVishkin_DC_Semi_External(t,p,errors,out);
        landauVishkin_DC(t,p,errors,out);
        landauVishkin_DC_Navarro(t,p,errors,out);
        landauVishkin_DC_Parallel(t,p,errors,out);
        landauVishkin_RMQ<IndexRMQ<RegularLCP,RMQ_succinct<RegularLCP>>>(t,p,errors,out);
        landauVishkin_RMQ<IndexRMQ<ByteLCP,RMQ_succinct<ByteLCP>>>(t,p,errors,out);
        landauVishkin_DMin<Index<RegularLCP>>(t,p,errors,out);
        landauVishkin_DMin<Index<ByteLCP>>(t,p,errors,out);
        delete t;
        delete p;
        delete out;
    }
    return(0);
}
