#include "lex.h"
#include <stdio.h>
#include <ctype.h>

char *yytext = ""; // Lexeme (not '\0' terminated)
int yyleng = 0; // Lexeme length
int yylineno = 0; // Input line number

lex() {
    static char input_buffer[28];
    char *current;

    current = yytext + yyleng;
    
    while(1) {
        while(!*current) {
            /*
            Get new lines, skipping any leading and white space
            on the line, until a nonblank line is found
            */
           current = input_buffer;
           if(!gets(input_buffer)) {
                *current = '\0';
                return EOI;
           }
           ++yylineno;
           
           while(isspace(*current))
            ++current;
        }

        for(; *current; ++current){
            // Get the next token

            yytext = current;
            yyleng = 1;
            
            switch(*current){
                case EOF: 
                    return EOI;
                    break;
                case ';':
                    return SEMI;
                    break;
                case '+':
                    return PLUS;
                    break;
                case '*':
                    return TIMES;
                    break;
                case '(':
                    return LP;
                    break;
                case ')':
                    return RP;
                    break;
                
                case ' ':
                case '\n':
                case '\t':
                    break;
                
                default:
                    if(!isalnum(*current))
                        fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
                    else{
                        while(isalnum(*current))
                            ++current;
                        yyleng = current - yytext;
                        return NUM_OR_ID;
                    }
                    break;
            }
        }
    }
}
