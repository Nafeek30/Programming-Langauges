#ifndef P02PAR_h
#define P02PAR_h 1
//--------------------------------------------------------------------
// File p02par.h defines class Parser.
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ include files
//--------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include "p02lex.h"
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------
//Class Parser defines the attributes of a Pascal Parser
//--------------------------------------------------------------------
//Parser inherits from Scanner
class Parser : public Scanner
{
public:
    Parser(FILE*);
    ~Parser();
    int parse();
};
#endif
