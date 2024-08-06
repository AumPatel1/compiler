/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@           %&@@@@@@@@@@@     @@    ”
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    ”
# ECHO "    @@      @& @   @ @       @     @@    ”
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    ”
# ECHO "    @@      & @ @  @@              @@    ”
# ECHO "    @@       @/ @*@ @ @   @        @@    ”
# ECHO "    @@           @@@@  @@ @ @      @@    ”
# ECHO "    @@            /@@    @@@ @     @@    ”
# ECHO "    @@     @      / /     @@ @     @@    ”
# ECHO "    @@     @ @@   /@/   @@@ @      @@    ”
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@         S O F I A           @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 47

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	
	FL_T,		/* 13: Float literal token */
	ID_T,		/* 14: Identifier token */
	OP_T,		/* 15: Operator token */
	SYMB_T,		/* 16: Symbol token */
    ADD_T,		/* 17: Addition operator token */
	SUB_T,		/* 18: Subtraction operator token */
	MUL_T,		/* 19: Multiplication operator token */
	DIV_T,		/* 20: Division operator token */
	MOD_T,		/* 21: Modulus operator token */
	EXP_T,		/* 22: Exponentiation operator token */
	ASSIGN_T,	/* 23: Assignment operator token */
	EQ_T,		/* 24: Equal to operator token */
	NE_T,		/* 25: Not equal to operator token */
	GT_T,		/* 26: Greater than operator token */
	LT_T,		/* 27: Less than operator token */
	GE_T,		/* 28: Greater than or equal to operator token */
	LE_T,		/* 29: Less than or equal to operator token */
	AND_T,		/* 30: Logical AND operator token */
	OR_T,		/* 31: Logical OR operator token */
	NOT_T,		/* 32: Logical NOT operator token */
	IF_T,		/* 33: if keyword token */
	ELSE_T,		/* 34: else keyword token */
	FOR_T,		/* 35: for keyword token */
	WHILE_T,	/* 36: while keyword token */
	REPEAT_T,	/* 37: repeat keyword token */
	BREAK_T,	/* 38: break keyword token */
	NEXT_T,		/* 39: next keyword token */
	FUNC_T,		/* 40: function keyword token */
	RETURN_T,	/* 41: return keyword token */
	DOT_T,		/* 42: Dot token */
	COMMA_T,	/* 43: Comma token */
	COLON_T,	/* 44: Colon token */
	SEMICOLON_T, /* 45: Semicolon token */
ARROW_RIGHT_T  ,// Define a value for the '->' token
 ARROW_LEFT_T   // Define a value for 

    
};

/* TO_DO: Define the list of keywords */
static mobile_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	mobile_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	mobile_intg intValue;				/* integer literal attribute (value) */
	mobile_intg keywordIndex;			/* keyword index in the keyword table */
	mobile_intg contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	mobile_real floatValue;				/* floating-point literal attribute (value) */
	mobile_char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	mobile_char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	mobile_byte flags;			/* Flags information */
	union {
		mobile_intg intValue;				/* Integer value */
		mobile_real floatValue;			/* Float value */
		mobile_string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	mobile_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	mobile_intg scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '"'
#define CHRCOL5 '/'
#define CHRCOL6 '*'
#define CHRCOL7 '#'
#define CHRCOL8 '\n'
#define CHRCOL9 '.'
#define CHRCOL10 '{'
#define CHRCOL11 '}'
#define CHRCOL12 '<'
#define CHRCOL13 '>'
#define CHRCOL14 '('
#define CHRCOL15 ')'
//#define CHRCOL16 '"'
#define CHRCOL17 '\''

//#define CHRCOL18 '''
/* These constants will be used on VID / MID function */
#define MNID_SUF '&'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /*/* TO_DO: State transition table definition 
#define NUM_STATES		10
#define CHAR_CLASSES	8

/* TO_DO: Transition table - type of states defined in separate table
static mobile_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) *
	{     1, ESNR, ESNR, ESNR,    4, ESWR,	  6, ESNR},	// S0: NOAS
	{     1,    1,    1,    2,	  3,    3,   3,    3},	// S1: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S2: ASNR (MVID)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S3: ASWR (KEY)
	{     4,    4,    4,    4,    5, ESWR,	  4,    4},	// S4: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S5: ASNR (SL)
	{     6,    6,    6,    6,    6, ESWR,	  7,    6},	// S6: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S7: ASNR (COM)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S8: ASNR (ES)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS}  // S9: ASWR (ER)
};
*/
#define NUM_STATES 16
#define CHAR_CLASSES 17

// State transition table
static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*      L(A-Z),  D(0-9),   U(_),  M(&)  R("),    S(/),  A(*),   H(#),  E(Enter),  P(.),    {-}      <,    >,    (,      ),     ",     Q(')
			       0,      1,    2,    3,    4,     5,      6,      7,     8,          9,      10,      11,   12    13,    14,     15     16 
	/* S0 */ {     1,      9,    1,   ESWR,  13,    6,     ESWR,    3,    ESWR,     ESWR,      ESWR,    ESWR, ESWR, ESWR,  ESWR	, ESWR,	  15},	//NOFS(1) },
	/* S1 */ {     1,      1,    1,    2,    2,     2,      2,      2,     2,         2,       2,       2,      2,   2,      2 ,   2,     2},	// NOFS(2)
	/* S2 */ {    FS,     FS,   FS,   FS,    FS,    FS,   FS,       FS,    FS,        FS,      FS,     FS,      FS,  FS,    FS,    FS,   FS},//FSW(VAR | MET)
	/* S3 */ {     3,      3,    3,    3,     3,     3,    3,      3,        4,		  3,      3,       3,       3,   3,     3,     3,     3},//NOFS(3) },
	/* S4 */ {    FS,     FS,   FS,   FS,    FS,    FS,   FS,    FS,        FS,		FS,      FS,	   FS,      FS,  FS,     FS,    FS,    FS},	// SLC },
	/* S5 */ {    ESWR,   ESWR,ESWR, ESWR,    6,  ESWR, ESWR,  ESWR,      ESWR,		ESWR,    ESWR,	 ESWR,     ESWR, ESWR  ,  ESWR,  ESWR,  ESWR},	//NOFS(5) },
	/* S6 */ {     6,      6,    6,    6,     6,     6,    7,    6,       6,   	     6,       6,       6,       6,    6,      6,     6,     6},	//NOFS(6) },
	/* S7 */ {    6,      6,    6,    6,     6,     6,    7,     6,        6,   	 6,       6,       6,       6,     6,      6,     6,     6},//NOFS(7) },
	/* S8 */ {    FS,     FS,   FS,   FS,    FS,    FS,   FS,   FS,        FS,		FS,      FS,	   FS,      FS,  FS,     FS,    FS,    FS },//MLC },
	/* S9 */ {    10,      9,    10,    10,   10,   10,   10,    10,       10,   	10,       10,      10,      10,   10,    10,    10,    10},	// NOFS(9) },
	/* S10*/ {     FS,     FS,   FS,   FS,    FS,    FS,   FS,    FS,        FS,	 FS,      FS,	   FS,      FS,  FS,     FS,    FS,    FS},	 //FSW(IL) },
	/* S11*/ {    12,      12,   12,   12,    12,    12,    12,   12,      12,   	12,       12,       12,     12,   12,    12,    12,    12},	// NOFS(11) },
	/* S12*/ {    FS,     FS,   FS,   FS,    FS,    FS,   FS,   FS,        FS,		FS,      FS,	   FS,      FS,  FS,     FS,    FS,    FS},	//FSW(FL) },
	/* S13*/ {    13,     13,   13,   13,    14,    13,   13,   13,       13,		13,      13,	   13,      13,    13,   13,    13,     13},// NOFS(13) },
	/* S14*/ {    FS,     FS,   FS,   FS,    FS,    FS,   FS,   FS,        FS,		FS,      FS,	   FS,      FS,  FS,     FS,    FS,    FS},	//SL },
	/* S15*/ {    13,     13,   13,   13,    13,    13,   13,   13,       13,		13,      13,	   13,      13,    13,   13,    13,     14},// NOFS(15) },
};

/*** assssssssssssssssssssssssssk/



/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
//static mobile_intg stateType[NUM_STATES] = {
	//NOFS, /* 00 */
//	NOFS, /* 01 */
//	FSWR, /* 02 (MID) - Methods */
//	NOFS, /* 03 (KEY) */
//	FSNR, /* 04 */
//	NOFS, /* 05 (SL) */
//	NOFS, /* 06 */
//	NOFS, /* 07 (COM) */
//	NOFS, /* 08 (Err1 - no retract) */
//	FSNR,  /* 09 (Err2 - retract) */
//	FSWR, /* 10 */
//	NOFS, /* 11 */
//	FSWR, /* 12 */
//	NOFS, /* 13 */
//	FSNR, /* 14 */
//	FSNR, /* 15 */


//};

static mobile_intg stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (MID) - Methods */
	NOFS, /* 03 (KEY) */
	FSNR, /* 04 */
	NOFS, /* 05 (SL) */
	NOFS, /* 06 */
	NOFS, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSNR,  /* 09 (Err2 - retract) */
	FSWR, /* 10 */
	NOFS, /* 11 */
	FSWR, /* 12 */
	NOFS, /* 13 */
	FSNR, /* 14 */
	NOFS, /* 15 */


};
/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
mobile_intg			startScanner(BufferPointer psc_buf);
static mobile_intg	nextClass(mobile_char c);					/* character class function */
static mobile_intg	nextState(sofia_intg, sofia_char);		/* state machine function */
mobile_void			printScannerData(ScannerData scData);
Token				tokenizer(sofia_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(mobile_string lexeme);

/* Declare accepting states functions */
Token funcSL	(mobile_string lexeme);
Token funcIL	(mobile_string lexeme);
Token funcID	(mobile_string lexeme);
Token funcCMT   (mobile_string lexeme);
Token funcKEY	(mobile_string lexeme);
Token funcErr	(mobile_string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
//static PTR_ACCFUN finalStateTable[NUM_STATES] = {
//	NULL,		/* -    [00] */
	//NULL,		/* -    [01] */
	//funcKEY,	/* MNID	[02] */
//	NULL,	/* KEY  [03] */
//	funcSL,		/* -    [04] */
//	NULL,		/* SL   [05] */
//	NULL,		/* -    [06] */
//	NULL,	/* COM  [07] */
//	funcSL,	/* ERR1 [08] */
//	NULL,		/* ERR2 [9] */
//	funcKEY,		/* -    [10] /  INTEGER LITERAL IN REAL*/
//	NULL,		/* -    [11] */
//	funcKEY,	/* MNID	[12] */  //  FLOAT LITERAL IN REAL
//	NULL,	/* KEY  [13] */
//	funcSL,		/* -    [14] */
//	NULL,		/* SL   [15] */

//};

static PTR_ACCFUN finalStateTable[NUM_STATES] = {
		NULL,		/* -    [00] */
		NULL,		/* -    [01] */
		funcKEY,	/* MNID	[02] */
		funcKEY,	/* KEY  [03] */
		funcCMT,		/* -    [04] */
		funcSL,		/* SL   [05] */
		NULL,		/* -    [06] */
		funcCMT,	/* COM  [07] */
		funcCMT,//funcErr,	/* ERR1 [08] */
		NULL,		/* -    [09] */
		funcKEY,//NULL,	/* -    [10] */
		NULL,		/* -    [11] */
		funcKEY,//NULL		/* -    [12] */
		NULL,		/* -    [13] */
		funcSL,//funcCMT	/* -    [14] */
		NULL,		/* -    [15] */

};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 17

/* TO_DO: Define the list of keywords */
static mobile_string keywordTable[KWT_SIZE] = {
	
	"code",		/* KW01 */
	"int",		/* KW02 */
	"real",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do",		/* KW09 */
	"for",      /* KW10 */
	"repeat",   /* KW11 */
	"break",    /* KW12 */
	"next",     /* KW13 */
	"function", /* KW14 */
	"return",   /* KW15 */
	"TRUE",     /* KW16 */
	"FALSE"		/* KW17 */
	
	
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	mobile_char indentationCharType;
	mobile_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
mobile_intg numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
