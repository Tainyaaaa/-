%option noyywrap nodefault yylineno batch
%{
#include "part2.h"
#include "part2.tab.h"
%}
digit [0-9]
letter [a-zA-Z]
identifier {letter}({letter}|{digit})*
decimal [0]|[1-9]{digit}*
octal [0][0-7]+
hexa [0][xX][0-9a-fA-F]+
iloct [0][0-7]*[89]{digit}*
ilhex [0][xX][0-9a-fA-F]*[g-zG-Z]({letter}|{digit})*
%%
[ \n\t]+ {;}
if {return IF;}
then {return THEN;}s
else {return ELSE;}
while {return WHILE;}
do {return DO;}
";" {return EOL;}
">=" {return GE;}
"<=" {return LE;}
"<>" {return NE;}
"+"|"-"|"*"|"/"|">"|"<"|"="|"("|")"|"{"|"}" {return yytext[0];}
{identifier} {yylval.c = yytext; return IDN;}
{decimal} {yylval.c = yytext; return DEC;}
{octal} {yylval.c = yytext; return OCT;}
{hexa} {yylval.c = yytext; return HEX;}
{iloct} {yylval.c = yytext; return ILOCT;}
{ilhex} {yylval.c = yytext; return ILHEX;}
<<EOF>> {yyterminate();}
%%

