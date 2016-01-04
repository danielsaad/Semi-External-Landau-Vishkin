
/*
 * LandauVishkinMain.cpp
 *
 *  Created on: Dec 12, 2013
 *      Author: Daniel Saad Nogueira Nunes
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <lvlib/LandauVishkin.hpp>
#include <lvlib/text.hpp>
#include <lvlib/RMQ.hpp>
#include <lvlib/Index.hpp>


/**
 * argv[1] = text
 * argv[2] = pattern
 * argv[3] = errors
 * argv[4] = output
 * argv[5] = variation -- DC/DC-NAV/DC-SE/DC-PAR/DC-RMQ/DC-RMQ-BYTE/DMIN/DMIN-BYTE
 */
int main(int argc, char** argv){
    word errors;
    Text* t;
    Text* p;
    Text* out;

    if(argc!=6){
        std::cerr << "Error " << "\n" << "Usage: ./example <text-file> <pattern-file> <number of errors> <output-file> <variation>\n";
        exit(EXIT_FAILURE);
    }

    t =  new Text(argv[1],std::ios::in | std::ios::binary);
    p = new Text(argv[2],std::ios::in | std::ios::binary);
    errors = atoi(argv[3]);
    out = new Text(argv[4],std::ios::out);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    if(strcmp(argv[5],"DC")==0){
    	landauVishkin_DC(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DC-NAV")==0){
    	landauVishkin_DC_Navarro(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DC-SE")==0){
    	landauVishkin_DC_Semi_External(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DC-PAR")==0){
    	landauVishkin_DC_Parallel(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DC-RMQ")==0){
    	landauVishkin_RMQ<IndexRMQ<RegularLCP,RMQ_succinct<RegularLCP>>>(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DC-RMQ-BYTE")==0){
    	landauVishkin_RMQ<IndexRMQ<ByteLCP,RMQ_succinct<ByteLCP>>>(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DMIN")==0){
    	landauVishkin_DMin<Index<RegularLCP>>(t,p,errors,out);
    }
    else if(strcmp(argv[5],"DMIN-BYTE")==0){
    	landauVishkin_DMin<Index<ByteLCP>>(t,p,errors,out);
    }
    else{
    	std::cerr <<"Error: Unknow variation.\n";
    	exit(EXIT_FAILURE);
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << duration << endl;
    delete t;
    delete p;
    delete out;
    return(0);
}
