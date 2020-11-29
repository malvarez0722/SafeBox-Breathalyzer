
#ifndef wifi
#define wifi

#include <ESP8266WiFi.h>
#include <stdio.h>
#include <string.h>
//#include <BlynkSimpleEsp8266.h>

class WIFI{
  public:
    //Constructor
    WIFI();
    
    //Methods
    void SetupWIFI();
    void BlynkWrite(int num);
    void BlynkRead();
  private:

  
};

#endif
