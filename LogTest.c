#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double v = -1.00000000000000003037e-13; 
double v1 = 1.0e+13;
int main(int argc,char **argv){
	double r;
	v= fabs(v);
	r = (log(v)/M_LN10);
	printf("log(v)=%lf \n",r);
	r = (log(v1));
	printf("log(v1)=%lf \n",r);
}
