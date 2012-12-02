/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: language.h,v 1.4 2012-05-06 15:37:18 Gebruiker Exp $
*/

/*	The abstract class Language contains the routines Init_Language,
	May_Be_Start_Of_Run and Best_Run_Size which describe in some sense the
	language and which are required by compare.c.

	These routines must be provided by all Xlang.l files.
*/

#include	"token.h"

extern void Init_Language(void);
extern int May_Be_Start_Of_Run(Token ch);
extern unsigned int Best_Run_Size(const Token *str, unsigned int size);
