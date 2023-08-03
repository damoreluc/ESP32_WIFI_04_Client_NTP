# WiFi Esempio 04: esempio di client NTP con connessione a rete WiFi

Il progetto illustra un client NTP che si collega tramite WiFi ad un server NTP e visualizza data e ora locale

---

## CONFIGURAZIONE WIFI

La scheda ESP32 è configurata come __STATION__ in una rete WiFi:

* modificare il file `WIFI/credentials.h` con i propri `SSID` e `Password`

Per il controllo dello stato della connessione vengono adoperati gli eventi dell'oggetto Wifi.

Vengono gestite le situazioni di perdita di connessione mediante riconnessione automatica.

Il pin `23` viene impiegato come uscita digitale per indicare la connessione all'access point wiFi. Per configurare un'altra posizione del led, modificare il parametro `pinWiFiConnected` nel file `HWCONFIG\hwConfig.h`

Il layer WiFi mette a disposizione due funzioni utilizzabili dai layer o protocolli superiori:

* l'evento WiFi `ARDUINO_EVENT_WIFI_STA_GOT_IP` richiama la funzione `WIFI\src\wifi_network_ready.cpp` nel cui codice è possibile programmare l'avvio dei protocolli di livello superiore
* l'evento WiFi `ARDUINO_EVENT_WIFI_STA_LOST_IP` richiama la funzione `WIFI\src\wifi_network_fail.cpp` nel cui codice è possibile gestire il ripristino dei protocolli di livello superiore

---

## SINCRONIZZAZIONE DATA/ORA CON NTP SERVER

Viene utilizzato un server __NTP__ per la gestione di data e ora:

* modificare il file `LOCALTIME/localTime.cpp` con i propri parametri NTP

Per la stampa di data e ora utilizzare la funzione `printLocalTime()`.

---

## AVVIO DEL SERVIZIO NTP

La connessione al server NTP viene svolta nella funzione ausiliaria `WIFI\src\wifi_network_ready.cpp` che è associata all'evento WiFi `ARDUINO_EVENT_WIFI_STA_GOT_IP`

Il codice della function `WiFiNetworkReady()` è:

```C
// Operazioni dei layer superiori da compiere quando è pronto il layer IP
void WiFiNetworkReady()
{
    digitalWrite(pinWiFiConnected, HIGH);

    // connect to NTP server
    connectToNTP();
    // pretty print local time and date
    printLocalTime();  
}
```

__NOTA 1__: la funzione `WiFiNetworkReady()` è utilizzabile per avviare automaticamente tutti quei servizi o protocolli che richiedono la presenza di connessione di rete.


---

## FUNZIONE SETUP()

Nella funzione `setup()` è importante rispettare la sequenza di operazioni:

1. configurare tutti i dispositivi hardware
2. assegnare i valori predefiniti a variabili/oggetti della applicazione
3. creare eventuali task RTOS
4. avviare il sotto sistema WiFi con `initWiFi_STA();`
