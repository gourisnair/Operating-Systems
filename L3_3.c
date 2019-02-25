#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#define pi 3.14
int main()
{
	pid_t pid1, pid2;
	pid1 = fork();
	if(pid1 == 0) {
		execl("./L3_3a", "", NULL);	
	} else {
			if(pid1 > 0) {
				wait(NULL);
				pid2 = fork();
				if(pid2 == 0) {
					execl("./L3_3b", "", NULL);				
				} else {
						wait(NULL);
					}
			}
		}
}
