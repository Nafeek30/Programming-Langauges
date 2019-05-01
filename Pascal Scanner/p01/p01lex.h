#ifndef P01LEX_h
#define P01LEX_h 1
//--------------------------------------------------------------------
// File p01lex.h defines class Scanner.
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ include files
//--------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <cstdio>
#include <iomanip>
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;

#ifdef __cpluscplus
extern "C"
#endif

int yylex(void);
//--------------------------------------------------------------------
//Class Scanner defines the attributes of a Scanner
//--------------------------------------------------------------------
class Scanner {
  int tokencode;                 //Code for the most recent token found

public:
  Scanner(FILE* i);           //Constructor establish the input file 
  int Lex(void);                 //Call the scanner and return the code
  int FetchTokenCode(void);      //Return the code of the most recent token
  void StoreTokenCode(int T);    //Store the token code.
  char* FetchSpelling(void);    //Return the spelling of the most recent
                                 //token
  int GetLine(void);
  int GetColumn(void);
};
#endif
