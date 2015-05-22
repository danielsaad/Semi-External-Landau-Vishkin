#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <lvlib/text.hpp>


/**
    @file Provides text manipulation functions
**/


/**
    Extract a substring from the text.
    @param start the start position of the substring in the text
    @param end the end position of the substring in the text
    @return substring
**/
byte* Text::extractSubstring(word start, word end){
    byte* str = new byte[end-start+1];
    file.seekg(start,std::ios_base::beg);
    file.read(reinterpret_cast<char*>(str),sizeof(byte)*(end-start+1));
    return(str);
}

/**
    Read from the text and place the information on a already allocated buffer.
    @param buffer the buffer
    @param start start position in the text where the data will be read.
    @param size the size in bytes of the data to be read.
    @return return the number of bytes read.
**/
word Text::readBuffer(byte* buffer,word start,word size){
    file.seekg(start,std::ios_base::beg);
    file.read(reinterpret_cast<char*> (buffer),sizeof(byte)*size);
    return(file.gcount());
}


word Text::readBuffer(byte* buffer,word size){
	file.read(reinterpret_cast<char*> (buffer),sizeof(byte)*size);
    return(file.gcount());
}


byte Text::readSymbol(word start){
	byte b;
	if(file.good()){
		file.seekg(start,std::ios_base::beg);
		file.read(reinterpret_cast<char*> (&b),sizeof(byte));
	}
	else{
		std::cout << "File not good\n";
	}
	return(b);
}


byte Text::readSymbol(){
	byte b;
	file.read(reinterpret_cast<char*> (&b),sizeof(byte));
	return(b);
}

word Text::getLength(){
    return(length);
}

Text::Text(const char* filename,std::ios_base::openmode mode){
	strcpy(this->filename,filename);
	if(mode & std::ios_base::binary) binaryFlag=1;
	else binaryFlag=0;
    try{
        file.open(filename,mode);
    }
    catch(std::fstream::failure e){
        std::cout << e.what();
    }
    file.seekg(0,std::ios::end);
    length = file.tellg();
    reset();
    textStart = 0;
    textEnd = length-1;
}

Text::~Text(){
    file.close();
}

std::fstream& Text::getFile(){
	std::fstream& ref = file;
	return(ref);
}

void Text::serialize(std::ostream& output){
	output.write(reinterpret_cast<const char*> (filename),sizeof(char)* maxPathnameLength);
	output.write(reinterpret_cast<const char*> (&binaryFlag),sizeof(binaryFlag));
}

Text::Text(std::istream& input){
	input.read(reinterpret_cast<char*> (filename),sizeof(char)* maxPathnameLength);
	input.read(reinterpret_cast<char*> (&binaryFlag),sizeof(binaryFlag));
    try{
        if(binaryFlag) file.open(filename,std::ios::binary|std::ios::in|std::ios::out);
        else file.open(filename,std::ios::in|std::ios::out);
    }
    catch(std::fstream::failure e){
        std::cout << e.what();
	}
	file.seekg(0,std::ios::end);
	length = file.tellg();
	reset();
	textStart = 0;
	textEnd = length-1;
}

void Text::reset(){
    file.seekg(0,std::ios::end);
    length = file.tellg();
	file.clear();
    file.seekg(0,std::ios_base::beg);
    file.seekp(0,std::ios_base::beg);
}
