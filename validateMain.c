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
  ValidateMain begins by validating the command-line input, followed by
  validating existence of the standard input, then validating the input provided
  by the standard input. Those values from the standard input that meet the
  required "month/day/year" string formatting will be counted as valid and
  printed to the standard output. When are command line argument has been
  satisfied by the number of dates validated, the program terminates
  successfully. If there are any errors in the program will print the reason for
  the error to the screen and terminate unsuccessfully.
*/
int main(int argc, const char * argv[])
{
  bool isValid = FALSE;
  char * strInput = NULL;
  int LOCATIONTOVALIDATE = argc - 1;
  int commandArg = NUM_INIT;
  int terminationMode = NUM_INIT - 1;
  int numOfValidDates = NUM_INIT;

  isValid = validateCommandInput(argc, argv);
  if(isValid == TRUE)
  {
    commandArg = atoi(argv[LOCATIONTOVALIDATE]);
    numOfValidDates = validateStandardInput(commandArg);
  }
  else
  {
    terminationMode = NUM_INIT;
    printErrorMessage(terminationMode);
  }
  return EXECUTION_STATUS;
}

/*
  Checks the validity of the command-line input.

  Valid command-line input has two arguments, the program execution call, and a
  single string that can be interpreted as an integer greater than or equal to
  zero.

  Returns TRUE if the input is valid, FALSE otherwise.

  Input   = {int, const char * []}
  Output  = {bool}
*/
bool validateCommandInput(int numOfArgs, const char * strArgs[])
{
  /* There is only one argument allowed, located at the end of argv */
  /* The lowest int value acceptable is zero */
  const int CORRECTNUMOFARGS = 2;
  const int LOCTOVERIFY = CORRECTNUMOFARGS - 1;
  const int LOWESTBOUND = NUM_INIT;
  /* The maximum amount of characters, excluding the null character is 80 */
  char strInput[MAX_STR_BUFF + 1];
  int numInput = NUM_INIT;
  char delim = '\0';
  bool isValid = FALSE;

  /* Verify number of arguments */
  if(numOfArgs == CORRECTNUMOFARGS)
  {
    /* Verify if the argument at LOCTOVERIFY is an integer. */
    copyChars(strInput, strArgs[LOCTOVERIFY], delim);
    if(strInput == NULL)
    {
      isValid = FALSE;
    }
    isValid = isValidYear(strInput);
    if(isValid == TRUE)
    {
      numInput = atoi(strInput);
      /* Verify range of numInput */
      if(numInput < LOWESTBOUND)
      {
        isValid = FALSE;
      }
    }
    else
    {
      isValid = FALSE;
    }
  }
  else
  {
    isValid = FALSE;
  }
  return isValid;
}

/*
  Reads data from the standard input, entire lines are determined whether or not
  the line is a valid date:
  "month/day/year"

  The number of lines that are required to be validated is determined by the
  commandInput variable. If commandInput is 0 the entire standard input is
  validated line by line. If commandInput is greater than the number of valid
  dates in the standard input, then the entire standard input is validated and
  the function terminates.

  Every valid date found is printed to the standard output, raises a signal
  so that other processes can process the standard output, and pauses until a
  signal is raised.

  Returns the number of valid dates found.

  Input   = {int}
  Output  = {int}
*/
int validateStandardInput(int commandInput)
{
  char strInput[MAX_STR_BUFF + 1];
  bool isValid = FALSE;
  bool nextLine = FALSE;
  int numOfValidDates = NUM_INIT;

  /* Begin reading from standard input */
  nextLine = TRUE;
  while(nextLine == TRUE)
  {
    /*
      Command input of zero indicates to stop at the end of file
    */
    if(commandInput == NUM_INIT)
    {
      if(feof(stdin) != NUM_INIT)
      {
        nextLine = FALSE;
      }
    }
    else
    {
      /*
        Any other valid command input should stop when the number of valid dates
        is equal to the command input or when the end of file is reach, which
        ever comes first.
      */
      if(numOfValidDates >= commandInput || feof(stdin) != NUM_INIT)
      {
        nextLine = FALSE;
      }
    }
    /* Read every line until the nextLine variable is FALSE */
    if(nextLine != FALSE)
    {
      getLine(strInput);
      /*
        If the string is valid increment the counter, print to screen, and raise
        a signal for other processes.
      */
      isValid = isValidDate(strInput);
      if(isValid == TRUE)
      {
        numOfValidDates ++;
        fprintf(stdout, strInput);
        puts("\0");
      }
    }
  }
  /* return number of validated date strings */
  return numOfValidDates;
}

/*
  Checks if the string possibleDate is a valid date, composed of a valid month,
  a valid day, and a valid year in the format:

  month/day/year"

  String input must be with a single line of console input on a standard unix
  machine, so the string is confined to 80 characters. Predicate zeros will be
  ignored and a single negative symbol is allowed before any digits are taken.

  Returns TRUE if possibleDate is a valid date, FALSE otherwise.

  Input   = {char *}
  Output  = {bool}
*/
bool isValidDate(char * possibleDateSeq)
{
  static const char SEPERATOR = '/';
  static const char ENDOFSTR = '\0';
  static const int CORRECTSEPCOUNT = 2;
  bool isDate = FALSE;
  bool isMonth  = FALSE;
  bool isYear = FALSE;
  bool isDay = FALSE;
  int seperatorCount = NUM_INIT;
  int firstSepLocation = NUM_INIT;
  int secondSepLocation = NUM_INIT;
  int strPos = NUM_INIT;
  char possibleDate[MAX_STR_BUFF + 1];
  char possibleMonth[MAX_STR_BUFF + 1];
  char possibleDay[MAX_STR_BUFF + 1];
  char possibleYear[MAX_STR_BUFF + 1];

  /*
    copy the possibleDateSeq to possibleDate ensure the value is a string of the
    correct size.
  */
  if(copyChars(possibleDate, possibleDateSeq, ENDOFSTR) > NUM_INIT)
  {
    /* Check every character in the sequence */
    while(possibleDate[strPos] != ENDOFSTR)
    {
      /*
        When a '/' character is encountered, keep track of which seperator is
        found, first or second, and it's respective location in the sequence.
      */
      if(possibleDate[strPos] == SEPERATOR)
      {
        seperatorCount ++;
        if(firstSepLocation == NUM_INIT)
        {
          firstSepLocation = strPos;

        }
        else if(secondSepLocation == NUM_INIT)
        {
          secondSepLocation = strPos;
        }
      }
      /* Check the next character */
      strPos ++;
    }
    /*
      If there are exactly two seperators in the sequence, copy the characters
      before the first '/' into the possibleMonth variable, copy the characters
      after the first and before the second '/' character into the possibleDay
      variable, and copy the characters that come after to the possibleYear
      variable.
    */
    if(seperatorCount == CORRECTSEPCOUNT)
    {
      copyChars(possibleMonth, possibleDateSeq, SEPERATOR);
      copyChars(possibleDay,
                & possibleDateSeq[firstSepLocation + 1],
                SEPERATOR);
      copyChars(possibleYear,
                & possibleDateSeq[secondSepLocation + 1],
                ENDOFSTR);
    }
    /*
      all arguments, possibleMonth, possibleDay, and possibleYear, must be valid
      must be valid for possibleDay to be valid.
    */
    isDay = isValidDay(possibleMonth, possibleDay, possibleYear);
    isDate = isDay;
  }
  return isDate;
}

/*
  Determines if the string possibleMonth is a valid month in the year.

  String input must be with a single line of console input on a standard unix
  machine, so the string is confined to 80 characters. Predicate zeros will be
  ignored and a single negative symbol is allowed before any digits are taken.

  Valid input is a string that can be represented as a number in the range 1
  to 12 inclusive. Returns TRUE if the string is valid, FALSE otherwise.

  Input   = {char *}
  Output  = {bool}
*/
bool isValidMonth(char * possibleMonth)
{
  bool isMonth = FALSE;
  int month = NUM_INIT;

  isMonth = isValidYear(possibleMonth);
  if(isMonth == TRUE)
  {
    month = atoi(possibleMonth);
    if(month < 1 || month > MONTHSPERYEAR)
    {
      isMonth = FALSE;
    }
  }
  return isMonth;
}

/*
  Determines if the string possibleDay is a valid day in the month considering
  whether or not the year is a leap year. In order for a day to be valid, the
  string possibleMonth, and possibleYear must be a valid month and a valid year
  respectively and the day must be a day within that month of that year.

  String input must be with a single line of console input on a standard unix
  machine, so the string is confined to 80 characters. Predicate zeros will be
  ignored and a single negative symbol is allowed before any digits are taken.

  This function takes three strings as input and returns a bool value of TRUE if
  possibleDay is valid, FALSE otherwise.

  Input   = {char *, char *, char *}
  Output  = {bool}
*/
bool isValidDay(char * possibleMonth, char * possibleDay, char * possibleYear)
{
  static const int DAYSPERMONTH[MONTHSPERYEAR] = {31, 28, 31, 30, 31, 30, 31,
                                                  31, 30, 31, 30, 31};
  bool isDay = FALSE;
  bool isMonth = FALSE;
  bool isYear = FALSE;
  bool isLYear = FALSE;
  int day = NUM_INIT;
  int month = NUM_INIT;
  int year = NUM_INIT;
  int range = NUM_INIT;

  /*
    A valid day is an integer between 1 through range inclusive. Both the month
    and the year must be valid as well.
  */
  isMonth = isValidMonth(possibleMonth);
  isYear = isValidYear(possibleYear);
  if(isYear == TRUE && isMonth)
  {
    month = atoi(possibleMonth);
    year = atoi(possibleYear);
    isDay = isValidYear(possibleDay);
    if(isDay == TRUE)
    {
      day = atoi(possibleDay);
      isLYear = isLeapYear(possibleYear);

      /* If the year is a leap year and the month is February */
      /* The range of days available for February is increased by one */
      if((isLYear == TRUE) && (month == FEBRUARY))
      {
        range = (DAYSPERMONTH[month - 1] + 1);
      }
      else /* Otherwise the range is standard */
      {
        range = DAYSPERMONTH[month - 1];
      }
      /*
        If the day provided falls outside the appropriate range, the day is
        invalid.
      */
      if(day < 1 || day > range)
      {
        isDay = FALSE;
      }
    }
  }
  return isDay;
}

/*
  Function to determine if a string of characters can be represented as an
  validYear. Returns TRUE if the string of characters is an integer, FALSE
  otherwise.

  String input must be with a single line of console input on a standard unix
  machine, so the string is confined to 80 characters. Predicate zeros will be
  ignored and a single negative symbol is allowed before any digits are taken.

  Input   = {char *}
  Output  = {bool}
*/
bool isValidYear(char * possibleYear)
{
  int strPos = NUM_INIT;
  int digits = NUM_INIT;
  long longStorage = NUM_INIT;
  bool negativeNum = FALSE;

  /* Count the number of digits in possibleInt. */
  while(possibleYear[strPos] != '\0' &&  possibleYear[strPos] != EOF)
  {
    /*
      If the character being inspected is a digit, increment the number of
      digits counted.
    */
    if(possibleYear[strPos] > 47 && possibleYear[strPos] < 58)
    {
      digits ++;
      strPos ++;
    }
    else
    {
      /* check for a single predicate negative symbol */
      if(possibleYear[strPos] == '-' && digits == NUM_INIT)
      {
        if(negativeNum == TRUE)
        {
          return FALSE;
        }
        negativeNum = TRUE;
        strPos ++;
      }
      else if(possibleYear[strPos] != '\0' &&  possibleYear[strPos] != EOF)
      {
        /*
          If any other symbol other than the null character or EOF interupts the
          string, the string is not an int.
        */
        return FALSE;
      }
    }
  }
  /*
    If the number of digits in the string is beyond the maximum buffer size for
    a string, the string is not an int.
  */
  if(digits > MAX_STR_BUFF)
  {
    return FALSE;
  }
  /*
    Exclude values outside the range of INT_MIN...INT_MAX
  */
  longStorage = atol(possibleYear);
  if(longStorage < INT_MIN || longStorage > INT_MAX)
  {
    return FALSE;
  }
  return TRUE;
}

/*
  Determines if sequence of characters is a leap year. A leap year is a valid
  year that is divisible by four except for those years which are both divisible
  by 100 and not divisible by 400.

  String input must be with a single line of console input on a standard unix
  machine, so the string is confined to 80 characters. Predicate zeros will be
  ignored and a single negative symbol is allowed before any digits are taken.

  Takes sequence of characters, possibleLeapYear, as input and returns TRUE if
  possibleLeapYear is a leap year, returns FALSE otherwise.

  The logic used in this function detailed in chapter 5 section 7 of the book
  "The C Programming Language" by Brian Kernighan and Dennis Ritchie,
  Prentice-Hall ISBN:0-13-110362-8

  Input   = {char *}
  Output  = {bool}
*/
bool isLeapYear(char * possibleLeapYear)
{
  static const int leapYearNum = 4;
  static const int leapNumExceptionOne = 100;
  static const int leapNumExceptionTwo = 400;
  bool leapYear = FALSE;
  int year = NUM_INIT;

  /* Leap years must be valid years */
  leapYear = isValidYear(possibleLeapYear);
  /* Any multiple of four is also a multiple of 400. */
  if(leapYear == TRUE)
  {
    year = atoi(possibleLeapYear);
    leapYear = (year % leapYearNum == NUM_INIT &&
    year % leapNumExceptionOne != NUM_INIT ||
    year % leapNumExceptionTwo == NUM_INIT);
  }
  return leapYear;
}
