%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int yylex(void);
void yyerror(const char *s);

int square(int x) { return x * x; }
int max(int a, int b) { return (a > b) ? a : b; }
%}

%union {
    int ival;
    char* sval;
}

%token <ival> NUMBER
%token <sval> FUNCTION
%token PLUS MINUS MUL DIV MOD LPAR RPAR COMMA

%type <ival> expr term function_call

%left PLUS MINUS
%left MUL DIV MOD

%%

input:
    expr '\n'        { printf("Result = %d\n", $1); }
  | '\n'             { /* empty line */ }
  ;

expr:
    expr PLUS expr    { $$ = $1 + $3; }
  | expr MINUS expr   { $$ = $1 - $3; }
  | expr MUL expr     { $$ = $1 * $3; }
  | expr DIV expr     { $$ = $1 / $3; }
  | expr MOD expr     { $$ = $1 % $3; }
  | term              { $$ = $1; }
  ;

term:
    NUMBER            { $$ = $1; }
  | LPAR expr RPAR    { $$ = $2; }
  | function_call     { $$ = $1; }
  ;

function_call:
    FUNCTION LPAR expr RPAR {
        if (strcmp($1, "square") == 0)
            $$ = square($3);
        else {
            fprintf(stderr, "Unknown function: %s\n", $1);
            $$ = 0;
        }
        free($1);
    }
  | FUNCTION LPAR expr COMMA expr RPAR {
        if (strcmp($1, "max") == 0)
            $$ = max($3, $5);
        else {
            fprintf(stderr, "Unknown function: %s\n", $1);
            $$ = 0;
        }
        free($1);
    }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    return yyparse();
}
