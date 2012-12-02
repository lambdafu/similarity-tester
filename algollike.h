/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: algollike.h,v 1.4 2012-05-06 15:37:17 Gebruiker Exp $
*/

/*	The class Algollike is a subclass of Language.  It implements
	the routines Init_Language, May_Be_Start_Of_Run and Best_Run_Size for
	ALGOL-like languages, in which it is meaningful and useful to
	isolate function bodies.

	It requires the user to define, preferably in Xlang.l, four token
	sets, represented as Token set[] and terminated by No_Token:

	Token Non_Finals[]	tokens that may not end a chunk
	Token Non_Initials[]	tokens that may not start a chunk
	Token Openers[]		openers of parentheses that must balance
					in functions
	Token Closers[]		the corresponding closers, in the same order
*/

#include	"language.h"
#include	"token.h"

extern const Token Non_Finals[];
extern const Token Non_Initials[];
extern const Token Openers[];
extern const Token Closers[];
