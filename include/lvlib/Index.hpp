#ifndef INDEX_HPP
#define INDEX_HPP
#include <unordered_map>
#include <divsufsort.h>
#include "RMQ.hpp"
#include "types.hpp"
#include "text.hpp"


template<class CLCP>
class Index{
public:
    Index(Text* T);
    integer* _sa;
    integer* _isa;
    CLCP* _lcp;
    byte* _textStr;
    integer _size;
    ~Index();
};

template<class CLCP>
class SemiExternalIndex{
public:
    SemiExternalIndex(Text* T);
    integer* _sa;
    integer* _isa;
    CLCP* _lcp;
    byte* _textStr;

    integer size;
    ~SemiExternalIndex();
};

template<class CLCP, class CRMQ>
class IndexRMQ{
public:
    IndexRMQ(Text* T);
    integer* _sa;
    integer* _isa;
    CLCP* _lcp;
    byte* _textStr;
    CRMQ* _rmq;

    integer _size;

    ~IndexRMQ();
};

template<class CLCP, class CRMQ>
class SemiExternalIndexRMQ{
public:
    SemiExternalIndexRMQ(Text* T);
    integer* _sa;
    integer* _isa;
    CLCP* _lcp;
    CRMQ* _rmq;

    integer size;
    ~SemiExternalIndexRMQ();
};


class RegularLCP{
public:
    RegularLCP(integer size){_lcp = new integer[size];}

    integer operator[](const integer i);
    void set(const integer i, const integer l){ _lcp[i]  = l; }
    integer* _lcp;

    ~RegularLCP(){ delete[] _lcp; }
};


class ByteLCP{
 public:
    ByteLCP(integer size){_lcp = new byte[size];}
    integer operator[](const integer i);
    void set(const integer i, const integer l){
        if(l<255){
            _lcp[i] = l;
        }
        else{
            _lcp[i] = 255;
           _hash[i] = l;
        }
    }
    byte* _lcp;
    std::unordered_map<integer,integer> _hash;

    ~ByteLCP(){ delete[] _lcp; }
};



template<class CLCP,class CRMQ>
IndexRMQ<CLCP,CRMQ>::IndexRMQ(Text *T){
    integer h = 0;
    integer k;
    _size = T->getLength();
    _textStr = new byte[_size];
    T->reset();
    T->readBuffer(_textStr,0,T->getLength());

    //Computes SA
    _sa = new integer[_size];
    if(divsufsort(_textStr,_sa,_size)){
       std::cerr<<("suffix sort error");
       exit(EXIT_FAILURE);
    }

    //Computes SAI
    _isa = new integer[_size];
    for(integer i=0;i<_size;i++)
        _isa[_sa[i]]=i;

    //Computes LCP via Kasai et.al
    _lcp = new CLCP(_size);
    for(integer i=0;i<_size;i++){
        if(_isa[i] !=  _size-1){
            k = _sa[_isa[i]+1];
            while(_textStr[i+h]==_textStr[k+h]){
                h++;
            }
            _lcp->set(_isa[i], h);
            if(h>0) h--;
        }
        else{
            _lcp->set(_isa[i], 0);
        }
    }
    //Computes RMQ
    _rmq = new CRMQ(_lcp,_size);

}

template<class CLCP,class CRMQ> IndexRMQ<CLCP,CRMQ>::~IndexRMQ(){
    delete[] _sa;
    delete[] _isa;
    delete[] _textStr;
    delete _lcp;
    delete _rmq;
}

template<class CLCP>
Index<CLCP>::Index(Text *T){
    integer h = 0;
    integer k;
    _size = T->getLength();
    _textStr = new byte[_size];
    T->reset();
    T->readBuffer(_textStr,0,T->getLength());

    //Computes SA
    _sa = new integer[_size];
    if(divsufsort(_textStr,_sa,_size)){
       std::cerr<<("suffix sort error");
       exit(EXIT_FAILURE);
    }

    //Computes SAI
    _isa = new integer[_size];
    for(integer i=0;i<_size;i++)
        _isa[_sa[i]]=i;

    //Computes LCP via Kasai et.al
    _lcp = new CLCP(_size);
    for(integer i=0;i<_size;i++){
        if(_isa[i] !=  _size-1){
            k = _sa[_isa[i]+1];
            while(_textStr[i+h]==_textStr[k+h]){
                h++;
            }
            _lcp->set(_isa[i], h);
            if(h>0) h--;
        }
        else{
            _lcp->set(_isa[i], 0);
        }
    }
}

template<class CLCP> Index<CLCP>::~Index(){
    delete[] _sa;
    delete[] _isa;
    delete _lcp;
    delete[] _textStr;
}

inline integer ByteLCP::operator[](const integer i){
    if(_lcp[i]<255)
        return(_lcp[i]);
    else
        return(_hash[i]);
}


inline integer RegularLCP::operator [](const integer i){
    return(_lcp[i]);
}



#endif // INDEX_HPP
