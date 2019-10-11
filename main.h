/*
 * Weather Forecast Tool (weather) : main.c
 *
 * Program retrieves a weather forecast from
 * DarkSky site and parses it for display
 *
 * author:     simon rowe <simon@wiremoons.com>
 * license:    open-source released under "MIT License"
 * source:     https://github.com/wiremoons/weather
 *
 * created: 26 July 2019 - initial outline code written
 *
 */

#ifndef MAIN_H_ /* Include guard */
#define MAIN_H_

#include "cJSON.h"           /* cJSON library : github.com/DaveGamble/cJSON */
#include "cli-args.h"        /* manages the command line args from user */
#include "get_url_details.h" /* get DarkSky url for weather forecast request */
#include "getpage.h"         /* downloads the web page provided */
#include "screen-output.h"   /* displays program outputs to the screen */
#include "weather-parse.h"   /* code to parse the weather JSON from Dark Sky */

#include <stdlib.h> /* to allow NULL to be used for globals var declarations */

/*
 *   APPLICATION GLOBAL VARIABLES
 */
char appversion[] = "0.0.2"; /* set the version of the app here */
int help = 0;          /* control help outputs request 0 == off | 1 == on */
int version = 0;       /* control version outputs 0 == off | 1 == on */
int debug = 0;         /* control if debug is enabled 0 == off | 1 == on */
char *cli_page = NULL; /* URL of request to DarkSky API */

/* FUNCTION DECLARATIONS FOR main.c */

void exit_cleanup(void);

#endif // MAIN_H_
