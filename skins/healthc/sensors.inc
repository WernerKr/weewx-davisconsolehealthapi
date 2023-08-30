## sensors module for weewx skins
## Copyright Tom Keffer, Matthew Wall
## See LICENSE.txt for your rights

## Modified to work with the DavisConsoleHealthAPI extension to display device info

#errorCatcher Echo
#encoding UTF-8

## this is a conditional display of sensor data, including connectivity,
## battery status, and various voltages.  if there are no data available,
## then this degenerates to nothing displayed.

#def get_battery_status($x)
#if $x == 0
<span class="status_ok">$gettext("OK")</span>
#else
<span class="status_low">$gettext("LOW")</span>
#end if
#end def

#set $conns = ["signalQuality", "rssiC"]
#set $battery_statuses = [ "txBatteryFlag" ]
#set $max_battery_statuses = 5

#set $transm = [ "freeMemC", "systemFreeSpaceC", "iFreeSpaceC", "queueKilobytesC", "databaseKilobytesC" ]

##

<div id='sensors_widget' class="widget">
  <div class="widget_title">
    $gettext("Status Davis Console")
    <a class="widget_control"
      onclick="toggle_widget('sensors')">&diams;</a>
  </div>
  <div class="widget_contents">
  <table>

    <tr><th>$gettext("Connectivity")</th><th></th></tr>
 #for $x in $conns
  #if $getattr($current($max_delta=3600,$data_binding='davisconsolehealthapi_binding'), $x).has_data
    <tr>
      #if 'signalQuality' in $x
       #set $color = 'blue'
      #else
       #set $color = 'black'
      #end if
      <td class="label"><font color=$color>$obs.label[$x]</font></td>
      #set $xv = $getattr($current($max_delta=3600,$data_binding='davisconsolehealthapi_binding'), $x) 
      <td class="data">$xv</td>
    </tr>
  #end if
 #end for

    <tr><th>$gettext("Power Status")</th><th></th></tr>
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').consoleBatteryC.has_data
    <tr>
      <td class="label">$obs.label.consoleBatteryC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').consoleBatteryC.format("%.0f")</td>
    </tr>
#end if
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryPercentC.has_data
    <tr>
      <td class="label">$obs.label.batteryPercentC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryPercentC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.batteryCurrentC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryCurrentC.format("%.3f")</td>
    </tr>
#end if
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryConditionC.has_data
    <tr>
      <td class="label">$obs.label.batteryConditionC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryConditionC</td>
    </tr>
#end if
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryStatusC.has_data
    <tr>
      <td class="label">$obs.label.batteryStatusC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryStatusC</td>
    </tr>
#end if
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryTempC.has_data
    <tr>
      <td class="label">$obs.label.batteryTempC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryTempC</td>
    </tr>
#end if
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').chargerPluggedC.has_data
    <tr>
      <td class="label">$obs.label.chargerPluggedC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').chargerPluggedC</td>
    </tr>
#end if
#if $current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryCycleCountC.has_data
    <tr>
      <td class="label">$obs.label.batteryCycleCountC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').batteryCycleCountC</td>
    </tr>
#end if

#set $count = 0
 #if $count != 0
 #for $x in $battery_statuses 
  #set $count = $count + 1  
  #if $getattr($current($max_delta=3600,$data_binding='davisconsolehealthapi_binding'), $x).has_data
    <tr>
      <td class="label">$obs.label[$x]</td>
      #set $xv = $getattr($current($max_delta=3600,$data_binding='davisconsolehealthapi_binding'), $x) 
      <td class="data">$get_battery_status($xv.raw)</td>
    </tr>
  #else
   #if $count <= $max_battery_statuses
    <tr>
      <td class="label"><font color='red'>$obs.label[$x]</font></td>
      <td class="data"><font color='red'>N/A</font></td>
    </tr>
   #end if
  #end if
 #end for
 #end if

 <tr><th>$gettext("Data Transmission")</th><th></th></tr>

 #for $x in $transm
  #if $getattr($current($max_delta=3600,$data_binding='davisconsolehealthapi_binding'), $x).has_data
    <tr>
      #if 'packetStreak' in $x
       #set $color = 'green'
      #else
       #set $color = 'black'
      #end if
      <td class="label"><font color=$color>$obs.label[$x]</font></td>
      #set $xv = $getattr($current($max_delta=3600,$data_binding='davisconsolehealthapi_binding'), $x) 
      <td class="data">$xv</td>
    </tr>
  #end if
 #end for

    <tr>
      <td class="label">$obs.label.rxKilobytesC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').rxKilobytesC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.txKilobytesC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').txKilobytesC</td>
    </tr>

    <tr>
      <td class="label">$obs.label.localAPIQueriesC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').localAPIQueriesC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.consoleApiLevelC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').consoleApiLevelC</td>
    </tr>

    <tr><th>$gettext("Information Console")</th><th></th></tr>

    <tr>
      <td class="label">$obs.label.appUptimeC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').appUptimeC.long_form(format_string="%(day)d%(day_label)s, %(hour)d:%(minute)02d:%(second)02d")</td>
    </tr>
    <tr>
      <td class="label">$obs.label.linkUptimeC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').linkUptimeC.long_form(format_string="%(day)d%(day_label)s, %(hour)d:%(minute)02d:%(second)02d")</td>
    </tr>
    <tr>
      <td class="label">$obs.label.connectionUptimeC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').connectionUptimeC.long_form(format_string="%(day)d%(day_label)s, %(hour)d:%(minute)02d:%(second)02d")</td>
    </tr>
    <tr>
      <td class="label">$obs.label.osUptimeC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').osUptimeC.long_form(format_string="%(day)d%(day_label)s, %(hour)d:%(minute)02d:%(second)02d")</td>
    </tr>

    <tr>
      <td class="label">$obs.label.consoleRadioVersionC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').consoleRadioVersionC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.consoleSwVersionC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').consoleSwVersionC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.consoleOsVersionC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').consoleOsVersionC</td>
    </tr>

    <tr>
      <td class="label">$obs.label.bootloaderVersionC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').bootloaderVersionC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.clockSourceC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').clockSourceC</td>
    </tr>
    <tr>
      <td class="label">$obs.label.healthVersionC</td>
      <td class="data">$current($max_delta=3600,$data_binding='davisconsolehealthapi_binding').healthVersionC</td>
    </tr>


  </table>
  </div>

</div>
