/*
 *  MIT License
 *
 *  Copyright (c) 2019 Simon Rowe
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 *
 *  Written by Simon Rowe <simon@wiremoons.com> on 11 Oct 2019
 *  Source code available from GitHub: https://github.com/wiremoons/weather.git
 *
 *  Weather Forecast Retrieval Tool (weather)
 *
 */

#include "main.h"

/* added to enable compile on MacOSX */
#ifndef __clang__
#include <malloc.h> /* free for use with strdup */
#endif

#include <curl/curl.h> /* obtain Curl library version */
#include <locale.h>    /* number output formatting with commas */
#include <stdio.h>     /* printf */
#include <stdlib.h>    /* getenv */
#include <string.h>    /* strlen strdup */
#include <unistd.h>    /* strdup access */

int main(int argc, char **argv)
{
        /* function to run when program exits */
        atexit(exit_cleanup);

        /* Set the default locale values according to environment variables. */
        setlocale(LC_NUMERIC, "");
        // setlocale (LC_ALL, "");

        /* obtain any command line args from the user and action them */
        if (argc > 1) {

                if (strcmp(argv[1], "-h") == 0 ||
                    strcmp(argv[1], "--help") == 0) {
                        show_help();
                        return (EXIT_SUCCESS);
                }

                if (strcmp(argv[1], "-d") == 0 ||
                    strcmp(argv[1], "--debug") == 0) {
                        debug = 1;
                }

                if (strcmp(argv[1], "-v") == 0 ||
                    strcmp(argv[1], "--version") == 0) {
                        print_version_screen(argv[0]);
                        return (EXIT_SUCCESS);
                }
        }

        /* initialise the libcurl library before any use */
        curl_global_init(CURL_GLOBAL_DEFAULT);

        /* get the full URL to use with  DarkSky web site API that
         * includes the DarkSky API key and the long/lat co-ordinates
         * for the weather forecast location */
        char *cli_page = provide_url();

        /* buffer to hold contents of JSON data file */
        char *source = NULL;

        /* get FILE handle for a temporary file */
        FILE *infile = tmpfile();
        if (infile == NULL) {
                fprintf(stderr, "Unable to open a temporary file\n");
                exit(EXIT_FAILURE);
        }

        /* Request the weather data in JSON format providing the URL to
         * use and the temporary file to write the JSON output into */
        long web_result_code = getpage(cli_page, infile);

        /* expecting a '200' result code from DarkSky web site - print
         * out anything different so it can be investigated */
        if (web_result_code != 200) {
                fprintf(stderr,
                        "\nWARNING: DarkSky web site returned http "
                        "response code: %ld\n",
                        web_result_code);
        }

        /* Read the temporary file JSON data into a memory buffer
         * called 'source' ready for parsing  in the next step */
        if (fseek(infile, 0L, SEEK_END) == 0) {

                /* Get the size of the file. */
                long bufsize = ftell(infile);

                if (bufsize == -1) {
                        fprintf(stderr, "ERROR: JSON weather temporary file "
                                        "size is negative\n");
                        exit(EXIT_FAILURE);
                }

                /* Allocate our buffer to that size. */
                source = malloc(sizeof(char) * (bufsize + 1));

                if (source == NULL) {
                        fprintf(stderr,
                                "ERROR: memory allocation failed for JSON "
                                "temporary file buffer\n");
                        exit(EXIT_FAILURE);
                }

                /* Go back to the start of the file. */
                if (fseek(infile, 0L, SEEK_SET) != 0) {
                        fprintf(stderr, "ERROR: unable to move to start of the "
                                        "JSON temporary file\n");
                        exit(EXIT_FAILURE);
                }

                /* Read the entire JSON temporary file into memory. */
                size_t newLen = fread(source, sizeof(char), bufsize, infile);

                if (ferror(infile) != 0) {
                        fputs("ERROR: reading JSON temporary file", stderr);
                } else {
                        source[newLen++] = '\0'; /* Just to be safe. */
                }
        }

        /* close temporary file now no longer needed */
        fclose(infile);

        /* call parse on JSON memory file 'source' then free it */
        if (parse_now(source) == EXIT_SUCCESS) {
                if (source != NULL)
                        free(source);
                return (EXIT_SUCCESS);
        } else {
                fprintf(stderr, "Failed to parse JSON structue\n");
                if (source != NULL)
                        free(source);
                return (EXIT_FAILURE);
        }
}

/*
 * Function: exit_cleanup
 *
 * Called at end of the programs run automatically to perform
 * and clean ups such as freeing heap memory etc. Is invoked by
 * registering 'atexit()' function at beginning of main()
 *
 * Function returns nothing and is always last part to the program to
 * execute
 *
 */
void exit_cleanup(void)
{
        if (debug) {
                printf("\nRunning 'exit_cleanup' function...\n");
        }

        /* free any global variables below */
        if (cli_page != NULL) {
                free(cli_page);
        }
        /* do final clean up for libcurl */
        curl_global_cleanup();

        printf("All is well\n");
        exit(EXIT_SUCCESS);
}

/* END OF SOURCE */
