#ifndef SENSE_H
#define SENSE_H

#define TEMPERATURE 0
#define HUMIDITY 1
#define PHOTO 2

typedef nx_struct SensorMsg {
    nx_uint16_t nodeid;
    nx_uint16_t type;
    nx_uint16_t data;
} SensorMsg;

enum {
    AM_SENSE = 6,
    TIMER_PERIOD_MILLI = 2000
};

#endif
