/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: stream.h,v 2.5 2012-05-04 15:49:53 Gebruiker Exp $
*/

/*
	Interface of the stream module.

	Implements the direct interaction with the lexical
	module.  It supplies the routines below.
*/

#include	"token.h"

extern int Open_Stream(const char *);
extern int Next_Stream_Token_Obtained(void);
extern void Close_Stream(void);
