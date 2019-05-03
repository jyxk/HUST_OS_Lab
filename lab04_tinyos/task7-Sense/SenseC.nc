#include "Timer.h"
#include "SensirionSht11.h"
#include "Sense.h"
#include "printf.h"

module SenseC {
  uses {
    interface Boot;
    interface Leds;
    interface Timer<TMilli>;
  }

  uses {
    interface Packet;
    interface AMPacket;
    interface AMSend;
    interface SplitControl as AMControl;
  }

  uses {
    interface Read<uint16_t> as readTemp;
    interface Read<uint16_t> as readHumidity;
    interface Read<uint16_t> as readPhoto;
  }
}
implementation {
  // sampling frequency in binary milliseconds
  #define SAMPLING_FREQUENCY 100

  bool busy = FALSE;
  message_t sensor_packet;

  uint16_t TempData;
  uint16_t HumidityData;
  uint16_t PhotoData;


  
  event void Boot.booted() {
    call Timer.startPeriodic(TIMER_PERIOD_MILLI);
    call AMControl.start();
  }

  event void Timer.fired() {
    call readTemp.read();
    call readHumidity.read();
    call readPhoto.read();
  }

  event void readTemp.readDone(error_t result, uint16_t data) {
    if (!busy && result == SUCCESS) {
      SensorMsg *payload = (SensorMsg *) call Packet.getPayload(&sensor_packet, sizeof(SensorMsg));
      if (payload == NULL) {
        return ;
      }
      payload->nodeid = TOS_NODE_ID;
      payload->type = TEMPERATURE;
      payload->data = data;
      if (call AMSend.send(AM_BROADCAST_ADDR, &sensor_packet, sizeof(SensorMsg)) == SUCCESS) {
        call Leds.led0Toggle();
        busy = TRUE;
      }
    }
  }

  event void readHumidity.readDone(error_t result, uint16_t data) {
    if (!busy && result == SUCCESS) {
      SensorMsg *payload = (SensorMsg *) call Packet.getPayload(&sensor_packet, sizeof(SensorMsg));
      if (payload == NULL) {
        return ;
      }
      payload->nodeid = TOS_NODE_ID;
      payload->type = HUMIDITY;
      payload->data = data;
      if (call AMSend.send(AM_BROADCAST_ADDR, &sensor_packet, sizeof(SensorMsg)) == SUCCESS) {
        call Leds.led1Toggle();
        busy = TRUE;
      }
    }
  }

  event void readPhoto.readDone(error_t result, uint16_t data) {
    if (!busy && result == SUCCESS) {
      SensorMsg *payload = (SensorMsg *) call Packet.getPayload(&sensor_packet, sizeof(SensorMsg));
      if (payload == NULL) {
        return ;
      }
      payload->nodeid = TOS_NODE_ID;
      payload->type = PHOTO;
      payload->data = data;
      if (call AMSend.send(AM_BROADCAST_ADDR, &sensor_packet, sizeof(SensorMsg)) == SUCCESS) {
        call Leds.led2Toggle();
        busy = TRUE;
      }
    }
  }

  event void AMControl.startDone(error_t err) {
    if (err == SUCCESS) {
      call Timer.startPeriodic(TIMER_PERIOD_MILLI);
    }
    else {
      call AMControl.start();
    }
  }

  event void AMControl.stopDone(error_t err) {

  }

  event void AMSend.sendDone(message_t* msg, error_t error) {
    if (&sensor_packet == msg) {
      busy = FALSE;
    }
  }
}
