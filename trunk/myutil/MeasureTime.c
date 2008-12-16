#ifdef WIN32
#include<windows.h>
#else
#include<sys/times.h>
#endif
#include<assert.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include "MeasureTime.h"

#ifdef WIN32
static HANDLE hptr=0;
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
	if(times(&(clk->measureTimeS1)) == (clock_t)-1){
		fprintf(stderr,"WARNING:Unable to Start the Clock %p \n",clk);
	}
}
void StopClock(Clock *clk){
	if(times(&(clk->measureTimeS2)) == (clock_t)-1){
		fprintf(stderr,"WARNING:Unable to Stop the Clock %p \n",clk);
	}
}
clock_t GetClockTicks(Clock *clk){
	return ((clk->measureTimeS2).tms_utime - (clk->measureTimeS1).tms_utime);
}
Clock * CreateClock(){
	return (Clock *)malloc(sizeof(Clock)*1);
}
void DeleteClock(Clock *clk){
	free(clk);
}
#ifdef UNIT_TEST_MEASURE_TIME
int main(int argc,char **argv){
	struct tms s1;
	struct tms s2;
	volatile int count,count1;
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
	printf("PROBE1: Clock Ticks Elapsed is %Lu \n",(clock_t)GetClockTicks(test_clk)); 

	StartClock(test_clk);
	for(i=0;i<1000000;i++){
		count1+=(i+1);
		count1 = (count1*i)/count1;
		X += ((X*X) + X/0.331)*(X*X*X);
	}
	StopClock(test_clk);
	printf("PROBE2: Clock Ticks Elapsed is %Lu \n",(clock_t)GetClockTicks(test_clk));

	printf("size of clock_t is %d \n",sizeof(clock_t));

}
#endif
