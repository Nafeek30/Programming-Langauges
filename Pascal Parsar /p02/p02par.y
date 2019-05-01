%{
    //--------------------------------------------------------
    //File: p02par.y
    //--------------------------------------------------------
    //Standard C and C++ include files
    //--------------------------------------------------------
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <iostream>
    #include <fstream>
    #include <string>
    //--------------------------------------------------------
    //Application include files
    //--------------------------------------------------------
    #include "p02par.h"
    //--------------------------------------------------------
    //Namespaces
    //--------------------------------------------------------
    using namespace std;
    //--------------------------------------------------------
    //Externals
    //--------------------------------------------------------
    extern ofstream tfs ;
    extern int lineCounter;
    extern int columnCounter;
    //--------------------------------------------------------
    //User subroutines
    //--------------------------------------------------------
    void yyerror(const char*);
%}

%token ID
%token BEGAN
%token END
%token AND
%token ARRAY
%token INTLIT
%token COMMA
%token SEMICOLON
%token ASSIGN
%token PLUS
%token MINUS
%token SLASH
%token STAR
%token LPAREN
%token RPAREN
%token DIV
%token DO
%token ELSE
%token FOR
%token FUNCTION
%token IF
%token INTEGER
%token MOD
%token NOT
%token OF
%token OR
%token PROCEDURE
%token REAL
%token REPEAT
%token THEN
%token TO
%token UNTIL
%token VAR
%token WHILE
%token REALIT
%token CHRLIT
%token EQU
%token NEQ
%token LES
%token LEQ
%token GRT
%token GEQ
%token LBRACKET
%token RBRACKET
%token COLON
%token PERIOD
%token RANGE
%token PROGRAM

%%
program: PROGRAM ID LPAREN identifier_list RPAREN SEMICOLON declarations subprogram_declarations compound_statement PERIOD
{
    tfs << endl << "#001 program-> PROGRAM ID(identifier-list); declarations subprogram-declarations compound-statment.";
}
identifier_list: ID
{
    tfs << endl << "#002 identifier-list-> ID";
}
identifier_list: identifier_list COMMA ID
{
    tfs << endl << "#003 identifier-list-> identifier-list, ID";
}
declarations: 
{
    tfs << endl << "#004 declarations-> /\\";
}
declarations: declarations VAR identifier_list COLON type SEMICOLON
{
    tfs << endl << "#005 declarations-> VAR identifier-list : type;";
}
type: standard_type
{
    tfs << endl << "#006 type-> standard-type";
}
type: ARRAY LBRACKET INTLIT RANGE RBRACKET OF standard_type
{
    tfs << endl << "#007 type-> ARRAY[INTLIT .. INTLIT] OF standard-type";
}
standard_type: INTEGER
{
    tfs << endl << "#008 standard-type-> INTEGER";
}
standard_type: REAL
{
    tfs << endl << "#009 standard-type-> REAL";
}
subprogram_declarations:
{
    tfs << endl << "#010 subprogram-declarations-> /\\";
}
subprogram_declarations: subprogram_declarations subprogram_declaration SEMICOLON
{
    tfs << endl << "#011 subprogram-declarations-> subprogram-declarations subprogram-declaration;";
}
subprogram_declaration: subprogram_head declarations compound_statement
{
    tfs << endl << "#012 subprogram-declaration-> subprogram-head declarations compound-statement";
}
subprogram_head: FUNCTION ID arguments COLON standard_type SEMICOLON
{
    tfs << endl << "#013 subprogram-head-> FUNCTION ID arguments : standard-type;";
}
subprogram_head: PROCEDURE ID arguments SEMICOLON
{
    tfs << endl << "#014 subprogram-head-> PROCEDURE ID arguments;";
}
arguments:
{
    tfs << endl << "#015 arguments-> /\\";
}
arguments: LPAREN parameter_list RPAREN
{
    tfs << endl << "#016 arguments-> (parameter-list)";
}
parameter_list: identifier_list COLON type
{
    tfs << endl << "#017 parameter-list-> identifier-list : type";
}
parameter_list: parameter_list SEMICOLON identifier_list COLON type
{
    tfs << endl << "#018 parameter-list-> parameter-list; identifier-list : type";
}
compound_statement: BEGAN optional_statements END
{
    tfs << endl << "#019 compound-statement-> BEGIN optional-statements END";
}
optional_statements:
{
    tfs << endl << "#020 optional-statements-> /\\";
}
optional_statements: statement_list
{
    tfs << endl << "#021 optional-statements-> statement-list";
}
statement_list: statement
{
    tfs << endl << "#022 statement-list-> statement";
}
statement_list: statement_list SEMICOLON statement
{
    tfs << endl << "#023 statement-list-> statement-list; statement";
}
statement: variable ASSIGN expression
{
    tfs << endl << "#024 statement-> variable := expression";
}
statement: procedure_statement
{
    tfs << endl << "#025 statement-> procedure-statement";
}
statement: compound_statement
{
    tfs << endl << "#026 statement-> compound-statement";
}
statement: IF expression THEN statement ELSE statement
{
    tfs << endl << "#027 statement-> IF expression THEN statement ELSE statement";
}
statement: WHILE expression DO statement
{
    tfs << endl << "#028 statement-> WHILE expression DO statement";
}
variable: ID
{
    tfs << endl << "#029 variable-> ID";
}
variable: ID LBRACKET expression RBRACKET
{
    tfs << endl << "#030 variable-> ID[expression]";
}
procedure_statement: ID
{
    tfs << endl << "#031 procedure-statement-> ID";
}
procedure_statement: ID LPAREN expression_list RPAREN
{
    tfs << endl << "#032 procedure-statement-> ID(expression-list)";
}
expression_list: expression
{
    tfs << endl << "#033 expression-list-> expression";
}
expression_list: expression_list COMMA expression
{
    tfs << endl << "#034 expression-list-> expression-list, expression";
}
expression: simple_expression
{
    tfs << endl << "#035 expression-> simple-expression";
}
expression: simple_expression relop simple_expression
{
    tfs << endl << "#036 expression-> simple-expression relop simple-expression";
}
relop: EQU
{
    tfs << endl << "#037 relop-> =";
}
relop: NEQ
{
    tfs << endl << "#038 relop-> <>";
}
relop: LES
{
    tfs << endl << "#039 relop-> <";
}
relop: LEQ
{
    tfs << endl << "#040 relop-> <=";
}
relop: GRT
{
    tfs << endl << "#041 relop-> >";
}
relop: GEQ
{
    tfs << endl << "#042 relop-> >=";
}
simple_expression: term
{
    tfs << endl << "#043 relop-> term";
}
simple_expression: sign term
{
    tfs << endl << "#044 simple-expression-> sign term";
}
simple_expression: simple_expression addop term
{
    tfs << endl << "#045 simple-expression-> simple-expression addop term";
}
addop: PLUS
{
    tfs << endl << "#046 addop-> +";
}
addop: MINUS
{
    tfs << endl << "#047 addop-> -";
}
addop: OR
{
    tfs << endl << "#048 addop-> OR";
}
term: factor
{
    tfs << endl << "#049 term-> factor";
}
term: term mulop factor
{
    tfs << endl << "#050 term-> term mulop factor";
}
mulop: STAR
{
    tfs << endl << "#051 mulop-> *";
}
mulop: SLASH
{
    tfs << endl << "#052 mulop-> /";
}
mulop: DIV
{
    tfs << endl << "#053 mulop-> DIV";
}
mulop: MOD
{
    tfs << endl << "#054 mulop-> MOD";
}
mulop: AND
{
    tfs << endl << "#055 mulop-> AND";
}
factor: ID
{
    tfs << endl << "#056 factor-> ID";
}
factor: ID LPAREN expression_list RPAREN
{
    tfs << endl << "#057 factor-> ID(expression-list)";
}
factor: INTLIT
{
    tfs << endl << "#058 factor-> INTLIT";
}
factor: REALIT
{
    tfs << endl << "#059 factor-> REALIT";
}
factor: LPAREN expression RPAREN
{
    tfs << endl << "#060 factor-> (expression)";
}
factor: NOT factor
{
    tfs << endl << "#061 factor-> NOT factor";
}
sign: PLUS
{
    tfs << endl << "#062 sign-> +";
}
sign: MINUS
{
    tfs << endl << "#063 sign-> -";
}

%%
//--------------------------------------------------------
//User function section
//--------------------------------------------------------
struct Error
{
    Error(const char* m)
    {
        cout << endl << "line(" << lineCounter << ") col(" << columnCounter << ") " << m;
        cout << endl;
    }
};

void yyerror(const char* m)
{
    throw Error(m);
}

Parser::Parser(FILE* i) : Scanner(i)
{
}

Parser::~Parser()
{
}

int Parser::parse()
{
    return yyparse();
}
