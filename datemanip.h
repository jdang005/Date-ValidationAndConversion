#ifndef datamanip_h
#define datamanip_h

typedef enum bool {FALSE, TRUE} bool;
#define EXECUTION_STATUS 0
#define NUM_INIT 0
#define MAX_STR_BUFF 80
#define FEBRUARY 2
#define ISVALIDDATEERROR 1
#define IFILEERROR 2
#define OFILEERROR 3
#define MONTHSPERYEAR 12

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* Defined in validateMain.c */
bool validateCommandInput(int, const char * *);
int validateStandardInput(int);
bool isValidDate(char *);
bool isValidMonth(char *);
bool isValidDay(char *, char *, char *);
bool isLeapYear(char *);
bool isValidYear(char *);

/* Defined in convertMain.c */
bool convertDate(char *, char *);
void printDatesFile();

/* Defined in datemanip.c */
int copyChars(char *, const char *, char);
int getLine(char *);
void printErrorMessage(int);

#endif /* datamanip_h */
