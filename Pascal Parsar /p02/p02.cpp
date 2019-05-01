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
#include "p02par.h"
#include "p02lex.h"
//-----------------------------------------------------------------------
//Exceptions
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//FileException is thrown when a file whose name is given on the command line
//cannot be opened.
//-----------------------------------------------------------------------
struct FileException
{
  FileException(const char *fn)
  {
    cout << endl;
    cout << "File " << fn << " cannot be opened.";
  }
};
//-----------------------------------------------------------------------
//BadSuffixException is thrown when a non-pascal file is entered into the
//command line
//-----------------------------------------------------------------------
struct BadSuffixException
{
  BadSuffixException(const string suffix)
  {
    cout << endl;
    cout << "Invalid file type: " << suffix << endl;
    cout << "Only files of type '.pas' are accepted.";
    cout << endl;
  }
};
//-----------------------------------------------------------------------
//Commandlineerror is thrown when too many arguments are put on the
//command line
//-----------------------------------------------------------------------
struct CommandLineException
{
  CommandLineException(int m, int a)
  {
    cout << endl;
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
//Externals
//-----------------------------------------------------------------------
ofstream tfs;
//-----------------------------------------------------------------------
//Functions
//-----------------------------------------------------------------------
void compilerMgr(FILE *i)
{
  Parser P(i);
  P.parse();
}
//-----------------------------------------------------------------------
//Function main processes command line arguments
//-----------------------------------------------------------------------
int main(int argc, char *argv[])
{
  try
  {
    char ifn[255], ofn[255];
    switch (argc)
    {
    case 1: //no files on the command line
      cout << "Enter the input file name. ";
      cin >> ifn;
      strcpy(ofn, ((string)ifn).replace(((string)ifn).size() - 4, 4, ".trc").c_str());
      break;
    case 2: //input file on the command line/prompt for output file
      strcpy(ifn, argv[1]);
      strcpy(ofn, ((string)ifn).replace(((string)ifn).size() - 4, 4, ".trc").c_str());
      break;
    default:
      throw CommandLineException(2, argc - 1);
      break;
    }

    string suffix = ((string)ifn).substr(((string)ifn).length() - 4, 4);
    if (suffix != ".pas")
      throw BadSuffixException(suffix);
    FILE *i = fopen(ifn, "r");
    if (!i)
      throw FileException(ifn);
    tfs.open(ofn);
    if (!tfs)
      throw FileException(ofn);

    //lexMgr(i, tfs);
    compilerMgr(i);

    fclose(i);
    tfs.close();
  }
  catch (...)
  {
    cout << endl;
    cout << "Program Terminated";
    cout << endl;
    exit(EXIT_FAILURE);
  }
  return 0;
}
