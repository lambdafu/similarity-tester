/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: lex.c,v 1.7 2012-05-08 20:16:11 Gebruiker Exp $
*/

/*	The communication variables, as set by yylex, Next_Stream_Token_Obtained
	and Next_Text_Token_Obtained.
*/

#include	"token.h"
#include	"lex.h"

Token lex_token;			/* token produced, or End_Of_Line */
unsigned int lex_nl_cnt;		/* line count */
unsigned int lex_tk_cnt;		/* token position */
unsigned int lex_non_ascii_cnt;		/* number of non-ASCII chars found */
