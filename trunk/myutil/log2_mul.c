#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main(int argc,char **argv){
	unsigned int i;
	printf("please enter an i\n");
	scanf("%u",&i);
	printf("%u\n",(unsigned int)log2f((float)i));
}
