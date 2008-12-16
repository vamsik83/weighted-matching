#ifdef WIN32
#include<windows.h>
#else
#include<sys/times.h>
#include<unistd.h>
#endif
#include<assert.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "MeasureTime.h"

#ifdef WIN32
static HANDLE hptr=0;
FILETIME sysptr;
FILETIME exitptr;
FILETIME createptr; 
#endif


/* Returns the usertime (time actually spend on 
 * executing CPU instructions). User time is good
 * beacuse it does not depend on the load of the
 * machine. Also the User time does not include
 * system time used by kernel to do processing on 
 * this task.
 *
 * Vamsi Kundeti @ ANST 
 */
void StartClock(Clock *clk){
#ifndef WIN32
	if((clk->wallStart = times(&(clk->measureTimeS1))) == (clock_t)-1){
		fprintf(stderr,"WARNING:Unable to Start the Clock %p \n",clk);
	}
#else
	if(!GetProcessTimes(hptr,&createptr,&exitptr,&sysptr,
		&(clk->measureTimeS1))){
		fprintf(stderr,"WARNING:Unable to Start the Clock %p \n",clk);
	}
#endif
}
void StopClock(Clock *clk){
#ifndef WIN32
	if((clk->wallEnd = times(&(clk->measureTimeS2))) == (clock_t)-1){
		fprintf(stderr,"WARNING:Unable to Stop the Clock %p \n",clk);
	}
#else
	if(!GetProcessTimes(hptr,&createptr,&exitptr,&sysptr,
		&(clk->measureTimeS2))){
		fprintf(stderr,"WARNING:Unable to Start the Clock %p \n",clk);
	}
#endif
}
#ifndef WIN32
clock_t GetClockTicks(Clock *clk){
#else
unsigned long GetClockTicks(Clock *clk){
#endif

#ifndef WIN32
	return ((clk->measureTimeS2).tms_utime - (clk->measureTimeS1).tms_utime);
#else
	/*Windows uses 1e-7 scale but tick is 1e-2 */
	ULARGE_INTEGER start;
	ULARGE_INTEGER end; 
	start.u.LowPart = (clk->measureTimeS1).dwLowDateTime;
	start.u.HighPart = (clk->measureTimeS1).dwHighDateTime;
	end.u.LowPart = (clk->measureTimeS2).dwLowDateTime;
	end.u.HighPart = (clk->measureTimeS2).dwHighDateTime;

	return (end.QuadPart-start.QuadPart)*(1e-5);
#endif	
}

#ifndef WIN32
clock_t GetWallClockTicks(Clock *clk){
	return (clk->wallEnd - clk->wallStart);
}
#endif

Clock * CreateClock(){
#ifdef WIN32
	if(!hptr){
		hptr = GetCurrentProcess();
	}
#endif
	return (Clock *)malloc(sizeof(Clock)*1);
}
void DeleteClock(Clock *clk){
	free(clk);
}
#ifdef UNIT_TEST_MEASURE_TIME
int main(int argc,char **argv){
	volatile int count,count1=0;
	volatile int i;
	volatile double X=1024;
	Clock *test_clk = CreateClock();

	StartClock(test_clk);
	for(i=0;i<1000000;i++){
		count1+=(i+1);
		count1 = (count1*i)/count1;
		X += ((X*X) + X/0.331)*(X*X*X);
	}
	StopClock(test_clk);
	printf("PROBE1: Clock Ticks Elapsed is %lu \n",(clock_t)GetClockTicks(test_clk)); 
	printf("PROBE1: Wall Clock Ticks is %lu \n", GetWallClockTicks(test_clk));

	StartClock(test_clk);
	for(i=0;i<1000000;i++){
		count1+=(i+1);
		count1 = (count1*i)/count1;
		X += ((X*X) + X/0.331)*(X*X*X);
	}
	/*Adding sleep here so that usertime will not change
	 *but wall clock time changes*/
	sleep(5);
	StopClock(test_clk);
	printf("PROBE2: Clock Ticks Elapsed is %lu \n",(clock_t)GetClockTicks(test_clk));
	printf("PROBE2: Wall Clock Ticks is %lu \n", GetWallClockTicks(test_clk));

	printf("size of clock_t is %d \n",sizeof(clock_t));
	printf("CLK_TCK = %u \n",CLK_TCK);

}
#endif
