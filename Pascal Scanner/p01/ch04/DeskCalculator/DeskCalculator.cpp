//-----------------------------------------------------------------
//Author:      Bjarne Stroustrup
//Implementor: Thomas R Turner
//E-Mail:      trturner@uco.edu
//Date:        September, 2018
//----------------------------------------------------------------
//C and C++ Include Files
//----------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <map>
using namespace std;
//----------------------------------------------------------------
//Define token codes
//----------------------------------------------------------------
enum Token_value {
    NAME,        NUMBER,      END,
    PLUS='+',    MINUS='-',   MUL='*',     DIV='/',
    PRINT=';',   ASSIGN='=',  LP='(',      RP=')'
};
Token_value curr_tok=PRINT;
//----------------------------------------------------------------
//Function error prints an error message and increments the number
//of error encountered.
//----------------------------------------------------------------
int no_of_errors=0;
double error(const string& s)
{   no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}
//----------------------------------------------------------------
//Function headers for recursive parser
//----------------------------------------------------------------
double expression(bool get);
double term(bool get);
double primary(bool get);
Token_value get_token();
//----------------------------------------------------------------
//Function expression parses and evaluates expression
//----------------------------------------------------------------
double expression(bool get)
{   double left=term(get);
    for(;;) 
        switch (curr_tok) {
            case PLUS:
                left+=term(true);
            break;
            case MINUS:
                left-=term(true);
            break;
            default:
                return left;
                 
        }//end switch
}//end expression
//----------------------------------------------------------------
//Function term parses and evaluate term
//----------------------------------------------------------------
double term(bool get)
{   double left=primary(get);
    for (;;)
        switch (curr_tok) {
            case MUL:
                left*=primary(true);
            break;
            case DIV:
                left/=primary(true);
            break;
            default:
                return left;
        }//end switch
}//end term
//----------------------------------------------------------------
//Global scanner declarations
//----------------------------------------------------------------
double number_value;
string string_value;
map<string,double> table;
//----------------------------------------------------------------
//Function primary parses and evaluates primary
//----------------------------------------------------------------
double primary(bool get)
{   if (get) get_token();
    switch (curr_tok) {
        case NUMBER:         //floating point constant
        {   double v=number_value;
            get_token();
            return v;
        }
        case NAME:           //Variable name
        {   double& v=table[string_value];
            if (get_token()==ASSIGN) v=expression(true);
            return v;
        }
        case MINUS:          //Unary minus
            return -primary(true);
        case LP:
        {   double e=expression(true);
            if (curr_tok!=RP) return error("')' exprected");
            get_token();
            return e;
        }
        default:
            return error("primary expected");
    }//end switch
}//end primary
//----------------------------------------------------------------
//Function get_token obtains the next token from the input stream
//cin
//----------------------------------------------------------------
Token_value get_token()
{   char ch;
    do { //skip white space except '\n'
        if (!cin.get(ch)) return curr_tok=END;
    } while (ch!='\n' && isspace(ch));


    switch (ch) {
        case ';':
        case '\n':
            return curr_tok=PRINT;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok=Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            cin.putback(ch);
            cin>>number_value;
            return curr_tok=NUMBER;
        default:
            if (isalpha(ch)) {
                string_value=ch;
                while (cin.get(ch) && isalpha(ch)) string_value.push_back(ch);
                cin.putback(ch);
                return curr_tok=NAME;
            }//end if
            error("bad token");
            return curr_tok=PRINT;
    }//end switch
}//end get_token
//----------------------------------------------------------------
//Function main is the driver
//----------------------------------------------------------------
int main()
{
    table["pi"]=3.1415926535897932385;
    table["e" ]=2.7182818284590452354;

    while (cin) {
        get_token();
        if (curr_tok==END) break;
        if (curr_tok==PRINT) continue;
        cout << expression(false) << '\n';
    }
    return no_of_errors;
}

