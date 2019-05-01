//----------------------------------------------------------------------
//File p01.cpp processes command line arguments and invokes lex 
//to find tokens in the input file.
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//C++ include files
//----------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;
//----------------------------------------------------------------------
//Application include files
//-----------------------------------------------------------------------
#include "p01tkn.h"
#include "p01lex.h"
//-----------------------------------------------------------------------
//FileException is thrown when a file whose name is given on the command line
//cannot be opened.
//-----------------------------------------------------------------------
struct FileException {
  FileException(const char* fn)
  {  cout << endl;
     cout << "File " << fn << " cannot be opened.";
  }
};
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//Commandlineerror is thrown when too many arguments are put on the 
//command line
//-----------------------------------------------------------------------
struct CommandLineException {
  CommandLineException(int m,int a)
  {  cout << endl; 
     cout << "Too many command line arguments";
     cout << endl;
     cout << "A maximum of " << m << " command line arguments can"
	  << " appear on the command line.";
     cout << endl;
     cout << a << " arguments were entered.";
     cout << endl;
     cout << "p01 (<input file name>)";
  }
};
//-----------------------------------------------------------------------
//Function Title prints a title
//-----------------------------------------------------------------------
void Title(ostream& o)
{   o << endl;
    o << setw(15) << "Token Code";
    o << " ";
    o << setw(15) << "Token Name";
    o << " ";
    o << setw(15) << "Line";
    o << " ";
    o << setw(15) << "Column";
    o << " ";
    o << setw(15) << "Token Spelling";
}
//-----------------------------------------------------------------------
//Function LexMgr processes the input file, calls the scanner, and
//produces the output file.
//-----------------------------------------------------------------------
void LexMgr(FILE* i, ostream& o)
{   static const char* TokenName[]=
    {
		"EOF"      ,"ID"      ,"BEGIN"   ,"END"    ,"AND"
        ,"ARRAY"    ,"INTLIT"  ,"COMMA"  ,"SEMICOLON"
        ,"ASSIGN"   ,"PLUS"    ,"MINUS"  ,"SLASH"	,"STAR"
	,"LPAREN"  ,"RPAREN" ,"ERROR"  ,"DIV"	,"DO"   ,"ELSE"
	,"FOR"      ,"FUNCTION" ,"IF"       ,"INTEGER"	,"MOD"
	,"NOT"      ,"OF"       ,"OR"	,"PROCEDURE"	,"REAL"
	,"REPEAT"	,"THEN"     ,"TO"   ,"UNTIL"    ,"VAR" 
	,"WHILE"	,"REALIT"	,"CHRLIT"	,"EQU"	,"NEQ"
	,"LES"	,"LEQ"	,"GRT" 	,"GEQ"		,"LBRACKET"
	,"RBRACKET"	,"COLON"	,"PERIOD"	,"RANGE"	,"PROGRAM"
    };

    Scanner S(i);
    Title(o);
    int t=S.Lex();
    while (t > 0) {
		o << endl;
		o << setw(15) << t;
		o << " ";
		o << setw(15) << TokenName[t];
		o << " ";
		o << setw(15) << S.GetLine();
		o << " ";
		o << setw(15) << S.GetColumn();
		o << " ";
		o << setw(15) << S.FetchSpelling();
		t=S.Lex();
    }
    o << endl;
}
//-----------------------------------------------------------------------
//Function main processes command line arguments
//-----------------------------------------------------------------------
int main(int argc, char* argv[])
{  
	try 
	{
     char ifn[255], ofn[255];
     switch (argc) {
       case 1://no files on the command line
         cout << "Enter the input file name. ";
         cin >> ifn;
         strcpy(ofn, ((string)ifn).replace(((string)ifn).size() -4, 4, ".trc").c_str());
         break;
       case 2://input file on the command line/prompt for output file
         strcpy(ifn,argv[1]);
         strcpy(ofn, ((string)ifn).replace(((string)ifn).size() -4, 4, ".trc").c_str());
		break;
       default:
         throw CommandLineException(2,argc-1); 
         break;
     }
     
     FILE* i=fopen(ifn, "r"); if (!i) throw FileException(ifn);
     ofstream o(ofn); if (!o) throw FileException(ofn);

     LexMgr(i, o);
     
     fclose(i);
     o.close();
   	} catch (...) {
     cout << endl;
     cout << "Program Terminated";
     cout << endl;
     exit(EXIT_FAILURE);
   }
   return 0;
}
