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
//--------------------------------------------------------------------
// Application Includes                                               
//--------------------------------------------------------------------
#include "p01lex.h"
#include "p01tkn.h"
//--------------------------------------------------------------------
//Namespaces
//--------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------
//Global Variables                                                    
//--------------------------------------------------------------------
int TokenMgr(int t);                   //Token post processing
int lineCounter;
int columnCounter;
%}
%%
"and"					return TokenMgr(AND);
"array"					return TokenMgr(ARRAY);
"begin"					return TokenMgr(BEGAN);
"div"					return TokenMgr(DIV);
"do"					return TokenMgr(DO);
"else"					return TokenMgr(ELSE);
"end"					return TokenMgr(END);
"for"					return TokenMgr(FOR);
"function"				return TokenMgr(FUNCTION);
"if"					return TokenMgr(IF);
"integer"				return TokenMgr(INTEGER);
"mod"					return TokenMgr(MOD);
"not"					return TokenMgr(NOT);
"of"					return TokenMgr(OF);
"or"					return TokenMgr(OR);
"procedure"				return TokenMgr(PROCEDURE);
"program"				return TokenMgr(PROGRAM);
"real"					return TokenMgr(REAL);
"repeat"				return TokenMgr(REPEAT);
"then"					return TokenMgr(THEN);
"to"					return TokenMgr(TO);
"until"					return TokenMgr(UNTIL);
"var"					return TokenMgr(VAR);
"while"					return TokenMgr(WHILE);
[0-9]+                                  return TokenMgr(INTLIT);
","                                     return TokenMgr(COMMA);
";"                                     return TokenMgr(SEMICOLON);
":="                                    return TokenMgr(ASSIGN);
"+"                                     return TokenMgr(PLUS);
"-"                                     return TokenMgr(MINUS);
"/"                                     return TokenMgr(SLASH);
"*"                                     return TokenMgr(STAR);
"("                                     return TokenMgr(LPAREN);
")"                                     return TokenMgr(RPAREN);
[0-9]+\.[0-9]*([Ee][+-]?[0-9]+)?        return TokenMgr(REALIT);
[0-9]*\.[0-9]+([Ee][+-]?[0-9]+)?]       return TokenMgr(REALIT);
[0-9]+[Ee][+-]?[0-9]+                   return TokenMgr(REALIT);
\'.\'|''''                              return TokenMgr(CHRLIT);
"="                                     return TokenMgr(EQU);
"<>"                                    return TokenMgr(NEQ);
"<"                                     return TokenMgr(LES);
"<="                                    return TokenMgr(LEQ);
">"                                     return TokenMgr(GRT);
">="                                    return TokenMgr(GEQ);
"["                                     return TokenMgr(LBRACKET);
"]"                                     return TokenMgr(RBRACKET);
":"                                     return TokenMgr(COLON);
"."                                     return TokenMgr(PERIOD);
".."                                    return TokenMgr(RANGE);
\n { lineCounter++; columnCounter=1; }
[ \t]+ { columnCounter += strlen(yytext); }
[A-Za-z_]+[A-Za-z0-9_]*			return TokenMgr(ID);
.					return TokenMgr(ERROR);
%%
//--------------------------------------------------------------------
//Class Scanner implementation
//--------------------------------------------------------------------
//Function TokenMgr processes the token after it has been recognized
//--------------------------------------------------------------------
int TokenMgr(int t)
{
	columnCounter += strlen(yytext);   
	return t;
}
//--------------------------------------------------------------------
//Constructor Scanner is used to redirect the input file stream from the
//keyboard to input file stream i.
//--------------------------------------------------------------------
Scanner::Scanner(FILE* i) 
{   yyin=i; 
    lineCounter = 1;
    columnCounter = 1;
}
//--------------------------------------------------------------------
//Function Lex calls yylex
//--------------------------------------------------------------------
int Scanner::Lex(void)
{   tokencode=yylex();
    return tokencode;
}
//--------------------------------------------------------------------
//Function FetchSpelling returns a pointer to the spelling of the most
//recent token.
//--------------------------------------------------------------------
char* Scanner::FetchSpelling(void)
{
    return (char*)yytext;
} 
//--------------------------------------------------------------------
//Function FetchTokenCode returns the code of the most recent token 
//--------------------------------------------------------------------
int Scanner::FetchTokenCode(void)
{  return tokencode;
}
//--------------------------------------------------------------------
//Function StoreTokenCode records the most recent token code
//--------------------------------------------------------------------
void Scanner::StoreTokenCode(int T)
{  tokencode=T;
}
//--------------------------------------------------------------------
//Function GetLine returns the line number
//--------------------------------------------------------------------
int Scanner::GetLine(void)
{  return lineCounter;
}
//--------------------------------------------------------------------
//Function GetColumn returns the starting column number of the token
//--------------------------------------------------------------------
int Scanner::GetColumn(void)
{  return columnCounter - strlen(yytext);
}
//-----------------------End of Scanner Definition------------------------
     



