/*
 * Weather Forecast Application : getpage.c
 *
 * Invokes curl library functions to download the weather data in JSON format
 * from the Dark Sky web site using data the from the provided URL. Uses the https
 * protocol only.
 *
 * Download weather data is stored in a local file called weatherdata.json
 *
 */

#include "getpage.h"

/* added to enable compile on MacOSX */
#ifndef __clang__
#include <malloc.h> /* free for use with strdup */
#endif

#include <curl/curl.h>
#include <string.h>
#include <sys/types.h>

/* Function getpage
 *  Takes two parameters:
 *       - url_req : the full url and parameters for the weather data request
 *       - pageholder : the temporary file to write the JSON data into
 *
 * function downloads the requested url and saves the output to a temporary
 * file. The function returns the result code received from the web site, or
 * exits on failure.
 *
 */
long getpage(char *url_req, FILE *pageholder)
{

        /* print out full URL request if in debug mode */
        if (debug) {
                printf("DarkSky URL request is: %s\n", url_req);
        }

        /* get handle to Curl structure */
        CURL *curl;
        CURLcode result;

        /* initialise the structure */
        curl = curl_easy_init();

        /* config Libcurl with full URL needed for the weather forecast */
        curl_easy_setopt(curl, CURLOPT_URL, url_req);
        /* set options for https when accessing DarkSky web site */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
        curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS);

        /* resolve IPv4 addresses only */
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        /* set if follow redirects(1L) or not (0L)  */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);

        /* write any downloaded data from the web site url the temporary file */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, pageholder);

        /* carry out retrieval of DarkSky weather page */
        result = curl_easy_perform(curl);

        /* check for errors */
        if (result != CURLE_OK) {
                fprintf(stderr,
                        "FAILED: Curl request returned error: '%d' : '%s'\n",
                        result, curl_easy_strerror(result));
        }

        /* get the result of the https request */
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        /* DEBUG : check what http response code was received and obtain some
         * basic performance stats for the transfer of the json data from Dark
         * Sky */
        if (debug) {
                /* print out web response code received from DarkSky site */
                printf("DarkSky web response code was: %ld\n", http_code);
                /* check to see if there was any site redirect provided? */
                char *redirect_url = NULL;
                curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirect_url);
                if (redirect_url) {
                        printf("Re-direct to web site: %s\n", redirect_url);
                }
                /* check to see if any re-directs were followed? */
                long redirects_cnt = 0L;
                curl_easy_getinfo(curl, CURLINFO_REDIRECT_COUNT,
                                  &redirects_cnt);
                printf("Number of re-directs followed: %ld\n", redirects_cnt);

                /* check the size in bytes of retrieved body data and time it
                 * took */
                curl_off_t dl;
                double total_time = 0;
                double name_lookup = 0;
                curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &dl);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
                curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &name_lookup);
                printf("Downloaded %'" CURL_FORMAT_CURL_OFF_T
                       " bytes in total time: %.1f seconds of which DNS took: "
                       "%.1f "
                       "seconds\n ",
                       dl, total_time, name_lookup);
        }

        /* clean up curl memory use */
        curl_easy_cleanup(curl);

        return http_code;
}
