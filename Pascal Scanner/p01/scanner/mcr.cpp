//----------------------------------------------------------------------
//File mcr.cpp processes command line arguments and invokes lex 
//to find tokens in the input file.
//----------------------------------------------------------------------
//Author: Thomas R. Turner
//E-Mail: trturner@uco.edu
//Date:   September, 2018
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
#include "mcrlex.h"
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
     cout << "p01 (<input file name> (<output file name>))";
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
    o << "Token Spelling";
}
//-----------------------------------------------------------------------
//Function LexMgr processes the input file, calls the scanner, and
//produces the output file.
//-----------------------------------------------------------------------
void LexMgr(istream* i,ostream& o)
{   static const char* TokenName[]=
        {"EOF"      ,"ID"      ,"BEGIN"   ,"END"    ,"READ"
        ,"WRITE"    ,"INTLIT"  ,"COMMA"  ,"SEMICOLON"
        ,"ASSIGN"   ,"PLUS"    ,"MINUS"  ,"SLASH"
        ,"STAR"     ,"LPAREN"  ,"RPAREN" ,"ERROR"
        };
    Lexer L(i);                 
    Title(o);
    int t=L.Lex();
    while (t > 0) {
        o << endl;
	o << setw(15) << t;
	o << " ";
	o << setw(15) ;
        o << TokenName[t];
	o << " ";
	o << L.FetchSpelling();
        t=L.Lex();
    }
    o << endl;
}
//-----------------------------------------------------------------------
//Function main processes command line arguments
//-----------------------------------------------------------------------
int main(int argc, char* argv[])
{  try {
     char ifn[255],ofn[255];
     switch (argc) {
       case 1://no files on the command line
         cout << "Enter the input file name. ";
         cin >> ifn;
         cout << "Enter the output file name. ";
         cin >> ofn;
         break;
       case 2://input file on the command line/prompt for output file
         strcpy(ifn,argv[1]);
         cout << "Enter the output file name. ";
         cin >> ofn;
         break;
       case 3://Both files on the input line
         strcpy(ifn,argv[1]);
         strcpy(ofn,argv[2]);
         break;
       default:
         throw CommandLineException(2,argc-1); 
         break;
     }
     ifstream i(ifn); if (!i) throw FileException(ifn);
     ofstream o(ofn); if (!o) throw FileException(ofn);

     LexMgr(&i,o);
     
     i.close();
     o.close();
   } catch ( ... ) {
     cout << endl;
     cout << "Program Terminated";
     cout << endl;
     exit(EXIT_FAILURE);
   }
   return 0;
}
