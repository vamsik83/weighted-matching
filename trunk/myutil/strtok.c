#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
char * my_strtok(char *input,char t){
static unsigned int token=0;   
static char **part_token = NULL;
static unsigned int current_returned_tokens=0;
  if(input){
    unsigned int i=0,j=0;
    /*Count the tokens and create the part_token array*/
    token=0;
    while(input[i]){
		if(input[i]==t){
			token++;
		}
		i++;
   }
   part_token = (char **) malloc(sizeof(char *)*(token+1));
   token = 0;
   i=0;j=0;
   while(input[i]){
       if(input[i] == t){
	   	part_token[token++] = malloc(sizeof(char)*(i-j+1));
	   	assert(part_token[token-1]);
	   	assert(strncpy(part_token[token-1],&input[j],i-j) == part_token[token-1]);
     	part_token[token-1][i-j] = '\0';
      	j = i+1;
   	  }
   i++;
  }
  part_token[token++] = malloc(sizeof(char)*(i-j+1));
  strncpy(part_token[token-1],&input[j],i-j);
  part_token[token-1][i-j+1] = '\0';
 }else if(current_returned_tokens < token){
      return part_token[current_returned_tokens++];
 }else{
	 current_returned_tokens = 0;
	 return NULL;
 }
}
int main(){
	//char *test_string = "ababbbbaaaaaba";
	char test_string[256];
	char *out=NULL;
	while(scanf("%s",test_string)){
		my_strtok(test_string,'a');
		out = my_strtok(NULL,'a');
		while(out){
			printf("%s\n",((out[0])?out:"(NULL)"));
			free(out);
			out = my_strtok(NULL,'a');
		}
	}
}
