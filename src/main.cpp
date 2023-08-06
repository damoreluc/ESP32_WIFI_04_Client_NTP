/*
 * WiFi Esempio 04: esempio di client NTP con connessione a rete WiFi
 *
 * Il progetto illustra un client NTP che si collega tramite WiFi ad un server NTP 
 * e visualizza data e ora locale
 * 
 * CONFIGURAZIONE WIFI ------------------------------------------------------------------------------
 * La scheda ESP32 è configurata come STATION in una rete WiFi: 
 * modificare il file WIFI/credentials.h con i propri SSID e Password
 * Per il controllo dello stato della connessione vengono adoperati gli eventi dell'oggetto Wifi
 * Vengono gestite le situazioni di perdita di connessione mediante riconnessione automatica.
 * Il pin 23 viene impiegato come uscita digitale per indicare la connessione all'access point wiFi.
 * 
 * SINCONIZZAZIONE DATA/ORA CON NTP SERVER ----------------------------------------------------------
 * Viene utilizzato un server NTP per la gestione di data e ora:
 * modificare il file LOCALTIME/localTime.cpp con i propri parametri NTP 
 * 
  * FUNZIONE SETUP() ---------------------------------------------------------------------------
 * Nella funzione setup() è importante rispettare la sequenza di operazioni:
 * 1. configurare tutti i dispositivi hardware
 * 2. assegnare i valori predefiniti a variabili/oggetti della applicazione
 * 3. creare eventuali task RTOS
 * 4. avviare il sotto sistema WiFi con initWiFi_STA();
 * 
 */

// include delle librerie minime necessarie
#include <Arduino.h>
#include <HWCONFIG/hwConfig.h>
#include <WiFi.h>
#include <WIFI/wifi_functions.h>

// altre librerie richieste dalla applicazione specifica
#include <LOCALTIME/localTime.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("WiFi Esempio 04: esempio di client NTP con connessione a rete WiFi");

  // impiega il metodo macAddress() dell'oggetto WiFi
  Serial.println();
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  // avvia la connessione ad un access point e registra gli handler degli eventi WiFi;
  // con l'evento GotIP vengono avviate le connessioni:
  // al server NTP

  initWiFi_STA();
}

void loop()
{
  // aggiorna data ed ora ogni 1 secondo
  printLocalTime();

  // pausa di 1 secondo
  vTaskDelay(pdMS_TO_TICKS(1000));
}