/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: lex.h,v 2.8 2012-05-07 16:28:33 Gebruiker Exp $
*/

/*	Since the lex_X variables are hoisted unchanged through the levels
	lang, stream, and buff, to be used by pass1, pass2, etc., they
	have to be placed in a module of their own.
*/

#include	"token.h"

extern Token lex_token;			/* token produced, or End_Of_Line */
extern unsigned int lex_nl_cnt;		/* line count */
extern unsigned int lex_tk_cnt;		/* token position */
extern unsigned int lex_non_ascii_cnt;	/* # of non-ASCII chars found */
