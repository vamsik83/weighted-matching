#include<stdio.h>
unsigned long fib[2];
int main(){
	unsigned long n;
	unsigned long fibt;
	unsigned long i;
	fib[0]=0; fib[1]=1;
	printf("Please Enter n\n");
	scanf("%u",&n);
	for(i=2;i<=n;i++){
		fibt = fib[1] + fib[0];
		fib[0] = fib[1];
		fib[1] = fibt;
	}
	printf("The n^th fib is %u\n",fib[1]);

}

