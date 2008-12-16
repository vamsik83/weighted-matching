#include<stdio.h>
double minus_zero=-1.0;
double d1=-0.99999999999999985;
float fminus_zero=-0.0;
long long int BASE = 0x8000000000000000;

int main(){
	printf("sizeof long long int is %d \n",sizeof(long long int)); 
	printf("sizeof long int is %d \n",sizeof(long int)); 
	printf("%Lx\n",(BASE-*((long long int *)&minus_zero)));
	printf("%Lx\n",(BASE-*((long long int *)&d1)));
	printf("%x\n",*((int *)&fminus_zero));
}
