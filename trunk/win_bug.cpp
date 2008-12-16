#include<stdio.h>
#include<iostream>

int main(){
	unsigned int *a = NULL;
	unsigned int b;
	printf("Enter the size\n");
	scanf("%u",&b);

	a = new unsigned int[b];
	a[b-1] = 10;
}
