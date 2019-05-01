#ifndef mcrlex_h
#define mcrlex_h 1
//--------------------------------------------------------------------
// File mcrlex.h defines class Lexer.  
//--------------------------------------------------------------------
// Author: Thomas R. Turner                                           
// E-Mail: trturner.uco.edu                                          
// Date:   September, 2018                                              
//--------------------------------------------------------------------
// Copyright September, 2018 by Thomas R. Turner
// Do not reproduce without permission from Thomas R. Turner.
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ include files                                        
//--------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <iomanip>
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------
//Token definitions
//--------------------------------------------------------------------
#define ID          1
#define BEGAN       2
#define END         3
#define READ        4
#define WRITE       5
#define INTLIT      6
#define COMMA       7
#define SEMICOLON   8
#define ASSIGN      9
#define PLUS        10
#define MINUS       11
#define SLASH       12
#define STAR        13
#define LPAREN      14
#define RPAREN      15
#define ERROR       16
//--------------------------------------------------------------------
//Class Lexer defines the attributes of a Scanner
//--------------------------------------------------------------------
class Lexer {
  int tokencode;                 //Code for the most recent token found
  string tokenspelling;          //Current token recognized by the scanner
  istream* i;                    //Input file stream
  char ch;                       //Current character
public:
  Lexer(istream* ifp);           //Constructor establish the input file 
  int Lex(void);                 //Call the scanner and return the code
  int FetchTokenCode(void);      //Return the code of the most recent token
  void StoreTokenCode(int T);    //Store the token code.
  string FetchSpelling(void);    //Return the spelling of the most recent
                                 //token
};
#endif
