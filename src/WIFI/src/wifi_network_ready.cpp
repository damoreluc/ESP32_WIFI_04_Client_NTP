#include <WIFI/wifi_functions.h>
#include <HWCONFIG/hwConfig.h>
#include <LOCALTIME/localTime.h>

// Operazioni dei layer superiori da compiere quando è pronto il layer IP
void WiFiNetworkReady()
{
    digitalWrite(pinWiFiConnected, HIGH);

    // connect to NTP server
    connectToNTP();
    // pretty print local time and date
    printLocalTime();  
}
