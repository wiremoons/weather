[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/hyperium/hyper/master/LICENSE)
![](https://github.com/wiremoons/weather-C/workflows/weather-build-C/badge.svg)

# weather
Command line weather forecast retrieving tool written in C.

Example output:
```

 ∞∞ Forecast ∞∞

» Weather timezone is: 'Europe/London' at latitude: '54.419212' and longitude: '-2.291481'
» Time: Mon Dec 23 20:43:15 2019

» Weather Currenty:
        Summary:     Overcast
        Windspeed:   6.5mph
        Temperature: 6.7°C feels like: 4.7°C
        UV Index:    0

» Weather Outlook:
        'Light rain throughout the week.'


Weather forecast data: Powered by Dark Sky™
Visit: https://darksky.net/poweredby/

All is well
```


## Note

This is under early development.

The program is working - but will require a source code file edit to add your own DarkSky API key and geo location data for your own forecast area to work. Work is in progress to automate this.

If you want to change the API key and / or the longitude and latitude, the see the source file: `get_url_details.c`. 

## License

MIT
