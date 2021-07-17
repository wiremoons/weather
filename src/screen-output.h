/*
 * Weather Forecast Application : screen-output.h
 *
 */

#ifndef SCREEN_OUTPUT_H_ /* Include guard */
#define SCREEN_OUTPUT_H_

/*
 *   APPLICATION GLOBAL VARIABLES
 */
extern const char appversion[]; /* the version of the app here */

/* FUNCTION DECLARATIONS FOR screen-output.c */

void show_help(void);
void print_version_screen(char *prog_name);

#endif // SCREEN_OUTPUT_H_
