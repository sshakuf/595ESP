#ifndef _74HC595_H
#define _74HC595_H

#include <c_types.h>
#include <ip_addr.h>
#include <espconn.h>
#include "server.h"

#include "common.h"


void ICACHE_FLASH_ATTR Init595();
void ICACHE_FLASH_ATTR loop595();
void ICACHE_FLASH_ATTR out595();

#endif