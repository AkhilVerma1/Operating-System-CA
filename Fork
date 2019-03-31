//child process must print some sequence and parent process must wait wait for the child process to complete before termination.

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    int number;
    printf("Enter any random number.!\n");
    scanf("%d",&number);
    if(number<0){
        printf("Number is negative. Please enter a +ve number, try again.!\n");
    }
    else{
    if(fork()==0){
    while(number>0){
        printf("%d, ",number);
        number=number/2;
    }
        printf("\n");
    }
    else{
        wait(NULL);
    }
    }
    return 0;
}
