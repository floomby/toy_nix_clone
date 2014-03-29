#include "../include/sleep.h"

void msleep(uint64_t millis)
{
	uint64_t tmp = the_timer->millis;
	uint64_t target = tmp + millis;

	while(the_timer->millis < target){

	}
}

void sleep(uint32_t sec)
{
	msleep(sec * 1000);
}