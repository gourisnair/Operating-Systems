#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  int fd[2];
  pid_t pid;
  char s[10];
  if(pipe(fd) == -1) {
    printf("Pipe failed");
  }
  pid = fork();
  if(pid == 0) {
    printf("Enter a string: ");
    scanf("%s", &s);
    close(fd[0]);
    write(fd[1], s, strlen(s));
    close(fd[1]);
  }else {
    wait(NULL);
	close(fd[1]);
	read(fd[0],s,sizeof(s));
	int i=0;
	while(s[i] !='\0')
		{
			s[i]=toupper(s[i]);
			i++;
		}
	close(fd[0]);
	printf("Parent:\nFinal String: %s\n",s);
  }
  return 0;
}
