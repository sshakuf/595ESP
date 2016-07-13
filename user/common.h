#ifndef COMMON_H
#define COMMON_H

#include "c_types.h"

#define SSID "STRSI"
#define SSID_PASSWORD "1011040311037"
// #define SSID "ShakufNet"
// #define SSID_PASSWORD "10111011"

//#define SSID "NewBackupChegg"
//#define SSID_PASSWORD "Ch399!M3"
//#define SSID "klar_wifi"
//#define SSID_PASSWORD "idonoa2013"
// #define SSID "Backup"
// #define SSID_PASSWORD "!Ch399!M3"
// #define SSID "teridion"
// #define SSID_PASSWORD "teridionisthebest"

#define AP_SSID     "ESP_EVENTS"
#define AP_PASSWORD "12341234"

#define HOSTNAME "Speakers"

// void dbgprint1(char* inBuff);
// void dbgprint(const char* format, ... );
// char dbgbuff[512];
// #define dbgprintf(f_, ...) os_sprintf(dbgbuff, (f_), __VA_ARGS__);\
//     			dbgprint(dbgbuff);

#define  OutputPin(pin, val) val==0 ? gpio_output_set(0, pin, pin, 0) : gpio_output_set(pin, 0, pin, 0)
#define  SetPin(pin) gpio_output_set(pin, 0, pin, 0)
#define  ClearPin(pin) gpio_output_set(0, pin, pin, 0)

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))
#define BIT_GET(a,b)  ((a >> b) & 1)

typedef struct
{
	int Hour;
	int Min;
} Time;

typedef struct
{
    int Sunday : 1;
    int Monday    : 1;
    int Tuesday       : 1;
    int Wednesday   : 1;
    int Thursday   : 1;
    int Friday   : 1;
    int Saturday   : 1;
} Days;

typedef struct
{
	Time StartTime;
	Time EndTime;
	Days DaysRepeat;
	int Port;
	bool Active;
}PowerEvent;

typedef enum  /// bit wise
{
	PORT_INPUT = 0,
	PORT_OUTPUT = 1,
    PORT_EPORT_OUTPUT = 2,

}PortType;

typedef struct
{
	int PortPinNumber;
	PortType Type;
	char PortName[20];
}PortInfo;

#define MAX_TIMED_POWER_EVENTS 10

//#define ESP_1

#ifdef ESP_1
#define NUM_OF_PORTS 1
#else
    // remove 3 ports for the 74hc595
#define NUM_OF_PORTS 5
#define NUM_OF_E_PORTS 8
#define NUM_ALL_PORTS NUM_OF_PORTS+NUM_OF_E_PORTS
#endif

//__declspec(align(4))  // needs to align ?
typedef union _DWORD_PART_ {
    char settings[128*8];

    struct {
        int magic;
        char ssid[32];
        char password[64];
        PowerEvent _PowerEvents[MAX_TIMED_POWER_EVENTS];
        PortInfo Ports[NUM_OF_PORTS + NUM_OF_E_PORTS];
        int SNTP;
        int ServerPort;
        int ePort;
    } ;
} FlashData;

#define MAGIC_NUM 7051
#define PRIV_PARAM_START_SEC 0x3c
#define PRIV_PARAM_SAVE     0

FlashData* flashData;
char* IPStation;

bool ICACHE_FLASH_ATTR IsStationConnected();



#endif //COMMON_H
