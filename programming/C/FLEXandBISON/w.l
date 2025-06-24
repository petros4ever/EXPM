%{
#include <stdlib.h>
void yyerror(char *);
#include "e.tab.h"
%}
%%
[A-Za-z]+ {printf("%s\n",yytext);return STRING;}
[0-9]+ {printf("%d\n",atoi(yytext));return INTEGER;}
"<LinearLayout" {printf("%s\n",yytext);return STARTOFLL;}
"<RelativeLayout" {printf("%s\n",yytext);return STARTOFRL;}
"<TextView" {printf("%s\n",yytext);return STARTOFTV;}
"<RadioGroup" {printf("%s\n",yytext);return STARTOFRG;}
"<RadioButton" {printf("%s\n",yytext);return STARTOFRB;}
"<Button" {printf("%s\n",yytext);return STARTOFB;}
"<ImageView" {printf("%s\n",yytext);return STARTOFIV;}
"<ProgressBar" {printf("%s\n",yytext);return STARTOFPB;}
"</LinearLayout>" {printf("%s\n",yytext);return SLASHLL;}
"</RelativeLayout>" {printf("%s\n",yytext);return SLASHRL;}
"</RadioGroup>" {printf("%s\n",yytext);return SLASHRG;}
"android:layout_width" {printf("%s",yytext);return ALW;}
"android:layout_height" {printf("%s",yytext);return ALH;}
"android:orientation" {printf("%s",yytext);return AO;}
"android:id" {printf("%s",yytext);return AI;}
"android:text" {printf("%s",yytext);return AT;}
"android:textColor" {printf("%s",yytext);return ATC;}
"android:src" {printf("%s",yytext);return AS;}
"android:padding" {printf("%s",yytext);return AP;}
"android:checkedButton" {printf("%s",yytext);return ACP;}
"android:max" {printf("%s",yytext);return AM;}
"android:progress" {printf("%s",yytext);return APR;}
[>] {printf("%s",yytext);return ENDTAG;}
[=] {printf("%s",yytext);return SAME;}
[/] {printf("%s",yytext);return SLASH;}
[ \t] ; /* skip whitespace */
[ \n] ; /* skip whitespace */
. {return 0;}
%%
int yywrap(void) {

}

