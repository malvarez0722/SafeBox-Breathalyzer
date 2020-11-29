
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include "WIFI.h"
#include <ESP8266WiFi.h>
#include <stdio.h>
#include <string.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "iP34HYmryD_CBD21JtIZuGEJDWQ0Xr9h";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ATTtejmpDS";
char pass[] = "+paz8dtsh#tw";

//char ssid[] = "SpectrumSetup-FB";
//char pass[] = "statuecosmic865";

WIFI::WIFI(){

}

void WIFI::SetupWIFI()
{
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void WIFI::BlynkWrite(int num)
{
  Blynk.run();
  Blynk.virtualWrite(0, num);
}

void WIFI::BlynkRead(){
  
}
