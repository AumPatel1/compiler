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
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "    @@                             @@    �
# ECHO "    @@           %&@@@@@@@@@@@     @@    �
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    �
# ECHO "    @@      @& @   @ @       @     @@    �
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    �
# ECHO "    @@      & @ @  @@              @@    �
# ECHO "    @@       @/ @*@ @ @   @        @@    �
# ECHO "    @@           @@@@  @@ @ @      @@    �
# ECHO "    @@            /@@    @@@ @     @@    �
# ECHO "    @@     @      / /     @@ @     @@    �
# ECHO "    @@     @ @@   /@/   @@@ @      @@    �
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@         S O F I A           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: MainReader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
* Function list: (...).
*************************************************************/

/*
 *.............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: Preprocessor directives
 * The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
 * to suppress the warnings about using "unsafe" functions like fopen()
 * and standard sting library functions defined in string.h.
 * The define directive does not have any effect on other compiler projects
 * (Gcc, VSCode, Codeblocks, etc.).
 *.............................................................................
 */

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /* Check for ANSI C compliancy */
#define ANSI_C 0
#if defined(__STDC__)
#undef ANSI_C
#define ANSI_C 1
#endif

/*
 * TODO .......................................................................
 * Basically, change all datatypes to your language definitions
 * (see "Compilers.h")
 */

 /*
  * -------------------------------------------------------------
  *  Function declarations
  * -------------------------------------------------------------
  */
mobile_void bErrorPrint(mobile_string fmt, ...);
mobile_void displayBuffer(Buffer* ptr_Buffer);
mobile_long getFileSize(mobile_string fname);
mobile_intg isNumber(const mobile_string ns);
mobile_void startReader(mobile_string, mobile_string, mobile_char, mobile_intg, mobile_intg);

/*
************************************************************
* Main function from Buffer
* Parameters:
*   argc / argv = Parameters from command prompt
* Return value:
*	Success operation.
************************************************************
*/

mobile_intg mainReader(mobile_intg argc, mobile_string* argv) {

	/* Create source input buffer */
	mobile_string program = argv[0];
	mobile_string input = argv[2];
	mobile_char mode = MODE_ADDIT;
	mobile_intg size = 0, increment = 0, wrongNumber = 0;

	/* Missing file name or/and mode parameter */
	if (argc <= 2) {
		bErrorPrint("\nDate: %s  Time: %s", __DATE__, __TIME__);
		bErrorPrint("\nRuntime error at line %d in file %s\n", __LINE__, __FILE__);
		bErrorPrint("%s\b\b\b\b%s%s", argv[0], ": ", "Missing parameters.");
		bErrorPrint("Usage: <Option=0> <SourceFile> [<Mode>]");
		exit(EXIT_FAILURE);
	}

	if (argc == 4) {
		mode = *argv[3];
		switch (mode) {
		case MODE_FIXED: case MODE_ADDIT: case MODE_MULTI: break;
		default:
			bErrorPrint("%s%s%c%s%c%s%c%s", program, ": Wrong mode - choose: ",
				MODE_FIXED, ", ", MODE_ADDIT, ", ", MODE_MULTI, ".");
			exit(EXIT_FAILURE);
		}
	}
	/* Read additional parameters, if any */
	if (argc == 6) {
		mode = *argv[3];
		if (isNumber(argv[4]))size = (short)atoi(argv[4]); else wrongNumber = 1;
		if (isNumber(argv[5]))increment = (short)atoi(argv[5]); else wrongNumber = 1;
		if (wrongNumber) {
			bErrorPrint("\nDate: %s  Time: %s", __DATE__, __TIME__);
			bErrorPrint("\nRuntime error at line %d in file %s\n", __LINE__, __FILE__);
			bErrorPrint("%s\b\b\b\b%s", argv[0], ": Missing or wrong number parameters.");
			bErrorPrint("Usage: <Option=0> <SourceFile> [<Mode> <Size> <Increment>]");
			exit(EXIT_FAILURE);
		}
	}

	startReader(program, input, mode, size, increment);

	/* Return success */
	return (EXIT_SUCCESS);
}

/*
************************************************************
* Buffer starting method
* Params:
*	- Program: Name of the program
*	- Input: Filename
*	- Mode: Operational mode
*	- Size: Buffer capacity
*	- Increment: buffer increment.
************************************************************
*/
mobile_void startReader(mobile_string program, mobile_string input, mobile_char mode, mobile_intg size, mobile_intg increment) {

	BufferPointer bufferp;		/* pointer to Buffer structure */
	FILE* fileHandler;			/* input file handle */
	mobile_intg loadSize = 0;		/* the size of the file loaded in the buffer */
	mobile_char symbol;			/* symbol read from input file */

	/* Create buffer */
	bufferp = readerCreate(size, (char)increment, mode);

	if (bufferp == NULL) {
		bErrorPrint("%s%s", program,
			": Cannot allocate buffer - Use: buffer <input> <mode> <size> <increment>.");
		bErrorPrint("Filename: %s %c %d %d\n", input, mode, size, increment);
		exit(1);
	}

	/* Open source file */
	if ((fileHandler = fopen(input, "r")) == NULL) {
		bErrorPrint("%s%s%s", program, ": Cannot open file: ", input);
		exit(1);
	}

	/* Load source file into input buffer  */
	printf("Reading file %s ....Please wait\n", input);
	loadSize = readerLoad(bufferp, fileHandler);

	/* Sets the checksum */
	readerChecksum(bufferp);

	/* If the input file has not been completely loaded, find the file size and print the last symbol loaded */
	if (loadSize == READER_ERROR) {
		printf("The input file %s %s\n", input, "has not been completely loaded.");
		printf("Current size of buffer: %d.\n", readerGetSize(bufferp));
		symbol = (char)fgetc(fileHandler);
		printf("Last character read from the input file is: %c %d\n", symbol, symbol);
		printf("Input file size: %ld\n", getFileSize(input));
	}

	/* Close source file */
	fclose(fileHandler);

	/* Finishes the buffer: add end of file character (EOF) to the buffer display again */
	if ((loadSize != READER_ERROR) && (loadSize != 0)) {
		if (!readerAddChar(bufferp, READER_TERMINATOR)) {
			bErrorPrint("%s%s%s", program, ": ", "Error in compacting buffer.");
		}
	}

	/* Prints the buffer property and content */
	displayBuffer(bufferp);

	/* Free the dynamic memory used by the buffer */
	readerFree(bufferp);
	bufferp = NULL;
}

/*
************************************************************
* Error printing function with variable number of arguments
* Params: Variable arguments, using formats from C language.
*	- Internal vars use list of arguments and types from stdarg.h
*   - NOTE: The format is using signature from C Language
************************************************************
*/

mobile_void bErrorPrint(mobile_string fmt, ...) {
	/* Initialize variable list */
	va_list ap;
	va_start(ap, fmt);

	(mobile_void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	/* Move to new line */
	if (strchr(fmt, '\n') == NULL)
		fprintf(stderr, "\n");
}

/*
************************************************************
* Get buffer size
* Params:
*	- Filename: Name of the file
************************************************************
*/

mobile_long getFileSize(mobile_string fname) {
	FILE* input;
	mobile_long flength;
	input = fopen(fname, "r");
	if (input == NULL) {
		bErrorPrint("%s%s", "Cannot open file: ", fname);
		return 0;
	}
	fseek(input, 0L, SEEK_END);
	flength = ftell(input);
	fclose(input);
	return flength;
}

/*
************************************************************
 * Tests for decimal-digit character string
 * Params:
 *		- String to be evaluated as numeric
 * Return:
 *		- Number value: Returns nonzero (true) if ns is a number; 0 (False) otherwise
************************************************************
*/

mobile_intg isNumber(const mobile_string ns) {
	mobile_char c; mobile_intg i = 0;
	if (ns == NULL) return 0;
	while ((c = ns[i++]) == 0) {
		if (!isdigit(c)) return 0;
	}
	return 1;
}

/*
************************************************************
* Print function
*	- Params: buffer to print all properties.
************************************************************
*/

mobile_void displayBuffer(Buffer* ptr_Buffer) {
	printf("\nPrinting buffer parameters:\n\n");
	printf("The capacity of the buffer is:  %d\n",
		readerGetSize(ptr_Buffer));
	printf("The current size of the buffer is:  %d\n",
		readerGetPosWrte(ptr_Buffer));
	printf("The operational mode of the buffer is: %c\n",
		readerGetMode(ptr_Buffer));
	printf("The increment factor of the buffer is:  %lu\n",
		readerGetInc(ptr_Buffer));
	printf("The first symbol in the buffer is:  %c\n",
		readerGetPosWrte(ptr_Buffer) ? *readerGetContent(ptr_Buffer, 0) : ' ');
	printf("The value of the flags field is: %02hX\n",
		readerGetFlags(ptr_Buffer));
	printf("%s", "Reader statistics : \n");
	readerPrintStat(ptr_Buffer);
	printf("Number of errors: %d\n",
		readerNumErrors(ptr_Buffer));
	printf("\nPrinting buffer contents:\n\n");
	readerRecover(ptr_Buffer);
	if (!readerPrint(ptr_Buffer))
		printf("Empty buffer\n");
}
