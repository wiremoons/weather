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
        char *dsky_key = NULL;
        const char *siteurl = "https://api.darksky.net/forecast/";
        const char *geoloc = "/51.419212,-3.291481?units=uk2";

        if (getenv("DSAPI")) {
            dsky_key = (char *) malloc(sizeof(char) * (strlen(getenv("DSAPI")) + 1));
            if (dsky_key == NULL)
            {
                fprintf(stderr, "\nERROR: unable to allocate "
                                "DarkSky API key memory in 'get_url_details.c'\n");
                exit(EXIT_FAILURE);
            }
            dsky_key = strndup(getenv("DSAPI"), strlen(getenv("DSAPI")));

        } else {
            fprintf(stderr, "\nERROR: unable to find DarkSky API key: "
                            "set env: 'DSAPI' with key and retry.\n");
            exit(EXIT_FAILURE);
        }

        size_t url_len = (strlen(siteurl) + strlen(geoloc) + strlen(dsky_key) + 1);

        /* allocated memory for complete URL on heap */
        cli_page = (char *)malloc(sizeof(char) * url_len);

        if (cli_page == NULL)
        {
                fprintf(stderr, "\nERROR: unable to allocate "
                                "url memory in 'get_url_details.c'\n");
                exit(EXIT_FAILURE);
        }

        // copy the siteurl; dsky_key; and geoloc strings into the allocated memory for cli_page
        snprintf(cli_page,url_len,"%s%s%s",siteurl,dsky_key,geoloc);

        // return the pointer to the heap allocated memory
        return cli_page;
}
