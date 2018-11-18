/*
  Author        : Justin Danglade
  Student ID    : 4552415
  Course        : COP4338
  Section       : U04
  Instructor    : William Feild
  Due Date      : November 6, 2018
*/

#include "datemanip.h"

/*
  Copy one seqeuence of characters into the location of a string given a
  deliminating character. The destination string must allow for complete unix
  command-line input, 80 character input, plus a single null character at the
  end to ensure that the char pointer is pointing to a string. A character count
  is kept so that the null character is always inserted at the very end of the
  sequence in the destination string. The character count is returned.

  If the source character pointer is NULL or if the deliminator character is not
  found within 80 characters, the destination is assigned to null and 0 is
  returned.

  Input   = {char [MAX_STR_BUFF + 1], char *, char}
  Output  = {int}
*/
int copyChars(char dest[MAX_STR_BUFF + 1], const char * src, char delim)
{
  int charCount = NUM_INIT;
  /* Reject invalid source strings */
  if(src == NULL)
  {
    dest = NULL;
    return NUM_INIT;
  }

  /* Count the number of characters until the deliminator is found */
  while(src[charCount] != delim || charCount > MAX_STR_BUFF)
  {
    charCount ++;
  }
  /*
    If the deliminator is not found within the MAX_STR_BUFF characters, return
    NULL
  */
  if(charCount > MAX_STR_BUFF)
  {
    dest = NULL;
    return NUM_INIT;
  }
  /* Copy src into the destination array and return its address via a pointer */
  strncpy(dest, src, charCount);
  /* Make destination a string */
  dest[charCount] = '\0';
  return charCount;
}

/*
  Reads from the standard input a line of characters and copies each character
  of a single line into the destination array, dest. If no newline is found
  within MAX_STR_BUFF character, the input is considered invalid and the number
  of characters read is set to 0.

  Returns the number of character read from standard input.

  Input   = {char [MAX_STR_BUFF + 1]}
  Output  = {int}
*/
int getLine(char dest[MAX_STR_BUFF + 1])
{
  int charactersRead = NUM_INIT;
  char thisChar = '\0';
  /* End reading when a newline or an EOF character are found. */
  /* End reading when charactersRead is greater than the MAX_STR_BUFF */
  while(thisChar != '\n' && thisChar != EOF && charactersRead <= MAX_STR_BUFF)
  {
    thisChar = getc(stdin);
    /* create a string when the line ends */
    if(thisChar == '\n' || thisChar == EOF)
    {
      dest[charactersRead] = '\0';
    }
    else /* otherwise copy the data into dest */
    {
      dest[charactersRead] = thisChar;
    }
    /* increment the charactersRead variable */
    charactersRead ++;
  }

  /*
    If the characters read exceeds the MAX_STR_BUFF variable the line was
    invalid and charactersRead is set to 0 and set the last character in dest to
    '\0'.
  */
  if(charactersRead > MAX_STR_BUFF || thisChar == EOF)
  {
    charactersRead = NUM_INIT;
    dest[MAX_STR_BUFF] = '\0';
  }
  return charactersRead;
}

/*
  Function that can print multiple termination messages. The modes are used to
  modify the message(s) printed to the standard error stream.

  mode = 0      : Represents invalid command line arguments.
  mode = 1      : Represents invalid date.
  mode = 2      : Represents invalid input.
  mode = 3      : Represents invalid output.
  any other mode: Represents and undefined reason for termination.

  Input   = {int}
  Output  = {void}
*/
void printErrorMessage(int mode)
{
  char * message1 = '\0';
  /* Assign message to print */
  if(mode == NUM_INIT)
  {
    /* Additional details are printed */
    char * message2 = '\0';
    char * message3 = '\0';

    message1 = "\nInvalid command input";
    message2 = "\nThe command argument must be an integer, x, such that x >= 0";
    message3 = "\nThe largest integer on this system is: \n";
    fprintf(stderr, "%s%s%s%d", message1, message2, message3, INT_MAX);
    fputs("\0", stderr);
  }
  else if(mode == NUM_INIT + 1)
  {
    message1 = "\nInvalid Date\n";
    fprintf(stderr, "%s", message1);
    fputs("\0", stderr);
  }
  else if(mode == NUM_INIT + 2)
  {
    message1 = "\nInvalid Input File\n";
    fprintf(stderr, "%s", message1);
    fputs("\0", stderr);
  }
  else if(mode == NUM_INIT + 3)
  {
    message1 = "\nInvalid Output File\n";
    fprintf(stderr, "%s", message1);
    fputs("\0", stderr);
  }
  else
  {
    /* Undefined reason for termination */
    message1 = "\nUndefined reason for termination!\n";
    fprintf(stderr, "%s", message1);
    fputs("\0", stderr);
  }
}
