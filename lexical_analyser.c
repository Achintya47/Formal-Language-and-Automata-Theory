/* Revised Parser */

#include <stdio.h>
#include "lex.h"

void factor (void);
void term (void);
void expression (void);

statements(){
	/* statements -> expression SEMI | expression SEMI statements*/
	while( !match(EOI)){
		expression();

		if(match(SEMI))
			advance();
		else
			fprintf(stderr, "%d: Inserting missing csemicolon\n", yylineno);
	}
}

