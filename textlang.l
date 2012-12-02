%{
/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: textlang.l,v 1.10 2012-05-09 08:26:50 Gebruiker Exp $
*/

/*
	Text front end for the similarity tester.
*/

#include	"sim.h"
#include	"language.h"
#include	"token.h"
#include	"idf.h"
#include	"lex.h"
#include	"lang.h"

/* Language-dependent Code */

void
Init_Language(void) {
	token_name = "word";
	if (!min_run_string) {
		Min_Run_Size = 8;
	}
	if (!threshold_string) {
		Threshold_Percentage = 20;
	}
}

/*ARGSUSED*/
int
May_Be_Start_Of_Run(Token tk) {
	/* any token is acceptable */
	return 1;
}

/*ARGSUSED*/
unsigned int
Best_Run_Size(const Token *str, unsigned int size) {
	/* any run size is acceptable */
	return size;
}

%}

WordElem	([-a-zA-Z\200-\377])
TightWord	({WordElem}+)

NonWordElem	([^-a-zA-Z\200-\377])
LooseElem	({WordElem}(" "))
SpacedWord	({LooseElem}+{WordElem})

%%

{TightWord}	{
		return_tk(idf_hashed(yytext));
	}

{SpacedWord}/{NonWordElem}	{
		/* the / operator works at the top level only */
		return_tk(idf_hashed(yytext));
	}


\n	{				/* count newlines */
		return_eol();
	}

.	{			/* ignore the rest */
	}

%%

/* Language-INdependent Code */

void
yystart(void) {
	BEGIN INITIAL;
}

int
yywrap(void) {
	return 1;
}
