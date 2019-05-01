//--------------------------------------------------------------------
// File mcrlex.cpp defines a prototype scanner for the micro language.
//-------------------------------------------------------------------
// Author: Thomas R. Turner                                           
// E-Mail: trturner@uco.edu                                          
// Date:   September, 2018
//--------------------------------------------------------------------
//Copyright September, 2018 by Thomas R. Turner.
//Do not reproduce without permission from Thomas R. Turner
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ Library Include Files                                     
//--------------------------------------------------------------------
#include <string>                          
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std;
//--------------------------------------------------------------------
// Application Includes                                               
//--------------------------------------------------------------------
#include "mcrlex.h"
//--------------------------------------------------------------------
//Class Lexer implementation
//--------------------------------------------------------------------
//Constructor Lexer is used to redirect the input file stream from the
//keyboard to input file stream i.
//--------------------------------------------------------------------
Lexer::Lexer(istream* ifp) 
{   i=ifp;   
    ch=' ';
    tokencode=0;
    tokenspelling="";
}
//--------------------------------------------------------------------
//Function Lex calls yylex
//--------------------------------------------------------------------
int Lexer::Lex(void)
{   tokenspelling="";
    i->get(ch);
    for (;;) {
        cout << endl << "ch='" << ch << "'";
        if (i->eof()) return 0;
        if (!isspace(ch)) break;
        i->get(ch);
    }
    cout << endl << "ch='" << ch << "'";
    if (isalpha(ch)) {
        for(;;) {
            if (i->eof()) return ID;
            if (!isalpha(ch)) {
                i->putback(ch);
                return ID;
            }
            tokenspelling+=ch;
            i->get(ch);
            cout << endl << "ch='" << ch << "'";
        }
    }
    tokenspelling=ch;
    switch (ch) {
        case ',': return COMMA;
        case ';': return SEMICOLON;
        case ':': 
            i->get(ch); 
            if (ch=='=') {
                tokenspelling+=ch;
                return ASSIGN;
            }
            i->putback(ch); 
            return ERROR;
        break;
        case '+': return PLUS;
        case '-': return MINUS;
        case '/': return SLASH;
        case '*': return STAR;
        case '(': return LPAREN;
        case ')': return RPAREN;
        default : return ERROR;
    }
    return 0;
}
//--------------------------------------------------------------------
//Function FetchSpelling returns a pointer to the spelling of the most
//recent token.
//--------------------------------------------------------------------
string Lexer::FetchSpelling(void)
{   return tokenspelling;
} 
//--------------------------------------------------------------------
//Function FetchTokenCode returns the code of the most recent token 
//--------------------------------------------------------------------
int Lexer::FetchTokenCode(void)
{  return tokencode;
}
//--------------------------------------------------------------------
//Function StoreTokenCode records the most recent token code
//--------------------------------------------------------------------
void Lexer::StoreTokenCode(int T)
{  tokencode=T;
}
//-----------------------End of Lex Definition------------------------
     



