/* Weather Forecast Application : cli-args.c */

#include "cli-args.h"

/* added to enable compile on MacOSX */
#ifndef __clang__
#include <malloc.h> /* free for use with strdup */
#endif

#include <ctype.h>  /* isdigit */
#include <getopt.h> /* getopt long */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* getenv */
#include <string.h> /* strlen strdup */
#include <unistd.h> /* strdup access */

/* Function: get_cli_args
 * Used to parse command line arguments provided by the user when run.
 * Options to be extracted and used when the program is run.
 * Uses the POSIX compliant getopts()
 *
 * Global varialbles are used to set options as flags. Consequently
 * the function does not return any data itself.
 */
void get_cli_args(int argc, char **argv)
{
        opterr = 0;
        int c = 0;

        while ((c = getopt(argc, argv, "hvd")) != -1) {
                switch (c) {

                case 'h':
                        help = 1;
                        break;

                case 'v':
                        version = 1;
                        break;

                case 'd':;
                        debug = 1;
                        break;

                case ':':
                        fprintf(
                            stderr,
                            "\nERROR: '%s' option '-%c' requires an argument\n",
                            argv[0], optopt);
                        exit(EXIT_FAILURE);
                        break;

                case '?':
                default:
                        fprintf(stderr,
                                "\nERROR: '%s' option '-%c' is invalid "
                                "or missing input data\n",
                                argv[0], optopt);
                        exit(EXIT_FAILURE);
                        break;
                }
        }
}
