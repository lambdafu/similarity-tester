/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: tokenarray.h,v 1.3 2012-05-06 09:42:11 Gebruiker Exp $
*/

#include	"token.h"

/* Interface for the token storage */
extern void Init_Token_Array(void);
extern void Store_Token(Token tk);
extern unsigned int Text_Length(void);	/* also first free token position */
extern Token *Token_Array;

