/*	This file is part of the software similarity tester SIM.
	Written by Dick Grune, Vrije Universiteit, Amsterdam.
	$Id: algollike.c,v 2.8 2012-05-06 15:37:17 Gebruiker Exp $
*/

/*	This module implements the routines Init_Language, May_Be_Start_Of_Run
	and Best_Run_Size for ALGOL-like languages, in which it is meaningful
	and useful to isolate function bodies.

	It requires the user to define, preferably in Xlang.l, four token
	sets, represented as Token set[] and terminated by No_Token:

	Token Non_Finals[]	tokens that may not end a chunk
	Token Non_Initials[]	tokens that may not start a chunk
	Token Openers[]		openers of parentheses that must balance
					in functions
	Token Closers[]		the corresponding closers, in the same order
*/

#include	"options.h"
#include	"token.h"
#include	"algollike.h"

/*	Arrays for fast identification tests for tokens.  Each token is
	identified by its position in the set + 1.  For example, if tk is
	the n-th Opener, openers[Token2int(tk)] == n+1.
*/
static char non_finals[N_REGULAR_TOKENS];
static char non_initials[N_REGULAR_TOKENS];
static char openers[N_REGULAR_TOKENS];
static char closers[N_REGULAR_TOKENS];

static int
pos_in_set(const char set[], const Token tk) {
	if (!is_regular_token(tk)) return 0;
	return set[Token2int(tk)];
}

static void cvt2bittable(const Token *tl, char bt[N_REGULAR_TOKENS]);
static unsigned int largest_function(const Token *str, unsigned int size);

void
Init_Language(void) {
	/* convert the token sets to bitmaps */
	cvt2bittable(Non_Finals, non_finals);
	cvt2bittable(Non_Initials, non_initials);
	cvt2bittable(Openers, openers);
	cvt2bittable(Closers, closers);
}

static void
cvt2bittable(const Token *tl, char bt[N_REGULAR_TOKENS]) {
	/* assumes bt[] is cleared */
	int i;
	int cnt = 1;

	for (i = 0; !Token_EQ(tl[i], No_Token); i++) {
		bt[Token2int(tl[i])] = cnt++;
	}
}

int
May_Be_Start_Of_Run(const Token tk) {
	return pos_in_set(non_initials, tk) == 0;
}

unsigned int
Best_Run_Size(const Token *tka, unsigned int size) {
	/*	Checks the run starting at tka[0] with length size for
		acceptability in the language.  Cuts from the end if
		necessary and returns the accepted length, which may
		be zero.
	*/

	if (is_set_option('f')) {
		/* reduce to a function-like form first */
		size = largest_function(tka, size);
	}

	while (	/* there is trailing garbage */
	       size != 0 && pos_in_set(non_finals, tka[size-1])
	) {
		/* remove it */
		size--;
	}

	return size;
}

static unsigned int
largest_function(const Token *tka, unsigned int size) {
	/*	Returns the size of the longest sequence starting at
		tka[0] and not containing unbalanced parentheses.
		Does not check the nesting of the parentheses, but then,
		sim is syntax-free anyway.
	*/
	unsigned int mrb_size = 0;  /* most recent balancing size */
	unsigned int pos;
	int i;
	int balance_count[N_REGULAR_TOKENS];
	/* Overkill: only a fraction of the tokens are balancers; oh well. */
	int n_imbalances;

	/* clear administration */
	n_imbalances = 0;
	for (i = 0; i < N_REGULAR_TOKENS; i++) {
		balance_count[i] = 0;
	}

	/* scan tka[] and see how far we get */
	for (pos = 0; pos < size; pos++) {
		Token tk = tka[pos];
		int pp;		/* parenthesis position */

		/* account for openers */
		if ((pp = pos_in_set(openers, tk))) {
			if (balance_count[pp] == 0) {
				/* about to create an imbalance */
				n_imbalances++;
			}
			balance_count[pp]++;
		}

		/* account for closers */
		if ((pp = pos_in_set(closers, tk))) {
			if (balance_count[pp] == 0) {
				/* this is one Closer too many */
				return mrb_size;
			}
			balance_count[pp]--;
			if (balance_count[pp] == 0) {
				/* we just cleared an imbalance */
				n_imbalances--;
			}
		}

		if (n_imbalances == 0) {
			/* register balance point */
			mrb_size = pos + 1;
		}
	}
	return mrb_size;
}
