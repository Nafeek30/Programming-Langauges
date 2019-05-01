%{
//--------------------------------------------------------------------
// File p01lex.l defines a scanner for Pascal.
// The scanner definition is a lex specification.                        
//-------------------------------------------------------------------
//--------------------------------------------------------------------
// Standard C and C++ Library Include Files                                     
//--------------------------------------------------------------------
#include <string>                          
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
//--------------------------------------------------------------------
// Application Includes                                               
//--------------------------------------------------------------------
#include "p02lex.h"
#include "p02tkn.h"
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------
//Global Variables                                                    
//--------------------------------------------------------------------
int lineCounter = 1;
int columnCounter = 1;
string names[] =
{
    "ID", "BEGIN", "END", "AND", "ARRAY", "INTLIT", "COMMA", "SEMICOLON", "ASSIGN", 
    "PLUS", "MINUS", "SLASH", "STAR", "LPAREN", "RPAREN", "DIV", "DO", 
    "ELSE", "FOR", "FUNCTION", "IF", "INTEGER", "MOD", "NOT", "OF", "OR", "PROCEDURE", 
    "REAL", "REPEAT", "THEN", "TO", "UNTIL", "VAR", "WHILE", "REALIT", "CHRLIT", "EQU", 
    "NEQ", "LES", "LEQ", "GRT", "GEQ", "LBRACKET", "RBRACKET", "COLON", "PERIOD", "RANGE", 
    "PROGRAM"
};
map<int, string> tokenNames;
//--------------------------------------------------------------------
//Externals
//--------------------------------------------------------------------
extern ofstream tfs;
//--------------------------------------------------------------------
//Functions                                                  
//--------------------------------------------------------------------
int tokenMgr(int t);                   //Token post processing
void printToken(ostream& o, int tokenCode, int line, int column);
//--------------------------------------------------------------------
//Exceptions                                                  
//--------------------------------------------------------------------
struct BadCharacterException
{
    BadCharacterException(char p, int line, int column)
    {
        cout << endl;
        cout << "line(" << line << ") column (" << column << ")";
        cout << "Lexical error: ";
        cout << "Illegal character |" << p << "| ASCII code=" << (int)p;
        cout << endl;
    }
};

%}
%%
"and"					                return tokenMgr(AND);
"array"					                return tokenMgr(ARRAY);
"begin"					                return tokenMgr(BEGAN);
"div"					                return tokenMgr(DIV);
"do"					                return tokenMgr(DO);
"else"					                return tokenMgr(ELSE);
"end"					                return tokenMgr(END);
"for"					                return tokenMgr(FOR);
"function"				                return tokenMgr(FUNCTION);
"if"					                return tokenMgr(IF);
"integer"				                return tokenMgr(INTEGER);
"mod"					                return tokenMgr(MOD);
"not"					                return tokenMgr(NOT);
"of"					                return tokenMgr(OF);
"or"					                return tokenMgr(OR);
"procedure"				                return tokenMgr(PROCEDURE);
"program"				                return tokenMgr(PROGRAM);
"real"					                return tokenMgr(REAL);
"repeat"				                return tokenMgr(REPEAT);
"then"					                return tokenMgr(THEN);
"to"					                return tokenMgr(TO);
"until"					                return tokenMgr(UNTIL);
"var"					                return tokenMgr(VAR);
"while"					                return tokenMgr(WHILE);
[0-9]+                                  return tokenMgr(INTLIT);
","                                     return tokenMgr(COMMA);
";"                                     return tokenMgr(SEMICOLON);
":="                                    return tokenMgr(ASSIGN);
"+"                                     return tokenMgr(PLUS);
"-"                                     return tokenMgr(MINUS);
"/"                                     return tokenMgr(SLASH);
"*"                                     return tokenMgr(STAR);
"("                                     return tokenMgr(LPAREN);
")"                                     return tokenMgr(RPAREN);
[0-9]+\.[0-9]*([Ee][+-]?[0-9]+)?        return tokenMgr(REALIT);
[0-9]*\.[0-9]+([Ee][+-]?[0-9]+)?]       return tokenMgr(REALIT);
[0-9]+[Ee][+-]?[0-9]+                   return tokenMgr(REALIT);
\'.\'|''''                              return tokenMgr(CHRLIT);
"="                                     return tokenMgr(EQU);
"<>"                                    return tokenMgr(NEQ);
"<"                                     return tokenMgr(LES);
"<="                                    return tokenMgr(LEQ);
">"                                     return tokenMgr(GRT);
">="                                    return tokenMgr(GEQ);
"["                                     return tokenMgr(LBRACKET);
"]"                                     return tokenMgr(RBRACKET);
":"                                     return tokenMgr(COLON);
"."                                     return tokenMgr(PERIOD);
".."                                    return tokenMgr(RANGE);
\n                                      { lineCounter++; columnCounter=1; }
[ \t]+                                  { columnCounter += strlen(yytext); }
[A-Za-z_]+[A-Za-z0-9_]*			return tokenMgr(ID);
.					{ throw BadCharacterException(*yytext, lineCounter, columnCounter); }
%%
//--------------------------------------------------------------------
//Function tokenMgr processes the token after it has been recognized
//--------------------------------------------------------------------
int tokenMgr(int t)
{
	columnCounter += strlen(yytext);   
    printToken(tfs, t, lineCounter, columnCounter);
	return t;
}
//--------------------------------------------------------------------
//Function printToken prints the token code, name, and spelling of the
//token
//--------------------------------------------------------------------
void printToken(ostream& o, int tokenCode, int line, int column)
{
    o << endl;
    o << "Token";
    o << ": Code=" << setw(3) << tokenCode;
    o << " Name=" << setw(10) << tokenNames[tokenCode];
    o << " line=" << setw(3) << line;
    o << " column=" << setw(3) << column;
    o << " Spelling=\"" << (char*)yytext << "\"";
}
//--------------------------------------------------------------------
//Class Scanner implementation
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Constructor Scanner is used to redirect the input file stream from the
//keyboard to input file stream i.
//--------------------------------------------------------------------
Scanner::Scanner(FILE* i) 
{   
    yyin = i;
    //associate token codes with token names in a map
    for(int code = ID, name = 0; name < sizeof(names)/sizeof(*names); code++, name++)
    {
        tokenNames[code] = names[name];
	//cout << tokenNames[code] << endl;
    } 
}
//--------------------------------------------------------------------
//Function Lex calls yylex
//--------------------------------------------------------------------
int Scanner::lex()
{   
    tokenCode=yylex();
    return tokenCode;
}
//--------------------------------------------------------------------
//Function fetchSpelling returns a pointer to the spelling of the most
//recent token.
//--------------------------------------------------------------------
char* Scanner::fetchSpelling()
{
    return (char*)yytext;
} 
//--------------------------------------------------------------------
//Function fetchTokenCode returns the code of the most recent token 
//--------------------------------------------------------------------
int Scanner::fetchTokenCode()
{  
    return tokenCode;
}
//--------------------------------------------------------------------
//Function storeTokenCode records the most recent token code
//--------------------------------------------------------------------
void Scanner::storeTokenCode(int tokenCode)
{  
    this->tokenCode = tokenCode;
}
//-----------------------End of Scanner Definition------------------------
     



