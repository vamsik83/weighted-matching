#ifndef __MEASURE_TIME_H
#define __MEASURE_TIME_H

#ifndef WIN32 /*Linux or Solaris*/
#include<sys/times.h>
#include<time.h>
#else 
#include<windows.h>
#endif

#ifndef WIN32
typedef struct anst_clock{
	struct tms measureTimeS1;
	struct tms measureTimeS2;
	clock_t wallStart;
	clock_t wallEnd;
}Clock;
clock_t GetClockTicks(Clock *);
#else
typedef struct anst_clock{
	FILETIME measureTimeS1;
	FILETIME measureTimeS2;
}Clock;
unsigned long GetClockTicks(Clock *);
#endif

void StopClock(Clock *);
void StartClock(Clock *);
Clock* CreateClock(void);
#endif
