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
class Scanner 
{
  int tokenCode;                 //Code for the most recent token found
public:
  Scanner(FILE* i);           //Constructor establish the input file 
  int lex();                 //Call the scanner and return the code
  int fetchTokenCode();      //Return the code of the most recent token
  void storeTokenCode(int tokenCode);    //Store the token code.
  char* fetchSpelling();    //Return the spelling of the most recent token
};
#endif
