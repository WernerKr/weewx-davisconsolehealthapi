# weewx-davisconsolehealthapi
Collect and display station health information from the new Davis Console API

Modified from author uajqq

Weewx service that pulls device health (telemetry) information from Davis Instruments weather Console. 
I made this extension for users like me who have the new DAVIS Console. 

The code makes one API calls per archive period: 
to the "current" v2 API, which contains values like the console battery status and firmware version. 


The data are stored in their own database, since most of the fields don't exist within the default weewx database. 

Please note: This driver don't pull from the "Historic Data" API, which 
requires a paid monthly subscription from Davis to use (starting at about $4/month). 
See here: https://weatherlink.github.io/v2-api/data-permissions

## Data
Right now, the service records the following information from the Davis Console API (here with values):

"battery_voltage":4226
"wifi_rssi":-56
"console_radio_version":"10.3.2.90"
"console_api_level":28
"queue_kilobytes":4
"free_mem":699453
"system_free_space":747118
"charger_plugged":1
"battery_percent":100
"local_api_queries":null
"health_version":1
"link_uptime":31130
"rx_kilobytes":20465563
"console_sw_version":"1.2.13"
"connection_uptime":31113
"os_uptime":1187518
"battery_condition":2
"internal_free_space":2215120
"battery_current":0.003
"battery_status":5
"database_kilobytes":108347
"battery_cycle_count":1
"console_os_version":"1.2.11"
"bootloader_version":2
"clock_source":2
"app_uptime":1186355
"tx_kilobytes":181662

"battery_temp":33		it's not know if this is °C or what else (seems to be °C)

## Installation
Install the extension:

`sudo wee_extension --install davisconsolehealthapi.zip`


## Configuration
By default, the installer installs `davisconsolehealthapi` as a service, allowing your station to keep collecting weather information via its usual driver. 
It runs during every archive interval and inserts data into its own SQL database.

Example in the weewx.conf

[davishealthapi]

    data_binding = davisconsolehealthapi_binding
    station_id = ?????
    packet_log = 0
    max_age = None # default is 2592000
    api_key = ????????????????????????????????
    api_secret = ????????????????????????????????

##packet_log = 0 -> none logging - log once: "Found current data from data ID %s Struc"
##packet_log = 1 -> "Found current data from data ID %s Sensortype %s" 
##packet_log = 3 -> Log all received packets "packet: %s" % record
##packet_log = 5 -> Log all current received Data "c_data: %s" % data

### API keys
Once installed, you need to add your Davis WeatherLink Cloud API key, station ID, and secret. 
To obtain an API key and secret, go to your WeatherLink Cloud account page and look for a button marked "Generate v2 Token." 
Once you complete the process, enter your key and secret where indicated in weewx.conf.

### Station ID
Davis doesn't make it easy to make API calls, and you have to make an API call to get your station ID. 
To help the process along, I adapted one of Davis' example Python scripts to make an API call that shows your station ID. 
To use it, look for the file `davis_api_toolc.py` in the zip file you downloaded. 
Open it in a text editor and type in your API key/secret where indicated. 
Save the file and run it like so:

`python3 davis_api_toolc.py`

It should return 3 URLs. Open that in a browser (don't delay, the timestamp is encoded in that URL and the Davis API will reject the call 
if you wait too long to make the call) and you'll get back a string of text. Your station ID will be near the beginning. 
Enter that number into weewx.conf and you should be good to go.
       v2 API URL: Stations
       v2 API URL: Current
       v2 API URL: Historic (only availabe with paid subscription from Davis) so here not supported!


## Usage
Once you enable the service/driver and get it running, you won't notice anything different. 

### Own skin health
The files for this new skin (additional to the Seasons skin) are found under 
skins/healthc


The necessary file are there stored during the installation.
Also the stanza in the weeewx.conf

        [StdReport]
          [[DavisCOnsoleHealth]]
             HTML_ROOT = /var/www/html/weewx/healthc
             enable = true
             skin = healthc 

In skin.conf:

        [[[daysignalC]]]
            title = Signal Strength
            data_binding = davisconsolehealthapi_binding
            yscale = -100.0, -30.0, 10
            [[[[rssiC]]]]

This should give you a result like this:


***In all cases, note that you have to specify the database binding as `davisconsolehealthapi_binding` 
whenever you are referencing the DavisHealthAPI data!!*** 
Take a look at the example files to see how that's been done so you can adapt it for your own purposes.
