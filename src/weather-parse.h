/* Weather Forecast Application : weather-parse.h */

#ifndef WEATHER_PARSE_H_ /* Include guard */
#define WEATHER_PARSE_H_

#include "cJSON.h" /* parson JSON library */

/* GLOBAL Variables */
extern int debug;

/*
 *   FUNCTION DECLARATIONS FOR weather-parse.c
 */

int parse_now(char *json_source);

#endif // WEATHER_PARSE_H
