#include<stdio.h>
#include<assert.h>

int main(int argc,char **argv){
	double f1,f2;
	FILE *file1,*file2;
	unsigned line = 0;
	double sum1=0.0,sum2=0.0;

	assert(argc == 3);

	file1  = fopen(argv[1],"r");
	file2 = fopen(argv[2],"r");
	assert(file1 && file2);

	while(fscanf(file1,"%lf",&f1)==1 && fscanf(file2,"%lf",&f2)==1){
		line++;
		sum1+=fabs(f1);sum2+=fabs(f2);
		if(fabs(f1-f2)<0.000001){
			continue;
		}else{
			fprintf(stderr,"fdiff failed at %u f1=%lf f2=%lf\n",line,f1,f2);
		}
	}
	printf("SUM1 = %lf SUM2 = %lf\n",sum1,sum2);

}
