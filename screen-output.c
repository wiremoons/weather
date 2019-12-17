/* Weather Forecast Tool (getweather) : screen-output.c */

#include "cJSON.h"
#include "screen-output.h"

/* added to enable compile on MacOSX */
#ifndef __clang__
#include <malloc.h> /* free for use with strdup */
#endif

#include <curl/curl.h> /* obtain Curl library version */
#include <locale.h>    /* number output formatting with commas */
#include <stdio.h>     /* printf */

/*
 * Function: print_version_screen
 * Prints out the version of the application and the primary
 * libraries that the application uses.
 *
 * Intended use is from command line argument '-v' from the user.
 *
 * Function does not return any information as it just outputs to the screen
 */
void print_version_screen(char *prog_name)
{
        /* get Curl info data struct to obtain version info */
        curl_version_info_data *cdinfo = curl_version_info(CURLVERSION_NOW);

        /* output version information to the screen for application and
         * libraries */
        printf("\n"
               "'%s' version is: %s.\n"
               "Complied with Curl version: %s including support for SSL "
               "version: %s.\n"
               "cJSON library version: %s.\n",
               prog_name, appversion, cdinfo->version, cdinfo->ssl_version,
               cJSON_Version());
        printf(
            "\nFor licenses and further information visit:\n"
            " - Weather application :  https://github.com/wiremoons/weather/\n"
            " - Curl and Libcurl    :  https://github.com/curl/curl/\n"
            " - cJSON library        :  https://github.com/DaveGamble/cJSON/\n"
            "\n");
}

/*
 * Function: show_help
 * Prints to stdout the command line flags available in the application
 *
 * Intended use is from the command line argument '-h' from user.
 *
 * Function does not return any information as it just outputs to the screen
 */
void show_help(void)
{
        printf("\n"
               "Help Summary:\n"
               "The following command line switches can be used:\n"
               "\n"
               "  -h    Help     : show this help information\n"
               "  -v    Version  : show version information\n"
               "  -d    Debug    : show debug output when run\n\n");
}
