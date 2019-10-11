/* Weather Forecast Application: cli-args.h */

#ifndef CLI_ARGS_H_ /* Include guard */
#define CLI_ARGS_H_

extern int argc;
extern char **argv;
extern char *cli_page;
extern int help;
extern int version;
extern int debug;
extern char appversion[];

/*
 *   FUNCTION DECLARATIONS FOR cli-args.c
 */

void get_cli_args(int argc, char **argv);

#endif // AMT_H_
