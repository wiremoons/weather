/*
 *  Weather Forecast Retrieval Tool (weather) : get_url_details.c
 */

#include "get_url_details.h"

/* added to enable compile on MacOSX */
#ifndef __clang__
#include <malloc.h> /* free for use with strdup */
#endif

#include <stdio.h>  /* printf */
#include <stdlib.h> /* getenv */
#include <string.h> /* strlen strdup */
#include <unistd.h> /* strdup access */

// https://api.darksky.net/forecast/<dark-skykey-here>/<geoloc-here>?units=uk2

/*
 * file: 'get_url_details.c'
 * Construct the URL required to obtains the weather forecast
 * from the DarkSky web site.
 * Needs to include API key, co-ordinates, and output format for
 * miles vs Kph etc. Allocate url string on heap and return pointer to
 * the calling function.
 */
char *provide_url(void)
{
        char *cli_page = NULL;

        char *fullurl = "https://api.darksky.net/forecast/"
                        "ADD-DARKSKY-API-KEY-HERE/"
                        "51.419212,-3.291481?units=uk2";

        /* allocated memory for complete URL on heap */
        cli_page = (char *)malloc(sizeof(char) * (strlen(fullurl) + 1));

        if (cli_page == NULL)
        {
                fprintf(stderr, "\nERROR: unable to allocate "
                                "url memory in 'get_url_details.c'\n");
                exit(EXIT_FAILURE);
        }

        // copy the fullurl string into the allocated memory for cli_page
        cli_page = strndup(fullurl, strlen(fullurl));

        // return the pointer to the heap allocated memory
        return cli_page;
}
