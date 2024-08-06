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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

BufferPointer readerCreate(mobile_intg size, mobile_intg increment, mobile_intg mode) {
	BufferPointer readerPointer;
	/* TO_DO: Defensive programming */
	if (size <= 0)
		size = READER_DEFAULT_SIZE;
	if (increment <= 0)
		increment = READER_DEFAULT_INCREMENT;
	/* TO_DO: Adjust the values according to parameters */
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return NULL;
	readerPointer->content = (mobile_string)malloc(size);
	/* TO_DO: Defensive programming */
	//ask

	//is -> content neccessary or not



	if (!readerPointer->content)
		return NULL;
	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}

	readerPointer->size = size;
	readerPointer->increment = increment;
	if (mode == MODE_ADDIT || mode == MODE_FIXED || mode == MODE_MULTI)
		readerPointer->mode = mode;
	else
		readerPointer->mode = MODE_FIXED;
	/* TO_DO: Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags |= Flag_Emp;
	/* NEW: Cleaning the content */
	if (readerPointer->content)
		readerPointer->content[0] = READER_TERMINATOR;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->position.read = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, mobile_char ch) {
	mobile_string tempReader = NULL;
	mobile_intg newSize = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	if ((ch < 0) || (ch >= NCHAR))
		readerPointer->numReaderErrors++;
	/* TO_DO: Reset Realocation */
	/*

	Change


	*/
	RESET_FLAG(readerPointer->flags, READER_DEFAULT_FLAG);


	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (mobile_intg)sizeof(mobile_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		/*
		Change

		*/
		//readerPointer->content[readerPointer->position.wrte++] = ch;

	}

	/*


	askkkk

	*/
	else {
		/* TO_DO: Reset Full flag */
		/*

		cHANGE

		*/
		RESET_FLAG(readerPointer->flags, Flag_FUL);

		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < 0 || newSize > READER_MAX_SIZE) {
				SET_FLAG(readerPointer->flags, Flag_FUL);
				return NULL;
			}
			break;


		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < 0 || newSize > READER_MAX_SIZE) {
				SET_FLAG(readerPointer->flags, Flag_FUL);
				return NULL;
			}
			break;
		default:
			return NULL;
		}

		/* TO_DO: New reader allocation */
		tempReader = (mobile_string)realloc(readerPointer->content, newSize);
		/* TO_DO: Defensive programming */
		if (!tempReader) {
			return NULL;
		}
		/* TO_DO: Check Relocation */
		if (tempReader != readerPointer->content) {
			SET_FLAG(readerPointer->flags, Flag_Rel);
		}

		/*try change*/
		readerPointer->content = tempReader;
		readerPointer->size = newSize;

	}
	if ((ch >= 0) && (ch < NCHAR)) {
		/* TO_DO: Add the char */
		readerPointer->content[readerPointer->position.wrte++] = ch;
		/* TO_DO: Updates histogram */
		readerPointer->histogram[ch]++;
	}
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Adjust flags original */
	readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;
	return TRUE;
	/*


	Change


	*/
	for (int i = 0; i < NCHAR; ++i) {
		readerPointer->histogram[i] = 0;
	}


	return TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Free pointers */
	if (readerPointer->content != NULL) {
		free(readerPointer->content);
		readerPointer->content = NULL;
	}
	free(readerPointer);

	return TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Check flag if buffer is FUL */
	if (readerPointer->flags & Flag_FUL) {
		return TRUE; // Buffer is full
	}

	return FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if
		(!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Check flag if buffer is EMP */
	if (readerPointer->flags & Flag_Emp)
	{
		return TRUE;
	}
	return FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerSetMark(BufferPointer const readerPointer, mobile_intg mark) {
	// Defensive Programming
	if (!readerPointer || mark < 0 || mark >= readerPointer->position.wrte) {
		return FALSE; // Ensure readerPointer is not NULL and mark is within valid range
	}

	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;

	return TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerPrint(BufferPointer const readerPointer) {
	mobile_intg cont = 0;
	mobile_char c;

	/* Defensive programming*/
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* Ensure the buffer is not empty and valid positions */
	/*
	if (readerPointer->position.mark < 0 || readerPointer->position.mark >= readerPointer->size) {
		return FALSE;
	}

	if (readerPointer->position.wrte <= 0 || readerPointer->position.wrte > readerPointer->size) {
		return FALSE;
	}
	*/

	/* Start reading from the mark position */
	readerPointer->position.read = readerPointer->position.mark;

	/* Read and print characters */
	while (cont < readerPointer->position.wrte) {
		c = readerGetChar(readerPointer);

		/* Check for end-of-buffer or invalid characters */
		/*
		if (c == '\0' || (c < 32 && c != '\n' && c != '\r' && c != '\t')) {
			break;
		}
		*/
		printf("%c", c);
		cont++;
	}

	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerLoad(BufferPointer const readerPointer, FILE* const fileDescriptor) {
	mobile_intg size = 0;
	mobile_char c;

	/* Defensive programming: check if readerPointer and fileDescriptor are NULL */
	if (readerPointer == NULL || fileDescriptor == NULL) {
		return READER_ERROR; // Error: NULL pointer
	}

	/* Read characters from the file and add them to the buffer */
	while ((c = (mobile_char)fgetc(fileDescriptor)) != EOF) {
		/**
		if ((c < 32 && c != '\n' && c != '\r' && c != '\t') || c > 126) {
			continue; // Skip invalid characters
		}
		*/
		/* Check if the buffer has space to load characters */
		/*
		if (readerPointer->position.wrte >= readerPointer->size) {
			break; // Stop if the buffer is full
		}*/
	
		/* Attempt to add character to the buffer */
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor); // Put back the character if add fails
			return READER_ERROR; // Error: Failed to add char to buffer
		}

		size++;
	}

	return size;
}




/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	return TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer->position.read > 0) {
		readerPointer->position.read--;
	}
	else {
		return FALSE; // Ensure read offset is positive
	}

	return TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_boln readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_TERMINATOR; // Ensure readerPointer is not NULL
	}

	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		/* TO_DO: Set EOB flag */
		SET_FLAG(readerPointer->flags, Flag_End);
		return READER_TERMINATOR; // Return end of string character ('\0')
	}

	/*

	 else {
		/* TO_DO: Reset EOB flag
		*
	RESET_FLAG(readerPointer->flags, READER_FLAG_END);
}


 change , checj this is the other way by which samw tihng can be done






	*/

	/* TO_DO: Reset EOB flag */
	if (readerPointer->position.wrte > 0)
		return readerPointer->content[readerPointer->position.read++];
	return READER_TERMINATOR;
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_string readerGetContent(BufferPointer const readerPointer, mobile_intg pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || pos < 0 || pos >= readerPointer->position.wrte) {
		return NULL;
	}
	/* TO_DO: Return content (string) */
	return readerPointer->content + pos;;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return -1;
	}
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return -1;
	}

	/* TO_DO: Return wrte */
	/*


	check

	*/
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return FALSE;
	}
	/* TO_DO: Return mark */
	return readerPointer->position.mark = readerPointer->position.read;// Adjust the mark position to the current read position

}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return -1;
	}
	/* TO_DO: Return size */
	return readerPointer->size;

}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return -1;
	}

	/* TO_DO: Return increment */
	return readerPointer->increment;

}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return mode */
	return readerPointer->mode;

}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_byte readerGetFlags(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return;
	}

	/* Initialize an array to hold the histogram of characters */
	int histogram[256] = { 0 }; // Assuming ASCII characters

	/* Calculate the frequency of each character in the buffer */
	for (mobile_intg i = 0; i < readerPointer->position.wrte; i++) {
		char c = readerPointer->content[i];
		histogram[(unsigned char)c]++;
	}

	/* Print the histogram */
	printf("Character Statistics:\n");
	for (int i = 0; i < 256; i++) {
		if (histogram[i] > 0) {
			printf("'%c': %d\n", (char)i, histogram[i]);
		}
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
mobile_intg readerNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return -1;
	}
	/* Return number of errors */
	return readerPointer->numReaderErrors;
}

/*
***********************************************************
* Function name: readerChecksum
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

mobile_void readerChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return;
	}

	/* TO_DO: Adjust the checksum to flags */
	/* TO_DO: Calculate the checksum */
	mobile_intg checksum = 0;
	for (mobile_intg i = 0; i < readerPointer->position.wrte; ++i) {
		checksum += readerPointer->content[i];
	}

	/* Use only the 4 initial bits of the checksum */
	checksum &= 0xF; // Mask to keep only the lowest 4 bits

	/* TO_DO: Adjust the checksum to flags */
	// Clear the current checksum bits in the flags
	//readerPointer->flags &= ~READER_FLAG_CHKSUM;//

	// Set the new checksum value in the flags

	readerPointer->flags &= 0xF0; /* Clear previous checksum bits*/
	readerPointer->flags |= (checksum & 0x0F); /* Set new checksum bits*/
	return;
}
