#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int* MinMaxInt(int *a,unsigned int n){
int current_min = a[0];
int current_max = a[1];
static int ret_value[2];
unsigned int i;
assert(n>=2);
/* 1 comparison here */
if (current_min > current_max){
	current_min = a[1];
	current_max = a[0];
}
for (i = 2; i < n - 1; i += 2){
    /*3 Comparisons here */
    if (a[i] < a[i + 1])
      {
	if (a[i] < current_min)
	  current_min = a[i];
	if (a[i + 1] > current_max)
	  current_max = a[i + 1];
      }
    else
      {
	if (a[i + 1] < current_min)
	  current_min = a[i + 1];
	if (a[i] > current_max)
	  current_max = a[i];
      }
}
 ret_value[0] = current_min;
 ret_value[1] = current_max;
 return ret_value;
}
int main(){
	int test[256];
	int i=0;
	int *output;
	while((i<256)&& (scanf("%d",&test[i++])==1));
	output = MinMaxInt(test,i);
	printf("Min=%d , Max=%d\n",output[0],output[1]);
}
