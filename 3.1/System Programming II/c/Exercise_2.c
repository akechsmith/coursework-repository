














/* Exercise */
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[]){
 printf("X\n");
 fork();
 printf("Y\n");
 fork();
 printf("Y\n");
 return 0;
}