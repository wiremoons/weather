/* Weather Forecast Application : getpage.h */

#ifndef GETPAGE_H_ /* Include guard */
#define GETPAGE_H_

/* <stdio.h> declared here as 'FILE' is used in function declaration below */
#include <stdio.h>

/* Global variable used in getpage.c */
extern int debug;

/*
 *   FUNCTION DECLARATIONS FOR getpage.c
 */

long getpage(char *url_req, FILE *pageholder);

#endif // GETPAGE_H_
