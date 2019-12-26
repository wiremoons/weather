/* Weather Forecast Tool (getweather) : weather-parse.c */

#include "weather-parse.h"

/* added to enable compile on MacOSX */
#ifndef __clang__
#include <malloc.h> /* free for use with strdup */
#endif

#include <stdio.h>  /* printf */
#include <stdlib.h> /* getenv */
#include <string.h> /* strlen strdup */
#include <time.h>   /* time struct */
#include <unistd.h> /* strdup access */

/* Function parse_now
 *  To parse Dark Sky weather forecast JSON output and
 *  display the resulting weather forecast to the screen
 */
int parse_now(char *json_source)
{
        /* check some JSON formatted weather data has been passed
         *  to the function for processing
         */
        if (json_source == NULL) {
                fprintf(stderr, "ERROR: JSON source is empty\n");
                return (EXIT_FAILURE);
        }

        /* parse the JSON from the buffer obtained from the data.json file */
        cJSON *weather_json = cJSON_Parse(json_source);
        /* check valid JSON data was obtained from the initial parse */
        if (weather_json == NULL) {
                const char *error_ptr = cJSON_GetErrorPtr();
                if (error_ptr != NULL) {
                        fprintf(stderr, "ERROR: in parse weather before: %s\n",
                                error_ptr);
                        cJSON_Delete(weather_json);
                        return (EXIT_FAILURE);
                }
        }

        /* Send first output to screen */
        printf("\n ∞∞ Forecast ∞∞\n\n");

        /* get object data from main JSON objects */
        const cJSON *timezone = NULL;
        const cJSON *latitude = NULL;
        const cJSON *longitude = NULL;

        /* print each data entry extracted to screen */
        timezone = cJSON_GetObjectItemCaseSensitive(weather_json, "timezone");
        if (cJSON_IsString(timezone) && (timezone->valuestring != NULL)) {
                printf("» Weather timezone is : '%s'\n", timezone->valuestring);
        }

        latitude = cJSON_GetObjectItemCaseSensitive(weather_json, "latitude");
        if (cJSON_IsNumber(latitude)) {
                printf("» Weather location is : latitude: '%f' ",
                       latitude->valuedouble);
        }

        longitude = cJSON_GetObjectItemCaseSensitive(weather_json, "longitude");
        if (cJSON_IsNumber(longitude)) {
                printf("and longitude: '%f'\n", longitude->valuedouble);
        }

        /* get additional objects from the JSON output object 'currently' */
        const cJSON *currently = NULL;
        const cJSON *time = NULL;
        const cJSON *windSpeed = NULL;
        const cJSON *summary = NULL;
        const cJSON *temperature = NULL;
        const cJSON *apparentTemperature = NULL;
        const cJSON *uvIndex = NULL;

        /* print each 'currently' data entry extracted to screen */
        currently = cJSON_GetObjectItem(weather_json, "currently");
        if (currently == NULL) {
                fprintf(
                    stderr,
                    "ERROR: unable to parse 'current' weather conditions\n");
        } else {

                time = cJSON_GetObjectItemCaseSensitive(currently, "time");
                if (cJSON_IsNumber(time)) {
                        time_t rawtime = (time_t)(long)time->valueint;
                        printf("» Forecast date is    : %s",
                               asctime(localtime(&rawtime)));
                }

                printf("\n» Weather Currenty:\n");
                summary =
                    cJSON_GetObjectItemCaseSensitive(currently, "summary");
                if (cJSON_IsString(summary) && (summary->valuestring != NULL)) {
                        printf("    Summary     : %s\n", summary->valuestring);
                }

                windSpeed =
                    cJSON_GetObjectItemCaseSensitive(currently, "windSpeed");
                if (cJSON_IsNumber(windSpeed)) {
                        printf("    Windspeed   : %.1fmph\n",
                               windSpeed->valuedouble);
                }

                temperature =
                    cJSON_GetObjectItemCaseSensitive(currently, "temperature");
                if (cJSON_IsNumber(temperature)) {
                        printf("    Temperature : %.1f°C ",
                               temperature->valuedouble);
                }

                apparentTemperature = cJSON_GetObjectItemCaseSensitive(
                    currently, "apparentTemperature");
                if (cJSON_IsNumber(apparentTemperature)) {
                        printf("feels like: %.1f°C\n",
                               apparentTemperature->valuedouble);
                }

                uvIndex =
                    cJSON_GetObjectItemCaseSensitive(currently, "uvIndex");
                if (cJSON_IsNumber(uvIndex)) {
                        printf("    UV Index    : %d\n", uvIndex->valueint);
                }
        }

        /* get objects from the json output object 'daily' */
        const cJSON *daily = NULL;
        const cJSON *dsummary = NULL;

        /* print each 'daily' data entry extracted to screen */
        daily = cJSON_GetObjectItem(weather_json, "daily");
        if (daily == NULL) {
                fprintf(stderr,
                        "ERROR: unable to parse 'daily' weather conditions\n");
        } else {
                dsummary = cJSON_GetObjectItemCaseSensitive(daily, "summary");
                if (cJSON_IsString(summary) &&
                    (dsummary->valuestring != NULL)) {
                        printf("\n» Days' Outlook:\n    '%s'\n",
                               dsummary->valuestring);
                }
        }

        /* end output with DarkSky required source use notification */
        printf("\n\nWeather forecast data: Powered by Dark Sky™\n");
        printf("Visit: https://darksky.net/poweredby/\n\n");

        /* DEBUG: print out a prettified version of the whole json file */
        if (debug) {
                char *rendered = cJSON_Print(weather_json);
                FILE *json_out;
                json_out = fopen("weatherdata.json", "w+");
                if (json_out != NULL) {
                        fprintf(json_out, "%s\n", rendered);
                        printf("See file 'weatherdata.json' for complete copy "
                               "of JSON "
                               "output received from DarkSky\n");
                        fclose(json_out);
                } else {
                        fprintf(stderr, "WARNING: Unable to open debug JSON "
                                        "file: 'weatherdata.json'\n");
                }
                free(rendered);
        }

        /* clean up cJSON data structures */
        cJSON_Delete(weather_json);
        return (EXIT_SUCCESS);

        /*END OF parse_now() */
}
