#include "Sense.h"

configuration SenseAppC 
{ 
} 
implementation { 
  
  components SenseC, MainC, LedsC, new TimerMilliC();
  components new SensirionSht11C();
  components new HamamatsuS1087ParC();

  components ActiveMessageC;
  components new AMSenderC(AM_SENSE);


  SenseC.Boot -> MainC;
  SenseC.Leds -> LedsC;
  SenseC.Timer -> TimerMilliC;

  SenseC.readTemp -> SensirionSht11C.Temperature;
  SenseC.readHumidity -> SensirionSht11C.Humidity;
  SenseC.readPhoto -> HamamatsuS1087ParC;

  SenseC.Packet -> AMSenderC;
  SenseC.AMPacket -> AMSenderC;
  SenseC.AMControl -> ActiveMessageC;
  SenseC.AMSend -> AMSenderC;

}
