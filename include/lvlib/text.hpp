#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <fstream>
#include <iostream>
#include <lvlib/types.hpp>

#define ALPHABET_SIZE 256

class Text{
public:
	Text(std::istream& input);
    Text(const char* filename,std::ios_base::openmode mode);
    ~Text();

    byte* extractSubstring(word start, word end);
    word readBuffer(byte* buffer,word start,word size);
    word readBuffer(byte* buffer,word size);
    byte readSymbol();
    byte readSymbol(word start);
    word getLength();
    std::fstream file; /**File where the text is stored**/
    void reset();
    std::fstream& getFile();
    void serialize(std::ostream& output);
    static const int maxPathnameLength = 200;
private:
    std::ios_base::openmode mode;
    char filename[maxPathnameLength];
    int binaryFlag;
    word length; /**number of symbols in text**/
    word textStart; /**position of the file where the text starts**/
    word textEnd; /**position of the file where the text ends**/
};


#endif // TEXT_H_INCLUDED
