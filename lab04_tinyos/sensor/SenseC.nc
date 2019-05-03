#include "Timer.h"
#include "Sense.h" 
#include "SensirionSht11.h"

module SenseC
{
	uses 
	{
		interface Boot;
		interface Leds;
		interface Timer<TMilli>;
		interface Read<uint16_t> as readTemp;
    	interface Read<uint16_t> as readHumidity;
    	interface Read<uint16_t> as readPhoto;
    	interface Packet;
    	interface AMPacket;
    	interface AMSend;
    	interface SplitControl as Control;
	}
}

implementation
{

	#define SAMPLING_FREQUENCY 100

	// sense pactet need to be send
	message_t sense_packet;

	bool locked =FALSE;

	// sense data
  	uint16_t TempData;
  	uint16_t HumidityData;
  	uint16_t PhotoData;

	event void Boot.booted() 
	{
    	call Control.start();
	}

	event void Control.startDone(error_t err) 
	{
    	if (err == SUCCESS) 
		{
      		call Timer.startPeriodic(1000);
    	}
  	}
	
  	event void Control.stopDone(error_t err) // error msg come from here
  	{}

    event void Timer.fired()
    {	
        if (locked) 
        {
            return;
        }
        call readTemp.read();      // Read temporary
        call readHumidity.read();  // Read humidity
        call readPhoto.read();     // Read photovoltaic
    }

    event void readTemp.readDone(error_t result, uint16_t val) 
    {
        if (result == SUCCESS) 
        {
            SenseMsg *payload = (SenseMsg*) call Packet.getPayload(&sense_packet, sizeof(SenseMsg));// payload is the part of transmitted data that is the actual intended message
            if (payload == NULL) 
            {
                return;
            }    
            payload->nodeid = TOS_NODE_ID;
            payload->kind = TEMPORARY;
            payload->data = val;
            if (call AMSend.send(AM_BROADCAST_ADDR, &sense_packet, sizeof(SenseMsg)) == SUCCESS) // send msg successfully
            {
                call Leds.led0Toggle();
                locked = TRUE;
            }
        }
       
    }

    event void readHumidity.readDone(error_t result, uint16_t val) 
    {
        if (result == SUCCESS) 
        {
            SenseMsg *payload = (SenseMsg*) call Packet.getPayload(&sense_packet, sizeof(SenseMsg));
            if (payload == NULL) 
            {
                return;
            } 
            payload->nodeid = TOS_NODE_ID;
            payload->kind = HUMIDITY;
            payload->data = val;
            if (call AMSend.send(AM_BROADCAST_ADDR, &sense_packet, sizeof(SenseMsg)) == SUCCESS)
            {
                call Leds.led1Toggle();
                locked = TRUE;
            }
        }
        
    }

    event void readPhoto.readDone(error_t result, uint16_t val) 
    {
        if (result == SUCCESS) 
        {
            SenseMsg *payload = (SenseMsg*)call Packet.getPayload(&sense_packet, sizeof(SenseMsg));
            if (payload == NULL) 
            {
                return;
            }
            payload->nodeid = TOS_NODE_ID;
            payload->kind = PHOTOVOLTAIC;
            payload->data = val;
            if (call AMSend.send(AM_BROADCAST_ADDR, &sense_packet, sizeof(SenseMsg)) == SUCCESS) 
            {
                call Leds.led2Toggle();
                locked = TRUE;
            }
        } 
    }

    event void AMSend.sendDone(message_t* msg, error_t err) 
    {
        if (&sense_packet == msg) 
        {
             locked = FALSE;
        }
  }
}

// interface Read<val_t> 
// {
// 	/**
// 	* Initiates a read of the value.
// 	*
// 	* @return SUCCESS if a readDone() event will eventually come back.
// 	*/
// 	command error_t read();

// 	/**
// 	* Signals the completion of the read().
// 	*
// 	* @param result SUCCESS if the read() was successful
// 	* @param val the value that has been read
// 	*/
// 	event void readDone( error_t result, val_t val );
// }