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
  ConvertMain repeatedly scans the standard input until no more data is found.
  After each scan, the program converts the input into the "day month year"
  format or prints an error.

  After converting the string the program prints it to standard output if
  convertMain encounters a blank line, it stops converting input and prints file
  "dates.dat" to the standard output.
*/
int main(int argc, const char * argv[])
{
  bool isValid = FALSE;
  char src[MAX_STR_BUFF + 1];
  char dest[MAX_STR_BUFF + 1];
  /* Repeatedly check for input */
  while(fscanf(stdin, "%s", src) > NUM_INIT)
  {
    isValid = convertDate(dest, src);
    if(isValid != TRUE)
    {
      printErrorMessage(NUM_INIT + 4);
    }
  }
  /* Print the string to standard output. */
  printDatesFile();

  return EXECUTION_STATUS;
}
/*
  Converts date input into the acceptable format and the formatted date to
  standard out.

  "day month year"

  Returns FALSE if the conversion fails for any reason.

  Input   = {char [], char *}
  Output  = {bool}
*/
bool convertDate(char dest[MAX_STR_BUFF + 1], char * src)
{
  static const char * MONTHS[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                  "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
  char * strInput = src;
  char delim = '/';
  char day[MAX_STR_BUFF + 1];
  char month[MAX_STR_BUFF + 1];
  int dayNum = NUM_INIT - 1;
  int monthNum = NUM_INIT - 1;
  int yearNum = NUM_INIT - 1;
  char year[MAX_STR_BUFF + 1];
  int strPos = NUM_INIT;
  int characterCount = NUM_INIT;

  /* Handle invalid source string */
  if(src != NULL)
  {
    /* Capture month variable */
    strPos = copyChars(month, strInput, delim);
    characterCount = strPos + 1;
    monthNum = atoi(month);
    if(strPos > NUM_INIT)
    {
      /* Capture day variable */
      strPos = copyChars(day, & strInput[characterCount], delim);
      characterCount += strPos + 1;
      if(strPos > NUM_INIT)
      {
        delim = '\0';
        /* Capture year variable */
        strPos = copyChars(year, & strInput[characterCount], delim);
        /* Print conversion */
        dayNum = atoi(day);
        yearNum = atoi(year);
        fprintf(stdout, "\n%2d", dayNum);
        fprintf(stdout, " %3s", MONTHS[monthNum - 1]);
        fprintf(stdout, " %d", yearNum);
      }
      else
      {
        /* return false if anything goes wrong */
        return FALSE;
      }
    }
    else
    {
      /* return false if anything goes wrong */

      return FALSE;
    }
  }
  /* return true otherwise */
  return TRUE;
}

/*
  Simple function to print out the contents of the dates.dat file if present

  Input   = {void}
  Output  = {void}
*/
void printDatesFile()
{
  FILE * dataFile = NULL;
  const char * datesFileName = "dates.dat";
  const char * READMODE = "r";
  char printC = NUM_INIT;
  /* Read from file */
  dataFile = fopen(datesFileName, READMODE);
  if(!dataFile)
  {
    /* Handle invalid files */
    printErrorMessage(IFILEERROR);
  }
  else
  {
    /* Print the file in a consistant formatting */
    puts("\0");
    puts("\0");
    while(printC != EOF)
    {
      printC = fgetc(dataFile);
      if(printC != EOF)
      {
        fprintf(stdout, "%c", printC);
      }
    }
    /* Close file */
    fclose(dataFile);
  }
}
