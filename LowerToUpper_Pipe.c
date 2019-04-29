#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
int main()
{
  int fd[2];
  char s[10];
  if(pipe(fd) == -1) {
    printf("Pipe failed");
  }
  if(fork() == 0) {
    printf("This is child with id %d\n", getpid());
    printf("My parent is %d\n", getppid());
    printf("Enter the string\n");
    scanf("%s", &s);
    close(fd[0]);
    write(fd[1], s, strlen(s));
    close(fd[1]);
  } else {
    wait(NULL);
    printf("Parent process with id %d\n", getpid());
    close(fd[1]);
    read(fd[0], s, sizeof(s));
    int i = 0;
    while(s[i] != '\0') {
      s[i] = toupper(s[i]);
      i++;
    }
    printf("The changed string is %s\n", s);
    close(fd[0]);
  }
}
