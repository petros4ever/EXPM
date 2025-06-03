%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

[0-9]+          { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return FUNCTION; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL;   }
"/"             { return DIV;   }
"%"             { return MOD;   }
","             { return COMMA; }
"("             { return LPAR;  }
")"             { return RPAR;  }
[ \t]         ; 
\n              { return '\n'; }
.               { return yytext[0]; }

%%
