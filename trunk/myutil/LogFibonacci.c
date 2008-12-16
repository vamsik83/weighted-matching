/*Find the n^th fibonacci number in O(log(n)) 
 *time, using the following idea of matrix formulation 
 * 
 * [   F_n  ]	[ 1	  1  ] [F_{n-1}]
 * [		] = [		 ] [	   ]
 * [ F_{n-1}]	[ 1	  0  ] [F_{n-2}]
 *
 * vamsik(at)engr(dot)uconn July 11, 2008
 */
#include<stdio.h>
#include<stdlib.h>
/*Fib returns the n^th Fibonacci number*/
unsigned int Fib(unsigned int n){
	unsigned int deg=1;
	unsigned int fib[2][2] = {{1,1},{1,0}};
	unsigned int fibAns[2][2];
	unsigned char initAns=0;
	unsigned int mul[4];
	if(n<=2){ return (n<2)?n:1;}
	while(deg < n-1){
		 mul[0] = fib[0][0]*fib[0][0] + fib[0][1]*fib[1][0];
		 mul[1] = fib[0][0]*fib[0][1] + fib[0][1]*fib[1][1];
		 mul[2] = fib[1][0]*fib[0][0] + fib[1][1]*fib[1][0];
		 mul[3] = fib[1][0]*fib[0][1] + fib[1][1]*fib[1][1];
		 fib[0][0] = mul[0]; fib[0][1] = mul[1]; 
		 fib[1][0] = mul[2]; fib[1][1] = mul[3];
		 deg <<=1;
		 if(deg & n-1){ /*i^th bit set*/
			 if(!initAns){
		 		fibAns[0][0] = fib[0][0]; fibAns[0][1] = fib[0][1]; 
		 		fibAns[1][0] = fib[1][0]; fibAns[1][1] = fib[1][1];
				initAns=1;
			 }else{
		 		mul[0] = fibAns[0][0]*fib[0][0] + fibAns[0][1]*fib[1][0];
		 		mul[1] = fibAns[0][0]*fib[0][1] + fibAns[0][1]*fib[1][1];
		 		mul[2] = fibAns[1][0]*fib[0][0] + fibAns[1][1]*fib[1][0];
		 		mul[3] = fibAns[1][0]*fib[0][1] + fibAns[1][1]*fib[1][1];
		 		fibAns[0][0] = mul[0]; fibAns[0][1] = mul[1]; 
		 		fibAns[1][0] = mul[2]; fibAns[1][1] = mul[3];
			 }
		 }
	}
	if(n-1 & 1){
		return fibAns[0][0] + fibAns[0][1];
	}
	return fibAns[0][0];
}
int main(int argc,char **argv){
	unsigned int n;
	printf("Enter the N:\n");
	scanf("%u",&n);
	printf("The %u^th Fibonacci Number is %u\n",n,Fib(n));
}
