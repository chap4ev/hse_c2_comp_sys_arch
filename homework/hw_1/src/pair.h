#ifndef __pairh__
#define __pairh__

//------------------------------------------------------------------------------
// pair.h - содержит 
// структуру ccPair пару <char, char> 
// структуру csPair пару <char, short int> 
//------------------------------------------------------------------------------

struct ccPair {
    char first;
    char second;
};

struct csPair {
    char first;
    short int second;
};

#endif  // __pairh__
